#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int INF = 1e8;

typedef vector<int> vi;
typedef vector<vi> vvi;

const int dy[16] = { 2, 1, 0,-1,-2, 1, 0,-1, 0};
const int dx[16] = { 1, 1, 1, 1, 1, 2, 2, 2, 3};

map<char, vvi> cost;

char m[71][71];
int w, h;

struct Data{
    char ft;
    int y, x;
};

void dfs(Data s){

    queue<Data> q;
    q.push(s);

    while(not q.empty()){
        // cout << endl;
        // rep(i,h){ rep(j,w){ cout << cost['R'][i][j] << ' ' ; } cout << endl; }
        // cout << endl;
        // rep(i,h){ rep(j,w){ cout << cost['L'][i][j] << ' ' ; } cout << endl; }
        // cout << endl;
        struct Data u = q.front(); q.pop();
        char nft = (u.ft == 'L' ? 'R' : 'L');
        rep(i,9){
            int ny = u.y + dy[i];
            int nx = u.x + dx[i] * (nft == 'R' ? 1 : -1);
            if(ny < 0 || ny >= h || nx < 0 || nx >= w) continue;
            if(m[ny][nx] == 'X' || m[ny][nx] == 'S') continue;
            if(m[ny][nx] == 'T'){
                //show(cost[u.ft][u.y][u.x])
                cost[nft][ny][nx] = min(cost[nft][ny][nx], cost[u.ft][u.y][u.x]);
                continue;
            }
            if(cost[u.ft][u.y][u.x] + (m[ny][nx] - '0') < cost[nft][ny][nx]){
                cost[nft][ny][nx] = cost[u.ft][u.y][u.x] + (m[ny][nx] - '0');
                q.push(Data{nft,ny,nx});
            }
        }
    }
}

int main(){
    while(cin >> w >> h, w){
        cost['R'] = vvi(71, vi(71,INF));
        cost['L'] = vvi(71, vi(71,INF));

        rep(i,h) rep(j,w) cin >> m[i][j];

        rep(i,w) if(m[h - 1][i] == 'S'){
            cost['R'][h - 1][i] = 0;
            dfs(Data{'R', h - 1, i});
            cost['L'][h - 1][i] = 0;
            dfs(Data{'L', h - 1, i});
        }

        int mini = INF;
        rep(i,w){
            int tmp = INF;
            if(m[0][i] == 'T') tmp = min(cost['R'][0][i], cost['L'][0][i]);
            mini = min(mini, tmp);
        }
        cout << (mini == INF ? -1 : mini) << endl;
    }
}
