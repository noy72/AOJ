#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
const int M = 10000;
using namespace std;

int solve(string a, int m){
    int dp[505][2][9][505][3] = {0}; //i番目まで見た、a未満である、前回の値、mod M、前回からの変化
    dp[0][0][0][0][0] = 0;
    rep(i,a.size()) rep(j,2) rep(k,9) rep(l,505) rep(o,3) {
        int lim = j ? 9 : a[i] - '0';
        switch (o) {
            case 0: //ゼロのとき
                dp[i + 1][j][k]
                break;
            default:
                
        }
        rep(d,lim){
            if(k < d) (dp[i + 1][j][k][(l + d) % m][0] += dp[i][j][k][l][1]) %= M;
            if(k > d) (dp[i + 1][j][k][(l + d) % m][1] += dp[i][j][k][l][0]) %= M;
        }
    }
    
    int ans = 0;
    rep(i,2) rep(j,9) rep(k,2) (ans += dp[a.size()][i][j][0][k]) %= M;
    return ans;
}

int main(){
    string a, b;
    int m;
    cin >> a >> b >> m;
    if(a.back() == 0){
        a.pop_back();
        char last = a.back();
        a.pop_back();
        a.push_back(static_cast<char>(last - 1));
    }
    cout << solve(b,m) - solve(a,m) << endl;
}
