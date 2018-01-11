
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
const int INF = 200000000;
using namespace std;

const int MAX_V = 10005;

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

int main(){
    int n,m;
    scanf("%d%d",&n,&m);

    int s = 0, t = n - 1;
    rep(i,m){
        int a, b, c;
        scanf("%d%d%d",&a,&b,&c);
        a--; b--;
        addEdge(a,b,1,c);
        addEdge(b,a,1,c);
    }
    printf("%d\n",minCostFlow(n,s,t,2));
}
