
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


const int MAX_V = 1001;

class Edge{
    public:
        //行き先、容量、コスト、逆辺
        int to, cap, cost, rev;
        Edge(int to, int cap, int cost, int rev):to(to), cap(cap), cost(cost), rev(rev){}
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
int minCostFlowBellmanFord(int V, int s, int t, int f){
    int res = 0;
    while(f > 0){
        fill(dist, dist + V, INF);
        dist[s] = 0;
        bool update = true;
        while(update){
            update = false;
            rep(v,V){
                if(dist[v] == INF) continue;
                rep(i,G[v].size()){
                    Edge &e = G[v][i];
                    if(e.cap > 0 && dist[e.to] > dist[v] + e.cost){
                        dist[e.to] = dist[v] + e.cost;
                        prev_v[e.to] = v;
                        prev_e[e.to] = i;
                        update = true;
                    }
                }
            }
        }
        if(dist[t] == INF){
            return -1;
        }

        int d = f;
        for(int v = t; v != s; v = prev_v[v]){
            d = min(d, G[prev_v[v]][prev_e[v]].cap);
        }
        f -= d;
        res += d * dist[t];
        for(int v = t; v != s; v = prev_v[v]){
            Edge &e = G[prev_v[v]][prev_e[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}

void compress(vector<int> &v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
}

int lb(vector<int> v, int num){
    return lower_bound(all(v), num) - v.begin();
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        G = vector<vector<Edge>>(MAX_V);
        int n,k;
        scanf("%d%d",&n,&k);

        int a[205], b[205], c[205];
        vector<int> x;
        rep(i,n){
            scanf("%d%d%d",&a[i],&b[i],&c[i]);
            x.push_back(a[i]);
            x.push_back(b[i]);
        }
        compress(x);

        int m = x.size();
        int s = m, t = s + 1;

        int res = 0;
        addEdge(s,0,k,0);
        addEdge(m - 1,t,k,0);
        rep(i,m - 1) addEdge(i,i + 1,INF,0);

        rep(i,n){
            int u = lb(x,a[i]);
            int v = lb(x,b[i]);
            addEdge(u,v,1,-c[i]);
            addEdge(s,u,1,0);
            addEdge(v,t,1,0);
            //res -= c[i];
        }
        //res += minCostFlowBellmanFord(t + 1,s,t,k);
        printf("%d\n",-minCostFlow(t + 1,s,t,k));
    }
}
