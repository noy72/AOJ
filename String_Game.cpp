#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

const int MAX_N = 200005;

string dat[4 * MAX_N];
string dat_lazy[4 * MAX_N];

class segTree{
    public:
        int n;
        virtual string query(int, int, int, int, int) = 0;
        void init(int n_){}
};

class rangeUpdateQuery : public segTree{
    private:
        string query(int a, int b, int k, int l, int r){
            evaluate(k);

            if(b <= l || r <= a) return "";
            else if(a <= l && r <= b) return dat[k];
            else{
                evaluate(k);
                string vl = query(a, b, k * 2, l, (l + r) / 2);
                string vr = query(a, b, k * 2 + 1, (l + r) / 2, r);
                return vl + vr;
            }
        }
        inline void evaluate(int k){
            if(dat_lazy[k] == "") return;
            dat[k] = dat_lazy[k];
            if(k < n){
                dat_lazy[2 * k] = dat_lazy[k];
                dat_lazy[2 * k + 1] = dat_lazy[k];
            }
            dat_lazy[k] = "";
        }
        string update(int a, int b, int k, int l, int r, string x){
            evaluate(k);

            if(r <= a || b <= l) return dat[k];

            if(a <= l && r <= b){
                return dat_lazy[k] = x;
            }else if(l < b && a < r){
                evaluate(k);
                string vl = update(a, b, k * 2, l, (l + r) / 2, x);
                string vr = update(a, b, k * 2 + 1, (l + r) / 2, r, x);
                return dat[k] = vl + vr;
            }
            return "";
        }
    public:
        void init(int n_){
            n = 1;
            while(n < n_) n *= 2;
            rep(i,2 * n){
                dat[i] = dat_lazy[i] = "";
            }
        }

        string query(int a, int b){
            return query(a,b,1,0,n);
        }
        void update(int s, int t, string x){
            update(s, t, 1, 0, n, x);
        }
        void update(int i, string x){
            update(i, i + 1, 1, 0, n, x);
        }
        string get(int a){ return query(a, a + 1); };
        void print(){
            range(i,1,n - 1){
                evaluate(i);
                cout << dat[i] << endl;
            }
        }
};

int main(){
    int n, q;
    string s;
    cin >> n >> s >> q;

    rangeUpdateQuery seg;
    seg.init(n);
    rep(i,n) {
        string x = "";
        x += s[i];
        seg.update(i + 1, x);
        //show(seg.query(1, n + 1));
    }
    //seg.print();

    rep(i,q){
        string com;
        cin >> com;
        if(com == "comp"){
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            string s = seg.query(a, b + 1);
            string t = seg.query(c, d + 1);
            //cout << s << ' ' << t << endl;
            if(s < t) cout << 's' << endl;
            else if(s > t) cout << 't' << endl;
            else cout << 'e' << endl;
        }else{
            int a, b;
            string c;
            cin >> a >> b >> c;
            seg.update(a, b + 1, c);
        }
    }
}
