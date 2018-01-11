
#include <assert.h>
#include <algorithm>
#include <complex>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <list>
#include <map>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
const int INF = 100000000;
using namespace std;


const int MAX_V = 205;

class Edge{
    public:
        //行き先、容量、コスト、逆辺
        int to, cap, cost, rev;
        Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev){}
};

vector<vector<Edge>> G(MAX_V);
int h[MAX_V]; //ポテンシャル
int dist[MAX_V]; //最短距離
int prev_v[MAX_V], prev_e[MAX_V]; //直前の頂点と辺

void addEdge(int from, int to, int cap, int cost){
    G[from].push_back(Edge(to, cap, cost, static_cast<int>(G[to].size())));
    G[to].push_back(Edge(from, 0, -cost, static_cast<int>(G[from].size() - 1)));
}

int minCostFlow(int v, int s, int t, int f){
    int res = 0;
    fill(h, h + v, 0);
    while(f > 0){
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        fill(dist, dist + v, INF);
        dist[s] = 0;
        q.push(make_pair(0, s));
        while(not q.empty()){
            pair<int, int> p = q.top(); q.pop();
            int u = p.second;
            if(dist[u] < p.first) continue;
            rep(i,G[u].size()){
                Edge &e = G[u][i];
                if(e.cap > 0 && dist[e.to] > dist[u] + e.cost + h[u] - h[e.to]){
                    dist[e.to] = dist[u] + e.cost + h[u] - h[e.to];
                    prev_v[e.to] = u;
                    prev_e[e.to] = i;
                    q.push(make_pair(dist[e.to], e.to));
                }
            }
        }
        if(dist[t] == INF){
            return -1;
        }
        rep(i,v) h[i] += dist[i];

        int d = f;
        for(int u = t; u != s; u = prev_v[u]){
            d = min(d, G[prev_v[u]][prev_e[u]].cap);
        }
        f -= d;
        res += d * h[t];
        for(int u = t; u != s; u = prev_v[u]){
            Edge &e = G[prev_v[u]][prev_e[u]];
            e.cap -= d;
            G[u][e.rev].cap += d;
        }
    }
    return res;
}

typedef struct {
    int x, y, c;
} ppi;

int main(){
    int n,m;
    scanf("%d%d",&n,&m);

    int s = n + m, t = n + m + 1;
    ppi bu[MAX_V], sh[MAX_V];
    int plan[MAX_V][MAX_V] = {0};
    rep(i,n) scanf("%d%d%d",&bu[i].x,&bu[i].y,&bu[i].c);
    rep(i,m) scanf("%d%d%d",&sh[i].x,&sh[i].y,&sh[i].c);

    rep(i,n) rep(j,m) scanf("%d",&plan[i][j]);

    int cost = 0;
    rep(i,n){
        rep(j,m){
            int dis = abs(bu[i].x - sh[j].x) + abs(bu[i].y - sh[j].y) + 1;
            addEdge(i,j + n,INF,dis);
            cost += plan[i][j] * dis;
        }
    }

    int total_flow = 0;
    rep(i,n){
        addEdge(s,i,bu[i].c,0);
        total_flow += bu[i].c;
    }
    rep(i,m){
        addEdge(n + i,t,sh[i].c,0);
    }
    if(minCostFlow(t + 1, s, t, total_flow) < cost){
        printf("SUBOPTIMAL\n");
        rep(i,n){
            rep(j,m){
                printf("%d%c", G[n + j][i].cap, j + 1 == m ? '\n' : ' ');
            }
        }
    }else{
        printf("OPTIMAL\n");
    }
}
