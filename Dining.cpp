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

const int MAX_V = 11000;

class Edge{
    public:
        int to, cap, rev;
        Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};

class Flow{
    private:
        vector<Edge> G[MAX_V];
        bool used[MAX_V];
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
    public:
        void addEdge(int from, int to, int cap){
            G[from].push_back(Edge(to, cap, static_cast<int>(G[to].size())));
            G[to].push_back(Edge(from, 0, static_cast<int>(G[from].size() - 1)));
        }
        int maxFlow(int s, int t){
            int flow = 0;
            while(true){
                memset(used, 0, sizeof(used));
                int f = dfs(s, t, INF);
                if(f == 0) return flow;
                flow += f;
            }
        }
};

int main(){
    /*[0,food) food
     *[food, food + drink) drink
     *[food + drink, food + drink + cow) food - cow
     *[food + drink + cow, food + drink + cow + cow) cow - drink
     *sink  = food  + drink + cow + cow + 1
     *source = food + drink + cow + cow + 2
     */
    Flow f;
    int n, food, drink;
    scanf("%d%d%d",&n,&food,&drink);

    int cow = food + drink;
    int s = cow * 3 + 1;
    int t = cow * 3 + 2;
    rep(i,food) f.addEdge(s,i,1);
    rep(i,drink) f.addEdge(food + i,t,1);
    rep(i,n) f.addEdge(cow + i, cow * 2 + i, 1);
    rep(i,n){
        int a,b;
        scanf("%d%d",&a,&b);
        rep(j,a){
            int x;
            scanf("%d",&x);
            f.addEdge(x - 1, i + cow,1);
        }
        rep(j,b){
            int x;
            scanf("%d",&x);
            f.addEdge(i + cow + cow, x - 1 + food, 1);
        }
    }
    cout << f.maxFlow(s,t) << endl;
}
