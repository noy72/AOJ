#include<iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cassert>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
using namespace std;

const int INF = 2000000000;
const int MAX_V = 21000;

class Edge{
    public:
        int to, cap, rev;
        Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};

class Flow{
    private:
        vector<Edge> G[MAX_V];
        bool used[MAX_V];
        int match[MAX_V];
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
        bool dfs(int v){
            used[v] = true;
            rep(i,G[v].size()){
                int u = G[v][i].to, w = match[u];
                if(w < 0 || (not used[w] && dfs(w))){
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
            return false;
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
        /*
        int bipartite_matching(int n){
            int res = 0;
            memset(match, -1, sizeof(match));
            rep(i,n){
                memset(used, 0, sizeof(used));
                if(dfs(i)){
                    res++;
                }
            }
            return res;
        }
        */
        void bipartite_matching(int n, int m, int d, int p){
            int res = 0;
            memset(match, -1, sizeof(match));
            rep(i,n * m * d){
                memset(used, 0, sizeof(used));
                if(dfs(i)){
                    if(++res == p){
                        printf("%d\n", i / d + 1);
                        return;
                    }
                }
            }
            printf("impossible\n");
        }
};

struct Point{ int x, y; };
int dy[4] = {0,1,0,-1}, dx[4] = {1,0,-1,0};
int dis[15][15][15][15];

void bfs(int h, int w, Point p, int dis[15][15], char M[15][15]){
    queue<Point> q;

    dis[p.y][p.x] = 0;
    q.push(p);

    Point u;
    while(not q.empty()){
        u = q.front(); q.pop();
        rep(i,4){
            Point next;
            next.x = u.x + dx[i];
            next.y = u.y + dy[i];
            if(next.x < 0 || next.x >= w || next.y < 0 || next.y >= h) continue;
            if(dis[next.y][next.x] == -1 && M[next.y][next.x] == '.'){

                dis[next.y][next.x] = dis[u.y][u.x] + 1;
                q.push(next);
            }
        }
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,m;
        scanf("%d%d",&n,&m);

        char a[15][15];
        rep(i,n) scanf("%s",a[i]);

        vector<Point> door(15 * 15);
        vector<Point> person(15 * 15);
        memset(dis, -1, sizeof(dis));
        Flow f;
        rep(i,n){
            rep(j,m){
                if(a[i][j] == 'D'){
                    door.push_back(Point{j,i});
                    bfs(n,m,Point{j,i},dis[i][j],a);
                }else if(a[i][j] == '.'){
                    person.push_back(Point{j,i});
                }
            }
        }


        int d = door.size(), p = person.size();
        rep(i,p){
            rep(j,d){
                int tmp = dis[ door[j].y ][ door[j].x ][ person[i].y ][ person[i].x ];
                if(tmp >= 0){
                    for(int k = tmp; k <= n * m; k++){
                        f.addEdge((k - 1) * d + i, n * m * d + j, 1);
                    }
                }
            }
        }

        if(p == 0){
            printf("0\n");
            continue;
        }

        f.bipartite_matching(n,m,d,p);
    }
}
