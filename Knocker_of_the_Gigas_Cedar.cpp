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

int main(){
	int d, n;
	while(cin >> d >> n, d||n){
		vector<int> a(n), e(n), r(n);
		rep(i,n){
			cin >> a[i] >> e[i] >> r[i];
		}

		const int INF = 100000;

		vector<vector<int>> dp(1000, vector<int>(1000, INF));
		dp[d][0] = 0;
		for(int i = d; i >= 0; i--){
			rep(j,101){
				rep(k,n){
					if(dp[i][j] == INF) continue;
					if(r[k] > j) continue;
					int y = max(i - a[k], 0);
					int x = min(100, j + e[k]);
					dp[y][x] = min(dp[y][x], dp[i][j] + 1);
				}
			}
		}

		int ans = INF;
		rep(i,101){
			ans = min(ans, dp[0][i]);
		}

		if(ans == INF){
			cout << "NA" << endl;
		}else{
			cout << ans << endl;
		}
	}
}
