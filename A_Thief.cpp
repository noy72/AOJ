#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int main(){
    int W;
    int cnt = 0;
    while(cin >> W,W){
        int n;
        cin >> n;

        int v[1005], w[1005];
        rep(i,n){
            char g;
            cin >> v[i] >> g >> w[i];
        }

        int dp[2005] = {0};
        rep(i,W + 1) dp[i] = -1;
        dp[0] = 0;

        rep(i,n){
            for(int j = W; j >= 0; j--){
                if(j - w[i] < 0) continue;
                if(dp[j - w[i]] == -1) continue;
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            }
        }

        int ans_v = 0, ans_w = 0;
        rep(i,W + 1){
            if(ans_v < dp[i]){
                ans_v = dp[i];
                ans_w = i;
            }
        }

        cout << "Case " << cnt + 1 << ":" << endl;
        cout << ans_v << endl;
        cout << ans_w << endl;
        cnt++;
    }
}
