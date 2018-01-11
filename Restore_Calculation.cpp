#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

const int M = 1000000007;

int main(){
    string s[3];
    while(cin >> s[0], s[0][0] != '0'){
        rep(i,2) cin >> s[i + 1];
        rep(i,3) reverse(all(s[i]));

        int n = s[0].size();
        long long dp[55][2] = {{0}};
        dp[0][0] = 1;
        rep(i,n){
            vector<int> a[3];
            rep(j,3){
                if(s[j][i] == '?'){
                    if(i == n - 1){
                        a[j] = vector<int>(9);
                        iota(all(a[j]), 1);
                    } else {
                        a[j] = vector<int>(10);
                        iota(all(a[j]), 0);
                    }
                }else{
                    a[j].emplace_back(s[j][i] - '0');
                }
            }
            for(auto j:a[0]){
                for(auto k:a[1]){
                    for(auto l:a[2]){
                        if((j + k) % 10 == l) (dp[i + 1][(j + k) / 10] += dp[i][0]) %= M;
                        if((j + k + 1) % 10 == l) (dp[i + 1][(j + k + 1) / 10] += dp[i][1]) %= M;
                    }
                }
            }
        }
        cout << dp[n][0] << endl;
    }
}
