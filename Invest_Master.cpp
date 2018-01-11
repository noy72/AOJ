#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

struct data{
    int a, b;
    double c;
    bool operator > (const data &right) const{
        return c > right.c;
    }
};

int requireProfit(int i, int j, int d, int x, int p[16][16]){
    vector<data> v;
    rep(k,d){
        v.emplace_back(data{p[j][k], p[i][k], static_cast<double>(p[i][k]) / p[j][k]});
    }
    sort(all(v), greater<data>());

    //上限がx、品物の価値が最大になるようにとる
    int dp[100005] = {0};
    memset(dp,-1,sizeof(dp));
    dp[0] = 0;
    //int c[100005] = {0};
    rep(k,d){
        if(v[k].c <= 1.0) continue;
        //show(k);
        for(int l = v[k].a; l <= x; l++){
            if(dp[l - v[k].a] == -1) continue;

            if(dp[l] < dp[l - v[k].a] + v[k].b){
                dp[l] = dp[l - v[k].a] + v[k].b;
            }else{
                dp[l] = dp[l];
            }
        }
    }
    int res = 0;
    rep(i,x + 1){
        res = max(res, dp[i] + x - i);
    }
    return res;
}

int main(){
    int n, d, x;
    cin >> d >> n >> x;

    int p[16][16];
    rep(i,n){
        rep(j,d){
            cin >> p[i][j];
        }
    }

    int dp[16] = {0};
    dp[0] = x;
    rep(i,n){
        rep(j,i){
            //cout << i << ' ' << j << endl;
            dp[i] = max(dp[i], requireProfit(i,j,d,dp[j],p));
        }
    }
    cout << dp[n - 1] << endl;
}
