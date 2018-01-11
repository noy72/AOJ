#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

const int MAX_N = 400010;

class segTree{
    public:
        int n, dat[4 * MAX_N];
        void init(int n_, int value, int dat_b[4 * MAX_N] = NULL){
            n = 1;
            while(n <= n_) n *= 2;
            rep(i,2 * n){
                dat[i] = value;
                if(dat_b != NULL) dat_b[i] = value;
            }
        }
        void initArray(int n_, int a[MAX_N]){ //配列aでの初期化
            n = 1;
            while(n <= n_) n *= 2;
            for(int i = n; i < n + n_; i++){
                dat[i] = a[i - n];
            }
            for(int i = n - 1; i >= 1; i--){
                dat[i] = min(dat[i * 2], dat[i * 2 + 1]);
                //dat[i] = dat[i * 2] + dat[i * 2 + 1];
            }
        }
        void output(int a[4 * MAX_N]){
            show("print");
            range(i,1,n * 2) cout << (a[i] == INT_MAX ? 0 : a[i]) << ' ';
            cout << endl;
        }
};

class rangeAddQuery : public segTree{
    //dat : その区間に一様に加算された値を保持
    //dat_add : 一様でなく加えられた値を保持
    private:
        int dat_add[4 * MAX_N];
        int query(int a, int b, int k, int l, int r){
            if(b <= l || r <= a) return 0;
            if(a <= l && r <= b) return dat[k] * (r - l) + dat_add[k];

            int res = (min(b, r) - max(a, l)) * dat[k];
            res += query(a, b, k * 2, l, (l + r) / 2);
            res += query(a, b, k * 2 + 1, (l + r) / 2, r);
            return res;
        }
        void add(int a, int b, int k, int l, int r, int x){
            if(a <= l && r <= b){
                dat[k] += x;
            }else if(l < b && a < r){
                dat_add[k] += (min(b, r) - max(a, l)) * x;
                add(a, b, k * 2, l, (l + r) / 2, x);
                add(a, b, k * 2 + 1, (l + r) / 2, r, x);
            }
        }
    public:
        rangeAddQuery(int n){ init(n); }
        void init(int n_){ segTree::init(n_, 0, dat_add); }
        int query(int a, int b){ return query(a,b,1,0,n); }
        void add(int s, int t, int x){ add(s, t, 1, 0, n, x); }
        void add(int i, int x){ add(i, i + 1, 1, 0, n, x); }
        int get(int a){ return query(a, a + 1); }
};

class rangeSumQuery : public segTree{
    private:
        int query(int a, int b, int k, int l, int r){
            if(r <= a || b <= l) return 0;
            if(a <= l && r <= b) return dat[k];

            int vl = query(a, b, k * 2, l, ( l + r) / 2);
            int vr = query(a, b, k * 2 + 1, (l + r) / 2, r);
            return vl + vr;
        }
    public:
        rangeSumQuery(int n){ init(n); }
        void init(int n_){ segTree::init(n_, 0); }
        void update(int i, int x){
            i += n; //葉の節点
            dat[i] += x;
            while(i > 0){ //登りながら更新
                dat[i / 2] = dat[i] + dat[i^1];
                i = i / 2;
            }
        }
        int query(int a, int b){ return query(a,b,1,0,n); }
        int get(int a){ return query(a, a + 1); }
        bool C(int mid, int x){
            return query(0, mid) < x;
        }
        int pos(int x){
            //show(x)
            int right = n, left = 0;
            rep(i,25){
                int mid = (right + left ) / 2;
                if(C(mid,x)) left = mid;
                else right = mid;
            }
            return left;
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
        rangeMinimumQuery(int n){ init(n); }
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
        rangeUpdateQuery(int n){ init(n); }
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

map<int,int> m, s; //id, pos / pos, id

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    int q, lim;
    while(cin >> q >> lim, q){
        //show(q)
        rangeSumQuery seg(q + 1);
        m.clear(); s.clear();
        int total = 0;
        rep(i,q){
            int com, x;
            cin >> com >> x;

            switch (com) {
                int pos;
                case 0:
                    pos = m.size();
                    m[x] = pos;
                    s[pos] = x;
                    seg.update(pos, 1);
                    total++;
                    if(total > lim){
                        seg.update(seg.pos(0), -1);
                        total--;
                    }
                    break;
                case 1:
                    pos = seg.pos(x);
                    seg.update(pos, -1);
                    total--;
                    break;
                case 2:
                    //show(seg.pos(x));
                    cout << s[seg.pos(x)] << endl;
                    break;
                case 3:
                    seg.update(m[x], -1);
                    total--;
                    break;
            }
        }
        cout << "end" << endl;
    }
}
