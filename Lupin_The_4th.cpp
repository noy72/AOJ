#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
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

const int MAX_N = 16;
double dp[1 << MAX_N][MAX_N], speed[1 << MAX_N];
int pres[1 << MAX_N][MAX_N];

int main(){
    int n;
    cin >> n;

    int id[MAX_N], dis[MAX_N], num[MAX_N];
    rep(i,n){
        cin >> id[i] >> dis[i] >> num[i];
    }

    const int N = 1 << n;
    rep(s,N){
        int c = 0;
        rep(i,n){
            pres[s][i] = -1;
            dp[s][i] = 1e11;

            if(getBit(s,i)) c += num[i];
        }
        speed[s] = 2000.0 / (70 + 20 * c);
    }
    rep(i,n) dp[1 << i][i] = 0;

    range(s,1,N){
        rep(i,n){
            rep(j,n){ //i -> jに移動
                //出発地点に来たことがない || 行き先がすでに訪問済み
                if((not getBit(s,i) || getBit(s,j))) continue; 

                double time = dp[s][i] + abs(dis[i] - dis[j]) / speed[s];
                int next_s = setBit(s,j);
                if(dp[next_s][j] > time){
                    dp[next_s][j] = time;
                    pres[next_s][j] = i;
                }
            }
        }
    }

    int cur = 0;
    range(i,1,n){
        if(dp[N - 1][cur] > dp[N - 1][i]){
            cur = i;
        }
    }

    vector<int> v;
    int s = N - 1;
    while(cur != -1){
        v.emplace_back(id[cur]);
        int next = pres[s][cur];
        s = clearBit(s,cur);
        cur = next;
    }

    for(int i = v.size() - 1; i >= 0; i--){
        cout << v[i] << (i == 0 ? '\n' : ' ');
    }
}
