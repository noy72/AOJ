#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int gmax_n = 505;

int cntX[2][gmax_n] = {0};
int cntY[2][gmax_n] = {0};
bool usa[gmax_n][gmax_n] = {{0}}, neko[gmax_n][gmax_n] = {{0}};

int checkPointU(int n, int u, pair<int, int> p){
    int y = p.first;
    int x = p.second;
    usa[y][x] = 1;


    int cnt = 0;
    cntX[0][x]++;
    cntY[0][y]++;

    rep(i,n){
        if(cntX[0][i] == n) cnt++;
        if(cntY[0][i] == n) cnt++;
    }

    bool f = true;
    rep(i,n) if(usa[i][i] == 0) f = false;
    if(f) cnt++;

    f = true;
    rep(i,n) if(usa[i][n - 1 - i] == 0) f = false;
    if(f) cnt++;
    //y = find(y,parY[0][x], cntY[0][x]);
    //x = find(x,parX[0][y], cntX[0][y]);
    //show(cntX[0][y][x])
    //show(cntY[0][x][y])
    //show(cnt)
    if(n == 1) cnt = 1;
    if(cnt >= u || cnt >= u) return 1;
    else return 0;
}

int checkPointN(int n, int v, pair<int, int> p){
    int y = p.first;
    int x = p.second;
    neko[y][x] = 1;


    int cnt = 0;
    cntX[1][x]++;
    cntY[1][y]++;

    rep(i,n){
        if(cntX[1][i] == n) cnt++;
        if(cntY[1][i] == n) cnt++;
    }

    bool f = true;
    rep(i,n) if(neko[i][i] == 0) f = false;
    if(f) cnt++;

    f = true;
    rep(i,n) if(neko[i][n - 1 - i] == 0) f = false;
    if(f) cnt++;
    //y = find(y,parY[0][x], cntY[0][x]);
    //x = find(x,parX[0][y], cntX[0][y]);
    //show(cntX[0][y][x])
    //show(cntY[0][x][y])

    if(n == 1) cnt = 1;
    if(cnt >= v || cnt >= v) return 1;
    else return 0;
}

int main(){
    int n, u, v, m;
    cin >> n >> u >> v >> m;

    int x;
    map<int,pair<int, int>> up, np;
    rep(i,n){
        rep(j,n){
            cin >> x;
            up[x] = make_pair(i,j);
        }
    }
    rep(i,n){
        rep(j,n){
            cin >> x;
            np[x] = make_pair(i,j);
        }
    }

    int ans = 0;
    rep(i,m){
        int a;
        cin >> a;
        //cout << a << endl;
        if(ans == 0){
            int utmp = -1, vtmp = -1;
            utmp = (up.count(a) ? checkPointU(n,u,up[a]) : 0);
            vtmp = (np.count(a) ? checkPointN(n,v,np[a]) : 0);
//            show(utmp)
            //show(vtmp)
            if(utmp == 0 && vtmp != 0) ans = 1;
            else if(utmp != 0 && vtmp == 0) ans = 2;
            else if(utmp != 0 && vtmp != 0) ans = 3;
            else if(utmp == 0 && vtmp == 0);
            else assert(0);
        }
 //       show(ans)
 //           rep(i,n){ rep(j,n){ cout << usa[i][j]; } cout << endl; }
 //       cout << endl;
 //           rep(i,n){ rep(j,n){ cout << neko[i][j]; } cout << endl; }
    }
    if(ans == 1) cout << "NEKO" << endl;
    else if(ans == 2) cout << "USAGI" << endl;
    else cout << "DRAW" << endl;
}
