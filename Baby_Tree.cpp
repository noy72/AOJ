#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int main(){
    int n,m;
    while(cin >> n >> m,n){
        double table[105][105];
        rep(i,n){
            rep(j,n){
                cin >> table[i][j];
            }
        }

        double dp[105][105] = {{0}}; //最後に与えた肥料、日にち
        rep(i,105) dp[i][0] = 1;
        range(i,1,m){
            rep(j,n){
                rep(k,n){
                    dp[j][i] = max(dp[j][i], dp[k][i - 1] * table[k][j]);
                }
            }
        }
        
        double maxi = 0;
        rep(i,n){
            maxi = max(maxi, dp[i][m - 1]);
        }
        cout <<fixed << setprecision(2) << maxi << endl;
    }
}
