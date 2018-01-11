#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

const int MAX_V = 105;
const int MAX_C = 22;
int charge[MAX_C][20005];
int edge[MAX_C][MAX_V][MAX_V];
int g[MAX_V][MAX_V];

void init(int m[MAX_V][MAX_V]){
    rep(i,MAX_V) rep(j,MAX_V) m[i][j] = INF;
    rep(i,MAX_V) m[i][i] = 0;
}

void warshallFloyd(int m[MAX_V][MAX_V], int n){
    rep(k,n){
        rep(i,n){
            rep(j,n){
                m[i][j] = min(m[i][j], m[i][k] + m[k][j]);
            }
        }
    }
}

void cost(int c, int n){
    init(g);
    rep(l,c){
        rep(i,n){
            rep(j,n){
                if(edge[l][i][j] == INF) continue;
                g[i][j] = min(g[i][j], charge[l][edge[l][i][j]]);
            }
        }
    }
}

void makeTable(int c){
    int p[MAX_C] = {0};
    int q[MAX_C][55] = {{0}}, r[MAX_C][55];

    rep(i,c) cin >> p[i];
    rep(i,c){
        rep(j,p[i] - 1) cin >> q[i][j + 1];
        q[i][p[i]] = 20000;
        rep(j,p[i]) cin >> r[i][j];
    }

    rep(i,c){
        rep(j,p[i]){
            for(int k = q[i][j] + 1; k <= q[i][j + 1]; k++){
                charge[i][k] = charge[i][k - 1] + r[i][j];
            }
        }
    }
    //rep(i,c){ rep(j,10){ cout << charge[i][j] << ' ' ; } cout << endl; }
}

int main(){
    int n, m, c, s, t;
    while(cin >> n >> m >> c >> s >> t,n){
        memset(charge, 0, sizeof(charge));

        s--; t--;
        rep(i,c) init(edge[i]);
        rep(i,m){
            int x, y, d, c;
            cin >> x >> y >> d >> c;
            x--; y--; c--;
            edge[c][x][y] = edge[c][y][x] = min(d,edge[c][y][x]);
        }
        rep(i,c) warshallFloyd(edge[i], n);

        makeTable(c);
        cost(c,n);
        warshallFloyd(g,m);
        //rep(i,n){ rep(j,n){ cout << g[i][j]; } cout << endl; }
        cout << (g[s][t] == INF ? -1 : g[s][t]) << endl;
    }
}
