#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

#define int long long
const int M = 1000000007;
int dp[205][10005];

signed main(){
	int n, w;
	cin >> n >> w;

	vector<int> a(n + 1, -1);
	rep(i,n) cin >> a[i + 1];
	sort(all(a));

	vector<int> sum(all(a));
	sum[0] = 0;
	range(i,1,n + 1){
		sum[i] += sum[i - 1];
	}

	dp[0][0] = 1;
	range(i,1,n + 1){ //頭から全ての荷物を入れたとき
		if(sum[i] > w) break;
		dp[0][sum[i]] = 1;
	}

	range(i,1,n + 1){ //i - 1番目の荷物を全部入れ、i 番目の荷物を入れないとき
		if(sum[i] > w) break;
		dp[i][sum[i - 1]] = 1;
		range(j,i + 1,n + 1){
			for(int k = w; k >= sum[i - 1]; k--){
				if(k + a[j] > w) continue;
				//show(k)
				(dp[i][k + a[j]] += dp[i][k]) %= M;
			}
		}
	}

	//rep(i,n + 1){ rep(j,w + 1){ cout << dp[i][j] <<' '; } cout << endl; }
	
	int ans = 0;
	range(i,1,n + 1){
		range(j,sum[i], w + 1){
			if(j + a[i] <= w) continue;
			//show(dp[i][j])
			//cout << i << ' ' << j << endl;
			(ans += dp[i][j]) %= M;
		}
	}

	cout << ans + 1 << endl; //荷物を頭から入れたときの1通り
}
