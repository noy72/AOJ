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

template <typename X, typename T>
auto vectors(X x, T a) {
	return vector<T>(x, a);
}

template <typename X, typename Y, typename Z, typename... Zs>
auto vectors(X x, Y y, Z z, Zs... zs) {
	auto cont = vectors(y, z, zs...);
	return vector<decltype(cont)>(x, cont);
}

const long long M = 1000000007;
long long dp[55][21][2][2][26];

long long solve(int i, string& pre, string& cur, string& nxt){
	rep(j,20) rep(k,2) rep(l,2) rep(m,26) {
		if(cur[i] == '?'){
			int lower = j ? 0 : (pre[i] - 'a');
			int upper = k ? 26 : (nxt[i] - 'a');
			range(d, lower, upper + 1){
				(dp[i + 1][j or d > (pre[i] - 'a')][k or d < (nxt[i] - 'a')]
				 += dp[i][j][k]) %= M;
			}
		}else{
			(dp[i + 1][j or cur[i] > pre[i]][k or cur[i] < nxt[i]]
			 += dp[i][j][k]) %= M;
		}
	}

	cout << dp[20][1][1] << endl;
	return dp[20][1][1];
}

int main(){
	int n;
	cin >> n;

	vector<string> s(n + 2);
	s[0] = "aaaaaaaaaaaaaaaaaaaa";
	rep(i,n){
		cin >> s[i + 1];
		while(s[i + 1].size() <= 20) s[i + 1] += ('a' - 1);
	}
	s[n + 1] = "zzzzzzzzzzzzzzzzzzzz";

	long long ans = 1;
	range(i,1,n + 1){
		(ans *= solve(int i, s[i - 1], s[i], s[i + 1])) %= M;
	}
	cout << ans << endl;
}
