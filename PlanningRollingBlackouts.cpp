#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int h, w, s;

const int MAX_N = 40;
//const int MAX_P = MAX_N * MAX_N;

pair<int, int> dp[MAX_N][MAX_N][MAX_N][MAX_N];


void cumulativeSum(int s[MAX_N][MAX_N], int h, int w){
    //左上の要素は(1,1)
    rep(i,h + 1) rep(j,w + 1) s[i][j + 1] += s[i][j];
    rep(i,h + 1) rep(j,w + 1) s[i + 1][j] += s[i][j];
}

//(i,j)を左上、(k,l)を右下とした長方形
int sum(int j, int i, int l, int k, int s[MAX_N][MAX_N]){
    return s[k][l] - s[i - 1][l] - s[k][j - 1] + s[i - 1][j - 1];
}

pair<int, int> dfs(int lx, int ly, int rx, int ry, int g[MAX_N][MAX_N]){
    if(dp[ly][lx][ry][rx].first != -1) return dp[ly][lx][ry][rx];

    int total = sum(1,1,w,h,g);
    pair<int, int> res = make_pair(1, s - (total - sum(lx,ly,rx,ry,g)));

    range(i,ly, ry){
        if(total - sum(lx,ly,rx,i,g) > s || total - sum(lx,i + 1,rx,ry,g) > s) continue;
        pair<int, int> a = dfs(lx,ly,rx,i,g);
        pair<int, int> b = dfs(lx,i + 1,rx,ry,g);
        pair<int, int> cal = make_pair(a.first + b.first, min(a.second, b.second));
        res = max(res, cal);
    }

    range(i,lx, rx){
        if(total - sum(lx,ly,i,ry,g) > s || total - sum(i + 1,ly,rx,ry,g) > s) continue;
        pair<int, int> a = dfs(lx,ly,i,ry,g);
        pair<int, int> b = dfs(i + 1,ly,rx,ry,g);
        pair<int, int> cal = make_pair(a.first + b.first, min(a.second, b.second));
        res = max(res, cal);
    }
    return dp[ly][lx][ry][rx] = res;
}

int main(){
    while(cin >> h >> w >> s, h||w){

        int g[MAX_N][MAX_N] = {0};
        rep(i,h){
            rep(j,w){
                cin >> g[i + 1][j + 1];
            }
        }

        rep(i,MAX_N) rep(j,MAX_N) rep(k,MAX_N) rep(l,MAX_N) dp[i][j][k][l] = make_pair(-1,-1);
        cumulativeSum(g,h,w);
        //rep(i,h + 1){ rep(j,w + 1){ cout << g[i][j] << ' ' ; } cout << endl; }
        //    rep(ry,h - 1){
        //        rep(rx,w - 1){
        //            range(ly,ry + 1,h){
        //                range(lx,rx + 1,w){
        //                    dp[
        //                }
        //            }
        //        }
        //    }
        pair<int, int> p = dfs(1,1,w,h,g);
        cout << p.first << ' ' << p.second << endl;
    }
}
