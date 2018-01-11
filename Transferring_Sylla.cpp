#include <iostream>
#include <vector>
#include <cstdio>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
using namespace std;

const int INF = 4;
const int MAX_V = 1002;

class Edge{
    public:
    int to, cap, rev;
    Edge(int to, int cap, int rev) :to(to), cap(cap), rev(rev){}
};

typedef vector<vector<Edge>> AdjList;
static AdjList G(MAX_V);
static bool used[MAX_V];

void addEdge(int from, int to, int cap){
    G[from].push_back(Edge(to, cap, int(G[to].size())));
    G[to].push_back(Edge(from, 0, int(G[from].size()) - 1));
}

int dfs(int v, int t, int f){
    if(v == t) return f;
    used[v] = true;
    rep(i,G[v].size()){
        Edge &e = G[v][i];
        if(not used[e.to] && e.cap > 0){
            int d = dfs(e.to, t, min(f, e.cap));
            if(d > 0){
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t){
    int flow = 0;
    while(true){
        memset(used, 0, sizeof(used));
        int f = dfs(s, t, INF);
        if(f == 0) return flow / INF + flow % INF;
        flow += f;
    }
}

bool check(int n){
    AdjList tmp = G;
    rep(i,n){
        rep(j,n){
            if(i == j) continue;
            if(maxFlow(i + n,j) < 3) return 0;
            G = tmp;
        }
    }
    return 1;
}

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m),n||m){
        G = AdjList(1005);
        rep(i,n) addEdge(i,i + n,1);
        rep(i,m){
            int a,b;
            scanf("%d%d",&a,&b);
            addEdge(a + n,b,INF);
            addEdge(b + n,a,INF);
        }
        puts(check(n) ? "YES" : "NO");
    }
}
