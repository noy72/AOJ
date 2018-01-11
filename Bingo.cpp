#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int M = 100000;
int dp[2005][3005][50];//最後に使った数字、今までに使った数字の合計、今までに使った数字の個数

int main(){
    int n, m, s;
    while(cin >> n >> m >> s,n){
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        rep(i,m + 1){
            range(j,i,s + 1){
                range(l,1,n * n + 1){
                    int sum = 0;
                    rep(k,i){
                        sum += dp[k][j - i][l - 1];
                        sum %= M;
                    }
                    //cout << i << ' ' << j << endl;
                    //show(dp[i][j])
                    dp[i][j][l] = max(dp[i][j][l],dp[i][j][l - 1]);
                }
            }
        }

        int sum = 0;
        rep(i,m + 1){
            sum += dp[i][s][n * n];
            sum %= M;
        }
        cout << sum << endl;
    }
}
