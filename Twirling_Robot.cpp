#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int INF = 1e8;

int m[33][33];
map<char,vector<vector<int>>> c;

/*
0: 「直進」命令
1: 「右折」命令
2: 「反転」命令
3: 「左折」命令
4: 「停止」命令
*/

struct Point{ int x, y; };
int dy[5] = {-1,0,1,0,-100}, dx[5] = {0,1,0,-1,-100};
char ch[5] = "nwse";
int mc[4];
int h, w;
int limit;

int direction(int com, char dis){
    if(com == 4) return com;
    if(dis == 'n') return com;
    else if(dis == 'w') return (com + 1) % 4;
    else if(dis == 's') return (com + 2) % 4;
    else if(dis == 'e') return (com + 3) % 4;
    return -1;
}

void dfs(int y, int x, char dis, int cost, int k){
    //cout << y << ' ' << x << endl;
    //show(m[y][x])
    //    show(dis)
    //if(k > w * h) return;
    if(cost > limit) return;

    rep(i,4){
        int p = direction(i,dis);
        int ny = y + dy[p];
        int nx = x + dx[p];
        int next_cost = cost + (i == m[y][x] ? 0 : mc[i]);

        if(nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
        if(c[ch[p]][ny][nx] <= next_cost) continue;
        c[ch[p]][ny][nx] = next_cost;
        dfs(ny,nx,ch[p], next_cost, k + 1);
    }
}

int main(){
    while(scanf("%d%d",&w,&h),h){
        rep(k,4) c[ ch[k] ] = vector<vector<int>>(33,vector<int>(33));
        rep(k,4) rep(i,h) rep(j,w) c[ch[k]][i][j] = INF;
        c['w'][0][0] = 0;

        rep(i,h) rep(j,w) scanf("%d",&m[i][j]);
        rep(i,4) scanf("%d",&mc[i]);
        limit = mc[0] * (h + w) + min(mc[1],mc[3]);

        dfs(0, 0, 'w', 0, 0);

        //rep(i,h){ rep(j,w){ cout << c['w'][i][j] << ' '; } cout << endl; }

        int mini = INF;
        rep(i,4) mini = min(mini, c[ch[i]][h - 1][w - 1]);
        cout << mini << endl;
    }
}
