#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int INF = 100000000;

struct Data{
    int xa, xi, ya, yi;
};

int h, w;

const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

void dfs(char m[55][55], bool used[55][55], Data &d, int y, int x, char a){
    d.xa = max(d.xa, x);
    d.xi = min(d.xi, x);
    d.ya = max(d.ya, y);
    d.yi = min(d.yi, y);
    used[y][x] = true;

    rep(i,4){
        int ny = y + dy[i];
        int nx = x + dx[i];
        if(y >= h || y < 0 || x >= w || x < 0) continue;
        if(m[ny][nx] != a) continue;
        if(used[ny][nx] == true) continue;
        dfs(m,used,d,ny,nx,a);
    }
}

bool isRect(char m[55][55], Data d, char a){
    range(i,d.yi,d.ya + 1){
        range(j,d.xi,d.xa + 1){
            if(m[i][j] != a && m[i][j] != '@') return false;
        }
    }
    return true;
}

bool check(char m[55][55]){
    rep(i,h){
        rep(j,w){
            if(m[i][j] >= 'A' && m[i][j] <= 'Z') return false;
        }
    }
    return true;
}

bool replace(char m[55][55], Data d){
    //cout << d.yi << ' ' << d.ya << endl;
    range(i,d.yi,d.ya + 1){
        range(j,d.xi,d.xa + 1){
            m[i][j] = '@';
        }
    }
   //cout << endl; rep(i,h){ rep(j,w){ cout << m[i][j]; } cout << endl; }
    return true;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        cin >> h >> w;

        char m[55][55];
        rep(i,h) cin >> m[i];

        while(true){
            bool f = false;
            bool used[55][55] = {0};
            rep(i,h){
                rep(j,w){
                    if(m[i][j] != '.' && m[i][j] != '@' && used[i][j] == false){
                        Data d = {-INF,INF,-INF,INF};
                        //dfs(m,used,d,i,j,m[i][j]);
                        rep(I,h){
                            rep(J,w){
                                if(m[I][J] == m[i][j]){
                                    d.xa = max(d.xa, J);
                                    d.xi = min(d.xi, J);
                                    d.ya = max(d.ya, I);
                                    d.yi = min(d.yi, I);
                                }
                            }
                        }
                        //cout << i << ' ' << j << endl;
                        //cout << d.yi << ' ' << d.ya << endl;
                        //cout << d.xi << ' ' << d.xa << endl;
                        if(isRect(m,d,m[i][j])) f = replace(m,d);
                    }
                }
            }
            if(not f){
                break;
            }
        }
        cout << (check(m) ? "SAFE" : "SUSPICIOUS") << endl;
    }
}
