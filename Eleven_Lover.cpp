#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int dp[80005][11];

int main(){
	string s;
	while(cin >> s, s[0] != '0'){
		memset(dp, 0, sizeof(dp));
		//dp[0][0] = 1;
		rep(i,s.size()) {
			int d = s[i] - '0';
			if(d) dp[i + 1][d]++;
			rep(j,11) {
				dp[i + 1][(j * 10 + d) % 11] += dp[i][j];
			}
		}

		int sum = 0;
		range(i,1,s.size() + 1) sum += dp[i][0];
		cout << sum << endl;
	}
}
