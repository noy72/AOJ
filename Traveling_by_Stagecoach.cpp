#include <bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
const double INF = 100000000;
using namespace std;

//i番目のビットを返す
bool getBit(int num, int i){
    return ((num & (1 << i)) != 0);
}

//i番目を1にする
int setBit(int num, int i){
    return num | (1 << i);
}

//i番目を0にする
int clearBit(int num, int i){
    int mask = ~(1 << i);
    return num & mask;
}

//i番目をvで置き換える
int updateBit(int num, int i, int v){
    int mask = ~(1 << i);
    return (num & mask) | (v << i);
}

int main(){
    int n, m, p, a, b;
    while(scanf("%d%d%d%d%d",&n,&m,&p,&a,&b), n){
        a--; b--;
        double g[40][40];
        rep(i,40) memset(g[i],-1,sizeof(g[i]));

        double t[10];
        rep(i,n) scanf("%lf",&t[i]);
        rep(i,p){
            int a, b;
            double c;
            scanf("%d%d%lf",&a,&b,&c);
            a--; b--;
           g[a][b] = g[b][a] = c;
        }

        double dp[500][40];
        rep(i, 1 << n) rep(j, 40) dp[i][j] = INF;
        dp[(1 << n) - 1][a] = 0;

        double ans = INF;
        for(int s = (1 << n) - 1; s >= 0; s--){
            ans = min(ans, dp[s][b]);
            rep(i,n){
                if(getBit(s,i)){
                    rep(v,m){
                        rep(u,m){
                            if(g[v][u] == -1) continue;
                            dp[clearBit(s,i)][u] = min(dp[clearBit(s,i)][u], dp[s][v] + g[v][u] / t[i]);
                        }
                    }
                }
            }
        }
        if(ans == INF){
            printf("Impossible\n");
        }else{
            printf("%.3f\n",ans);
        }
    }
}
