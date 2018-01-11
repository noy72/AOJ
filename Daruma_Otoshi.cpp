#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

bool check(int a, int b){
	return abs(a - b) <= 1;
}

int main(){
    int n;
    while(cin >> n,n){
        vector<int> w(n);
        rep(i,n){
            cin >> w[i];
        }

		int dp[300][300] = {{0}};
		range(W,2,n + 1){
			rep(i,n){
				int j = i + W - 1;
				if(i + W - 1 >= 300) break;
				if(check(w[i], w[j]) && dp[i + 1][j - 1] == W - 2){
					dp[i][j] = W;
				}
				range(k,i,j){
					dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
				}
			}
		}
		cout << dp[0][n - 1] << endl;
    }
}
