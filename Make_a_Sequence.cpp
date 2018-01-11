#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

void pushBall(int c[10][10][10], int top[10][10], int x, int y, int f){
    c[x][y][ top[x][y] ] = f;
    top[x][y]++;
}

void dfs(int n, int m, int x, int y, int z, int ball, int c[10][10][10], int &ans, int k, int dx, int dy, int dz){
    if(ans != -1) return;
    if(c[x][y][z] == ball) k++;
    else return;
    if(k == m){
        ans = ball;
        return;
    }

    int nx = x + dx;
    int ny = y + dy;
    int nz = z + dz;
    if(nx < 0 || nx >= n || ny < 0 || ny >= n || nz >= n || nz < 0) return;
    dfs(n,m,nx,ny,nz,ball,c,ans,k,dx,dy,dz);
}

int check(int c[10][10][10], int top[10][10], int n, int m){
    rep(i,n){
        rep(j,n){
            rep(k,n){
                if(c[i][j][k] == -1) continue;
                int tmp = -1;
                range(x,-1,2) range(y,-1,2) range(z,-1,2){
                    if(x == 0 && y == 0 && z == 0) continue;
                    dfs(n,m,i,j,k,c[i][j][k],c,tmp,0,x,y,z);
                }
                if(tmp != -1) return tmp;
            }
        }
    }
    return -1;
}

int main(){
    int n,m,q;
    while(cin >> n >> m >> q, n||m||q){
        int c[10][10][10]; //Black 0, white 1,
        memset(c,-1,sizeof(c));
        int top[10][10] = {0};
        vector<int> x, y;
        rep(i,q){
            int a, b;
            cin >> a >> b;
            a--; b--;
            x.emplace_back(a);
            y.emplace_back(b);
        }

        bool f = 0;
        rep(i,q){
            pushBall(c,top,x[i],y[i],i % 2);
            int tmp = check(c,top,n,m);
            if(tmp == 0){
                cout << "Black" << ' ' << i + 1 << endl;
                f = 1;
                break;
            }else if(tmp == 1){
                cout << "White" << ' ' << i + 1 << endl;
                f = 1;
                break;
            }
        }
        if(f == 0){
            cout << "Draw" << endl;
        }
    }
}
