#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int INF = 1e8;

const int MAX_V = 100005;

void dfs(int used[MAX_V], int cur, int g[MAX_V], int a[MAX_V], bool loop_check[MAX_V]){
    vector<int> v;
    while(true){
        //show(v.size())
        //show(cur)
        //    show(used[cur])
        if(a[cur] == 0){ //これ以上移動できない
            g[cur] = cur;
            used[cur] = 1;
            for(auto it:v){
                g[it] = cur;
                used[it] = 1;
            }
            break;
        }else if(loop_check[cur]){//HoI!!! これは閉路!!!!!
            //show("heiro")
            for(auto it:v){
                g[it] = INF;
                used[it] = 1;
            }
            break;
        }
        loop_check[cur] = true;
        v.emplace_back(cur);
        cur = cur + a[cur];
    }
}

int bfs(int n, int g[MAX_V]){
    int dis[MAX_V]; //距離
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    rep(i,MAX_V) dis[i] = INF;

    dis[0] = 0;
    q.push(make_pair(0,0));

    pair<int, int> u;
    while(!q.empty()){
        u = q.top(); q.pop();
        int c = u.second;
        for(int j = 6; j >= 1; j--){
            if(c + j >= n) continue;
            if(g[c + j] == INF) continue;
            if(dis[ g[c + j] ] > dis[c] + 1){
                dis[g[c + j]] = dis[c] + 1;
                q.push(make_pair(dis[c] + 1, g[c + j]));
            }
        }
    }
    //rep(i,n) show(dis[n])
    return dis[n - 1];
}

int main(){
    int n;
    cin >> n;
    int a[MAX_V];
    rep(i,n) cin >> a[i];

    int used[MAX_V] = {0};
    int g[MAX_V];
    rep(i,n){
        //show(i)
        bool tmp[MAX_V] = {0};
        if(used[i]) continue;
        dfs(used,i,g,a,tmp);
    }
    //rep(i,n){ cout << g[i] << endl; }

    //int dp[MAX_V];
    //rep(i,n) dp[i] = INF;
    //while(true){
    //    bool f = false;
    //    rep(i,n){
    //        range(j,1,7){
    //            if(g[i + j] == INF) continue;
    //            if(dp[ g[i + j] ] > dp[i] + 1){
    //                f = true;
    //                dp[ g[i + j] ] = dp[i] + 1;
    //            }
    //        }
    //    }
    //}

    cout << bfs(n,g) << endl;

}
