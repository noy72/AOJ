#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

#define int long long

const int MAX_N = 100010;

class segTree{
    public:
        int n, dat[4 * MAX_N];
        void init(int n_, int value, int dat_b[4 * MAX_N] = NULL){
            n = 1;
            while(n < n_) n *= 2;
            rep(i,2 * n){
                dat[i] = value;
                if(dat_b != NULL) dat_b[i] = value;
            }
        }
        void output(int a[4 * MAX_N]){
            show("print");
            range(i,1,n * 2) cout << (a[i] == INT_MAX ? 0 : a[i]) << ' ';
            cout << endl;
        }
};

class starrySky : public segTree{
    private:
        int query(int a, int b, int k, int l, int r){
            if(b <= l || r <= a) return 0;
            if(a <= l && r <= b) return dat[k] + dat_add[k];

            int vl = query(a, b, k * 2, l, (l + r) / 2);
            int vr = query(a, b, k * 2 + 1, (l + r) / 2, r);
            return max(vl, vr) + dat_add[k];
        }
        void add(int a, int b, int k, int l, int r, int x){
            if(b <= l || r <= a) return;
            if(a <= l && r <= b){
                dat_add[k] += x;
            }else{
                add(a, b, k * 2, l, (l + r) / 2, x);
                add(a, b, k * 2 + 1, (l + r) / 2, r, x);
                dat[k] = max(dat[k * 2] + dat_add[k * 2], dat[k * 2 + 1] + dat_add[k * 2 + 1]);
            }
        }
        void init(int n_){ segTree::init(n_,0,dat_add); }
    public:
        int dat_add[4 * MAX_N];
        starrySky(int n){ init(n); }
        int query(int a, int b){ return query(a, b, 1, 0, n); }
        void add(int s, int t, int x){ add(s, t, 1, 0, n, x); }
        void add(int i, int x){ add(i, i + 1, 1, 0, n, x); }
};


signed main(){
    long long n, h;
    cin >> n >> h;

    starrySky seg(n); //体力
    priority_queue<pair<long long, int>> q; //泉の回復量、pos
    long long cur = h, ans = 0;
    rep(i,n - 1){
        long long damage, heal;
        cin >> damage >> heal;
        q.push(make_pair(heal, i));

        seg.add(i, cur);
        cur -= damage;
        while(cur <= 0){
            pair<long long, int> use = q.top(); q.pop();
            long long maxHP = seg.query(use.second, i + 1); //回復地点から現在地までの体力の最大

            if(maxHP + use.first > h){ //回復量が上限を超えるので、実際の回復量に変更
                q.push(make_pair(h - maxHP, use.second));
                continue;
            }

            long long can_use = (h - maxHP) / use.first;
            long long require = ceil((-1.0 * cur + 1) / use.first);
            long long used = min(can_use, require);
            ans += used;
            cur += used * use.first;

            seg.add(use.second, i + 1, used * use.first);
            q.push(use);
        }
    }
    cout << ans << endl;
}
