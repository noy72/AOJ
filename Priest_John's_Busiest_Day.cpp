
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

typedef struct{
    int s,t,d;
}Input;

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
    int n;
    scanf("%d",&n);

    Input p[1005];
    rep(i,n){
        int h,m;
        scanf("%d%*c%d",&h,&m);
        p[i].s = h * 60 + m;
        scanf("%d%*c%d",&h,&m);
        p[i].t = h * 60 + m;
        scanf("%d",&p[i].d);
    }

    rep(i,n){
        rep(j,i){
            if(min(p[i].s + p[i].d, p[j].s + p[j].d) > max(p[i].s, p[j].s)){
                addEdge(i,j + n);
                addEdge(j,i + n);
            }
            if(min(p[i].s + p[i].d, p[j].t) > max(p[i].s, p[j].t - p[j].d)){
                addEdge(i,j);
                addEdge(j + n, i + n);
            }
            if(min(p[i].t, p[j].s + p[j].d) > max(p[i].t - p[i].d, p[j].s)){
                addEdge(i + n, j + n);
                addEdge(j,i);
            }
            if(min(p[i].t, p[j].t) > max(p[i].t - p[i].d, p[j].t - p[j].d)){
                addEdge(i + n, j);
                addEdge(j + n, i);
            }
        }
    }
    scc(n * 2);

    rep(i,n){
        if(cmp[i] == cmp[i + n]){
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    rep(i,n){
        if(cmp[i] > cmp[n + i]){
            printf("%02d:%02d %02d:%02d\n", p[i].s / 60, p[i].s % 60, (p[i].s + p[i].d) / 60, (p[i].s + p[i].d) % 60);
        }else{
            printf("%02d:%02d %02d:%02d\n", (p[i].t - p[i].d) / 60, (p[i].t - p[i].d) % 60, p[i].t / 60, p[i].t % 60);
        }
    }
}
