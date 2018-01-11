#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

//const int INF = 1e8;
const int N = 105;

char c[N][N];
long long dist[4][N][N];
long long h, w, l;
long long to, loop;

struct Point{ int x, y; };
int dy[4] = {0,1,0,-1}, dx[4] = {1,0,-1,0};

void dfs(Point p, int dir, long long dis){
    //cout << endl;
    if(dist[dir][p.y][p.x] != -1){
        //show(p.y)
        //show(p.x)
        //show(dis)
        //show(dist[p.y][p.x])
        to = dist[dir][p.y][p.x];
        loop = dis - dist[dir][p.y][p.x];
        return;
    }
    dist[dir][p.y][p.x] = dis;

    //rep(i,h){ rep(j,w){ cout << dist[dir][i][j] << ' '; } cout << endl; }

    int ny = p.y + dy[dir];
    int nx = p.x + dx[dir];
    while( (ny < 0 || ny >= h || nx < 0 || nx >= w) || c[ny][nx] == '#'){
        dir = (dir + 1) % 4;
        ny = p.y + dy[dir];
        nx = p.x + dx[dir];
    }


    dfs(Point{nx,ny}, dir, dis + 1);
}

void dfs_(Point p, int dir, long long dis){
    //show(dir) cout << p.y << ' ' << p.x << endl;
    if(dis == 0){
        char d[5] = {"ESWN"};
        cout << p.y + 1 << ' ' << p.x + 1 << ' ' << d[dir] << endl;
        return;
    }

    int ny = p.y + dy[dir];
    int nx = p.x + dx[dir];
    while( (ny < 0 || ny >= h || nx < 0 || nx >= w) || c[ny][nx] == '#'){
        dir = (dir + 1) % 4;
        ny = p.y + dy[dir];
        nx = p.x + dx[dir];
    }
    dfs_(Point{nx,ny}, dir, dis - 1);
}

int main(){
    while(cin >> h >> w >> l,h){
        memset(dist, -1, sizeof(dist));
        int dir = -1;
        Point p = Point{-1,-1};
        rep(i,h){
            rep(j,w){
                cin >> c[i][j];
                if(c[i][j] == 'N') dir = 3;
                else if(c[i][j] == 'E') dir = 0;
                else if(c[i][j] == 'S') dir = 1;
                else if(c[i][j] == 'W') dir = 2;
                if(dir != -1 && p.x == -1){
                    p = Point{j,i};
                }
            }
        }
        dfs(p,dir,0);
        //show(to)
        //show(loop)
        if(l >= to){
            l -= to;
            l %= loop;
            l += to;
        }
        dfs_(p,dir,l);
    }
}
