#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

struct Data{
    int a, b, c;
};

int main(){
    int d,n;
    cin >> d >> n;

    int dig[205];
    rep(i,d) cin >> dig[i];

    Data cl[205];
    rep(i,n) cin >> cl[i].a >> cl[i].b >> cl[i].c;

    int dp[205][205] = {{0}}; //最後に着た服、日
    memset(dp, -1, sizeof(dp));
    rep(i,n){
        if(cl[i].a <= dig[0] && dig[0] <= cl[i].b){
            dp[i][0] = 0;
        }
    }

    range(i,1,d){
        rep(j,n){
            if(cl[j].a <= dig[i] && dig[i] <= cl[j].b){
                rep(k,n){
                    if(dp[k][i - 1] == -1) continue;
                    dp[j][i] = max(dp[j][i], dp[k][i - 1] + abs(cl[k].c - cl[j].c));
                }
            }
        }
    }

    int maxi = 0;
    rep(i,n){
        maxi = max(maxi, dp[i][d - 1]);
    }
    cout << maxi << endl;
}
