
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

const int MAX_N = 210000;
const int MAX_V = 210000;

struct Edge{
    int to,cost;
};
vector<Edge> tree[MAX_N / 2];

class BIT{
    private:
        int bit[MAX_N + 1] = {0};
    public:
        int sum(int i){
            int s = 0;
            while(i > 0){
                s += bit[i];
                i -= i & -i;
            }
            return s;
        }
        void add(int i, int x, int n){
            while(i <= MAX_N){
                bit[i] += x;
                i += i & - i;
            }
        }
};

const int MAX_LOG_V = 20;

int root;

int parent[MAX_LOG_V][MAX_V];
int depth[MAX_V];

void dfs(int v, int p, int d){
    parent[0][v] = p;
    depth[v] = d;
    rep(i,tree[v].size()){
        if(tree[v][i].to != p) dfs(tree[v][i].to, v, d + 1);
    }
}

void init(int V){
    root = 0; //ココ
    dfs(root, -1, 0);
    rep(k,MAX_LOG_V - 1){
        rep(v,V){
            if(parent[k][v] < 0) parent[k + 1][v] = -1;
            else parent[k + 1][v] = parent[k][ parent[k][v] ];
        }
    }
}

int lca(int u, int v){
    if(depth[u] > depth[v]) swap(u, v);
    rep(k,MAX_LOG_V){
        if( (depth[v] - depth[u]) >> k & 1){
            v = parent[k][v];
        }
    }
    if(u == v) return u;
    for(int k = MAX_LOG_V - 1; k >= 0; k--){
        if(parent[k][u] != parent[k][v]){
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    return parent[0][u];
}

int vs[MAX_V]; //訪問順
int id[MAX_V]; //各頂点が初めてvsに登場するインデックス
int es[MAX_V]; //辺のインデックス
void dfs_tree(int v, int p, int d, int &k){
    id[v] = k;
    vs[k] = v;
    rep(i,tree[v].size()){
        Edge &e = tree[v][i];
        if(e.to != p){
            add(k, e.cost, MAX_V);
            es[e.id * 2] = k;
            dfs(e.to, v, d + 1, k);
            vs[k] = v;
            depth[k++] = d;
            add(k, -e.cost, MAX_V);
            es[e.id * 2 + 1] = k;
        }
    }
}

int main(){
    int n, q, s;
    scanf("%d%d%d",&n,&q,&s);
    rep(i,n - 1){
        int a, b, c;
        scanf("%d%d%d",&a,&b,&c);
        a--; b--;
        tree[a].push_back((struct Edge){b,c});
        tree[b].push_back((struct Edge){a,c});
    }
    init(n);

    rep(i,q){
        int com;
        scanf("%d",&com);
        if(com){
            int a, w;
            a--;
            scanf("%d%d",&a,&w);
        }else{
            int u;
            u--;
            scanf("%d",&u);
        }
    }
}
