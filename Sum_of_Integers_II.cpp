#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int main(){
    int n, s;
    while(cin >> n >> s, n){
        long long dp[10][2005] = {{0}};
        dp[0][0] = 1;
        rep(j,101){
            for(int i = n; i >= 0; i--){
                for(int k = s; k >= 0; k--){
                    dp[i + 1][k + j] += dp[i][k];
                }
            }
        }
        cout << dp[n][s] << endl;
    }
}
