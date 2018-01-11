#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int main(){
    int n;
    while(cin >> n,n){
        vector<pair<int, int>> v;
        rep(i,n){
            int a, b;
            cin >> a >> b;
            v.emplace_back(a,b);
        }

        int dp[1005] = {0};
        dp[0] = 1;
        rep(i,n){
            for(int j = 1000; j >= 0; j--){
                range(k,1,v[i].second + 1){
                    if(j - v[i].first * k < 0) continue;
                    dp[j] += dp[j - v[i].first * k];
                }
            }
        }

        int g;
        cin >> g;
        rep(i,g){
            int k;
            cin >> k;
            cout << dp[k] << endl;
        }
    }
}
