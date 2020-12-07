#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

template<typename T>
ostream& operator << (ostream& os, vector<T>& v){
	rep(i,v.size()){ os << v[i] << (i == v.size() - 1 ? "" : " "); } return os;
}
template<typename T>
istream& operator >> (istream& is, vector<T>& v){
	for(T& x: v){ is >> x; } return is;
}

const int MAX_N = 200000;

template <typename T>
class BIT{
	private:
		vector<T> bit; //[1, n]
	public:
		BIT(){
			bit = vector<T>(MAX_N + 1, 0);
		}
		T sum(int i, long long m){
			if(i == 0) return 0;
			assert(1 <= i and i <= MAX_N and "invalid argument");
			T s = 0;
			while(i > 0){
				(s += bit[i]) %= m;
				i -= i & -i;
			}
			return s;
		}

		void add(int i, int x, long long m){
			assert(1 <= i and i <= MAX_N and "invalid argument");
			while(i <= MAX_N){
				(bit[i] += x) %= m;
				//bit[i] = max(bit[i], x);
				i += i & - i;
			}
		}
};

int main(){
	long long a, b, m;
	while(cin >> a >> b >> m, a||b||m){
		vector<pair<string, int>> p;
		range(i,a,b + 1){
			p.emplace_back(to_string(i), i - a);
		}
		sort(all(p));

		vector<int> ma(p.size());
		rep(i,p.size()){
			ma[ p[i].second ] = i;
		}

		//cout << ma << endl;

		BIT<long long> bit;
		long long ans = 0;
		for(int i = b; i >= a; i--){
			long long t = (bit.sum(MAX_N, m) - bit.sum( ma[i - a] , m) + m) % m + 1;
			t %= m;
			(ans += t) %= m;
			bit.add(ma[i - a] + 1, t, m);
		}
		cout << ans << endl;
	}
}
