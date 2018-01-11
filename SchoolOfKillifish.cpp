#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

const int MAX_N = 1000100;

class segTree{
    public:
        int n;
        vector<int> dat;
        void init(int n_, int value, int dat_b[4 * MAX_N] = NULL){
            n = 1;
            while(n < n_) n *= 2;

            dat = vector<int>(4 * n);
            rep(i,2 * n){
                dat[i] = value;
                if(dat_b != NULL) dat_b[i] = value;
            }
        }
        void output(vector<int> a){
            show("print");
            range(i,1,n * 2) cout << (a[i] == INT_MAX ? -1 : a[i]) << ' ';
            cout << endl;
        }
};

class rangeMinimumQuery : public segTree{
    private:
        int query(int a, int b, int k, int l, int r){
            //[a, b) と[l, r)が交差しなければ、INT_MAX
            if(r <= a || b <= l) return INT_MAX;
            //[a,b)が[l,r)を完全に含んでいれば、この節点の値
            if(a <= l && r <= b) return dat[k];

            //そうでなければ、２つのこの最小値
            int vl = query(a, b, k * 2, l, ( l + r) / 2);
            int vr = query(a, b, k * 2 + 1, (l + r) / 2, r);
            return min(vl, vr);
        }
    public:
        void init(int n_){ segTree::init(n_,INT_MAX); }
        void update(int i, int x){
            i += n; //葉の節点
            dat[i] = x;
            while(i > 0){ //登りながら更新
                dat[i / 2] = min(dat[i], dat[i^1]);
                i = i / 2;
            }
        }
        //[a, b)の最小値を求める
        int query(int a, int b){ return query(a,b,1,0,n); }
};

class rangeUpdateQuery : public segTree{ //任意の範囲をupdateできる。minとかsumは取らない
    private:
        int dat_lazy[4 * MAX_N]; //遅延されている値を保持
        int query(int a, int b, int k, int l, int r){
            //要実装
            evaluate(k);

            if(b <= l || r <= a) return INT_MAX;
            else if(a <= l && r <= b) return dat[k];

            int vl = query(a, b, k * 2, l, (l + r) / 2);
            int vr = query(a, b, k * 2 + 1, (l + r) / 2, r);
            return min(vl, vr);
        }
        inline void evaluate(int k){
            if(dat_lazy[k] == INT_MAX) return;
            dat[k] = dat_lazy[k];
            if(k < n){
                dat_lazy[2 * k] = dat_lazy[k]; //遅延を伝搬する部分
                dat_lazy[2 * k + 1] = dat_lazy[k];
            }
            dat_lazy[k] = INT_MAX;
        }
        void update(int a, int b, int k, int l, int r, int x){
            evaluate(k);

            if(b <= l || r <= a ) return;

            if(a <= l && r <= b){
                dat_lazy[k] = x;
            }else{
                evaluate(k);
                update(a, b, k * 2, l, (l + r) / 2, x);
                update(a, b, k * 2 + 1, (l + r) / 2, r, x);
            }
        }
    public:
        void init(int n_){ segTree::init(n_,INT_MAX,dat_lazy); }
        int query(int a, int b){ return query(a,b,1,0,n); }
        void update(int s, int t, int x){ update(s, t, 1, 0, n, x); }
        void update(int i, int x){ update(i, i + 1, 1, 0, n, x); }
        int get(int a){ return query(a, a + 1); };
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


int main(){
    int h, w, q;
    while(cin >> h >> w >> q, h){
        bool f = false;
        if(h > w){
            swap(h, w);
            f = true;
        }
        vector<rangeMinimumQuery> seg(h);
        rep(i,h){
            seg[i].init(w);
            rep(j,w){
                int x;
                cin >> x;
                seg[i].update(j, x);
            }
        }
        rep(i,q){
            pair<int, int> a, b;
            cin >> a.first >> a.second >> b.first >> b.second;
            if(f){
                swap(a.first, a.second);
                swap(b.first, b.second);
            }
            //a.second++; b.second++;
            //cout << a.first << ' ' << a.second << endl;
            //cout << b.first << ' ' << b.second << endl;
            //show(seg[0].query(1,9));

            int ans = INT_MAX;
            for(int i = a.first; i <= b.first; i++){
                //show(i)
                //show(seg[i].query(a.second, b.second + 1));
                ans = min(ans, seg[i].query(a.second, b.second + 1));
            }
            cout << ans << endl;
        }
    }
}
