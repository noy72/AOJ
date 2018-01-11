#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int N = 10;

int h, w, c;

struct Point{ int x, y; };
int dy[4] = {0,1,0,-1}, dx[4] = {1,0,-1,0};

int bfs(vector<vector<int>> &M, int color, Point p = Point{0,0}){
    int dis[N][N];
    queue<Point> q;
    rep(i,N) rep(j,N) dis[i][j] = 1e8;

    dis[p.y][p.x] = 0;
    q.push(p);

    Point u;
    int cur = M[0][0];
    int ret = 0;
    while(not q.empty()){
        u = q.front(); q.pop();
        ret++;
        M[u.y][u.x] = color;
        rep(i,4){
            Point next;
            next.x = u.x + dx[i];
            next.y = u.y + dy[i];
            if(next.x < 0 || next.x >= w || next.y < 0 || next.y >= h) continue;
            if(dis[next.y][next.x] == 1e8 && M[next.y][next.x] == cur){
                dis[next.y][next.x] = dis[u.y][u.x] + 1;
                q.push(next);
            }
        }
    }
        //cout << endl;
        //rep(i,h){ rep(j,w){ cout << M[i][j]<<' '; } cout << endl; }
    return ret;
}
int dfs(vector<vector<int>> v, int k){
    if(k == 4){
        bfs(v,c);
        return bfs(v,8);
    }

    int ret = 0;
    range(i,1,7){
        vector<vector<int>> tmp = v;
        bfs(tmp, i);
        ret = max(ret,dfs(tmp,k + 1));
    }
    return ret;
}

int main(){
    while(cin >> h >> w >> c, h){

        vector<vector<int>> v(10, vector<int>(10));
        rep(i,h){
            rep(j,w){
                cin >> v[i][j];
            }
        }

        cout << dfs(v, 0) << endl;
    }
}
