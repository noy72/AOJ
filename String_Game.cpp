#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

const int M = 1000000007;

struct RAQ{
	using T = long long;
	T operator()(const T &a, const T &b) { return 1009 * (a + b) % M; };
	static constexpr T identity() { return 0; }
};

template<class Monoid>
class rangeAddQuery{
	private:
		using T = typename Monoid::T;
		Monoid op;
		const int n;
		vector<T> dat, lazy;
		T query(int a, int b, int k, int l, int r){
			if(b <= l || r <= a) return op.identity();
			else if(a <= l && r <= b) return dat[k] * (r - l) + lazy[k];
			else{
				T res = (min(b,r) - max(a,l)) * dat[k];
				res += query(a, b, k * 2, l, (l + r) / 2);
				res += query(a, b, k * 2 + 1, (l + r) / 2, r);
				return res;
			}
		}
		void add(int a, int b, int k, int l, int r, T x){
			if(a <= l && r <= b){
				dat[k] += x;
			}else if(l < b && a < r){
				lazy[k] += (min(b,r) - max(a,l)) * x;
				add(a, b, k * 2, l, (l + r) / 2, x);
				add(a, b, k * 2 + 1, (l + r) / 2, r, x);

			}
		}
		int power(int n){
			int res = 1;
			while(n >= res) res*=2;
			return res;
		}
	public:
		rangeAddQuery(int n) : n(power(n)), dat(4 * n, op.identity()), lazy(4 * n, op.identity()) {}
		rangeAddQuery(const vector<T> &v) : n(power(v.size())), dat(4 * n), lazy(4 * n, op.identity()){
			copy(begin(v), end(v), begin(dat) + n);
			for(int i = n - 1; i > 0; i--) dat[i] = op(dat[2 * i], dat[2 * i + 1]);
		}
		T query(int a, int b){ return query(a,b,1,0,n); }
		void add(int s, int t, T x){ add(s, t, 1, 0, n, x); }
		T get(int a){ return query(a, a + 1); };
		void out(){
			rep(i,n * 2){ cout << dat[i + 1] << ' '; } cout << endl;
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
