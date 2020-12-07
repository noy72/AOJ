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

#define int long long

const long long M = 1000000007;

//x^n mod M
typedef long long ull;
ull power(ull x, ull n){
	ull res = 1;
	if(n > 0){
		res = power(x, n / 2);
		if(n % 2 == 0) res = (res * res) % M;
		else res = (((res * res) % M) * x ) % M;
	}
	return res;
}

long long combination(long long n, long long r){
	long long res = 1;
	for(long long i = n, j = 0; j < r; i--, j++){
		(res *= i) %= M;
	}
	range(i,1,r + 1){
		(res *= power(static_cast<long long>(i), M - 2)) %= M;
	}
	return res % M;
}

signed main(){
	long long n, d, x;
	while(cin >> n >> d >> x, n||d||x){
		vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
		dp[0][0] = 1;
		vector<long long> sum(n + 1, 0);
		rep(i,n){
			range(j,i,n + 1){
				if(j - x >= 0){
					(dp[i + 1][j] += (sum[j - 1] % M - sum[j - x] % M + M) % M) %= M;
				}else{
					(dp[i + 1][j] += (i == 0 ? 1 : sum[j - 1] % M)) %= M;
				}
			}

			range(j,1,n + 1){
				sum[j] = (sum[j - 1] % M + dp[i + 1][j] % M) % M;
				//cout << sum[j]  << ' ';
			}
			//cout << endl;
		}

		//rep(i,n + 1){ rep(j,n + 1){ cout << dp[i][j] << ' '; } cout << endl; }
		long long ans = 0, com = 1;
		range(i,1,min(d,n) + 1){
			(com *= (d - i + 1) % M * power(i, M - 2) % M) %= M;
			assert(com >= 0);
			//show(com)
			(ans += dp[i][n] % M * com % M) %= M;
		}
		cout << ans << endl;
	}
}
