#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

struct Edge{
    int d, e;
};

const int N = 105;
Edge M[N][N];
bool can_use[N][N];
int n, m, l;

void bfs(int n){
    int dis[N]; //距離
    queue<int> q; //訪問した点を入れる
    rep(i,N) dis[i] = 0;

    dis[0] = l;
    q.push(0);

    int u;
    while(!q.empty()){
        u = q.front(); q.pop();
        rep(v,n){
            if(dis[v] <= dis[u] - M[u][v].d && dis[u] - M[u][v].d >= 0){
                dis[v] = dis[u] - M[u][v].d; //グラフの深さ 
                can_use[u][v] = true;
                cout << u << ' ' << v << endl;
                q.push(v);
            }
        }
    }
}

int bfs_(int n){
    int dis[N];
    queue<int> q;
    rep(i,N) dis[i] = INF;

    dis[0] = 0;
    q.push(0);

    int u;
    while(not q.empty()){
        u = q.front(); q.pop();
        rep(v,n){
            if(dis[v] > dis[u] + (can_use[u][v] ? 0 : M[u][v].e)){
                dis[v] = dis[u] + (can_use[u][v] ? 0 : M[u][v].e);
                q.push(v);
            }
        }
    }
    return dis[n - 1];
}

const int MAX_V = 105;

void init(int m[MAX_V][MAX_V]){
    rep(i,MAX_V) rep(j,MAX_V) m[i][j] = INF;
    rep(i,MAX_V) m[i][i] = 0;
}

void warshallFloyd(){
    int node[105][MAX_V];
    rep(i,105) rep(j,MAX_V) node[i][j] = INF;
    node[l][0] = 0;

    for(int o = l; o >= 0; o--){
        bool loop = true;
        while(loop){
            loop = false;
            rep(i,n){
                rep(j,n){
                    int tmp = o - M[i][j].d;
                    if(tmp >= 0){
                        if(node[tmp][j] > node[o][i]){
                            node[tmp][j] = node[o][i];
                            loop = true;
                        }
                    }
                    if(node[o][j] > node[o][i] + M[i][j].e){
                        node[o][j] = node[o][i] + M[i][j].e;
                        loop = true;
                    }
                }
            }
        }
        //rep(i,n){ show(node[o][i]) } cout << endl;
    }
    //cout << endl;

    int mini = INF;
    rep(i,l + 1){
        mini = min(mini, node[i][n - 1]);
    }
    cout << mini << endl;
    return;
}

int main(){
    while(cin >> n >> m >> l,n){
        rep(i,N) rep(j,N) M[i][j] = Edge{INF,INF};
        memset(can_use, 0, sizeof(can_use));
        rep(i,m){
            int a, b, d, e;
            cin >> a >> b >> d >> e;
            a--; b--;
            M[a][b] = Edge{d,e};
            M[b][a] = Edge{d,e};
        }
        warshallFloyd();
        //bfs(n);
        //cout << bfs_(n) << endl;
    }


}
