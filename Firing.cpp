
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
#include <ostream>
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
const long long INF = static_cast<long long>(1.05e18);
using namespace std;

const long long MAX_V = 5005;

class Edge{
    public:
        int to;
        long long cap;
        int rev;
};

vector<Edge> G[MAX_V];
bool used[MAX_V];

void addEdge(int from, int to, long long cap){
    Edge a = {to, cap, static_cast<int>(G[to].size())};
    Edge b = {from, 0, static_cast<int>(G[from].size()) - 1};
    G[from].push_back(a);
    G[to].push_back(b);
}

long long dfs(int v, int t, long long f){
    if(v == t) return f;
    used[v] = true;
    rep(i,G[v].size()){
        Edge &e = G[v][i];
        if(not used[e.to] && e.cap > 0){
            long long d = dfs(e.to, t, min(f, e.cap));
            if(d > 0){
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

long long maxFlow(int s, int t){
    long long flow = 0;
    while(true){
        memset(used, 0, sizeof(used));
        long long f = dfs(s, t, INF);
        if(f == 0) return flow;
        flow += f;
    }
}

void countNode(int current){
    used[current] = true;
    rep(i,G[current].size()){
        if(G[current][i].cap > 0 && not used[G[current][i].to]){
            countNode(G[current][i].to);
        }
    }
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    const int source = n, sink = n + 1;
    long long c[MAX_V];
    rep(i,n){
        scanf("%lld",&c[i]);
        if(c[i] > 0) addEdge(source, i, c[i]);
        else if(c[i] < 0) addEdge(i,sink, -c[i]);
    }
    rep(i,m){
        int a, b;
        scanf("%d%d",&a,&b);
        a--; b--;
        addEdge(a,b,INF);
    }

    maxFlow(source,sink);
    memset(used, 0,sizeof(used));
    countNode(source);
    long long sum = 0,cnt = 0;
    rep(i,n){
        if(used[i]){
            sum += c[i];
            cnt++;
        }
    }
    printf("%lld %lld\n",cnt,sum);
}
