
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

const int MAX_V = 10000;

vector<int> g[MAX_V]; //グラフ
vector<int> rg[MAX_V]; //辺が逆になったグラフ
vector<int> vs; //帰りがけ順の並び
bool used[MAX_V];
int cmp[MAX_V]; //属する強連結成分のトポロジカル順序

void addEdge(int from, int to){
    g[from].push_back(to);
    rg[to].push_back(from);
}

void dfs(int v){
    used[v] = true;
    rep(i,g[v].size()){
        if(not used[g[v][i]]) dfs(g[v][i]);
    }
    vs.push_back(v);
}

void rdfs(int v, int k){
    used[v] = true;
    cmp[v] = k;
    rep(i,rg[v].size()){
        if(not used[rg[v][i]]) rdfs(rg[v][i], k);
    }
}

int scc(int v){
    memset(used, 0, sizeof(used));
    vs.clear();
    rep(i,v){
        if(not used[i]) dfs(i);
    }
    memset(used, 0, sizeof(used));
    int k = 0;
    for(int i = vs.size() - 1; i >= 0; i--){
        if(not used[vs[i]]) rdfs(vs[i], k++);
    }
    return k;
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    rep(i,m){
        int a, b;
        scanf("%d%d",&a,&b);
        a--; b--;
        addEdge(a,b);
    }
    int v = scc(n);

    int u = 0, num = 0;
    rep(i,n){
        if(cmp[i] == v - 1){
            u = i;
            num++;
        }
    }

    memset(used, 0, sizeof(used));
    rdfs(u, 0);
    rep(i,n){
        if(not used[i]){
            num = 0;
            break;
        }
    }
    printf("%d\n",num);
}
