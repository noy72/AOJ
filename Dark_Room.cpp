#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int INF = 1e8;
const int MAX = 105;

int dr[MAX]; //dr[暗い部屋の番号] = 実際のbitの割り当て
int v[MAX][MAX];
int n, m, k;

bool getBit(int num, int i){
    return ((num & (1 << i)) != 0);
}

int moveto(int v[MAX], int num){
    //show(num)
    int ret = 0;
    //cout << "---------" << num << endl;
    rep(i,n){
        //暗い部屋からの移動である
        //暗い部屋のbitが1である
        //移動先が明るい部屋でない
        if(dr[i] != INF && getBit(num,dr[i]) && dr[v[i]] != INF){
            ret |= 1 << dr[v[i]];
        }
    }
    //show(ret)
    return ret;
}

int bfs(){
    int dis[1 << m]; //距離
    queue<int> q; //訪問した点を入れる
    rep(i,1 << m) dis[i] = INF;

    dis[(1 << m) - 1] = 0;
    q.push((1 << m) - 1);

    int u;
    while(!q.empty()){
        u = q.front(); q.pop();
        if(u == 0) continue;
        rep(i,k){
            //show(i)
            int tmp = moveto(v[i], u);
            //if(tmp == 0){ show(u) show(i) }
            if(dis[tmp] > dis[u] + 1){
                dis[tmp] = dis[u] + 1;
                q.push(tmp);
            }
        }
    }
    return dis[0];
}

int main(){
    int cnt = 0;
    cin >> n >> m >> k;
    rep(i,MAX) dr[i] = INF;
    rep(i,m) {
        int d;
        cin >> d;
        d--;
        dr[d] = cnt++;
    }

    rep(i,n){
        rep(j,k){
            cin >> v[j][i]; //v[j] := j番を選んだ時の頂点の移動先
            v[j][i]--;
        }
    }

    cout << bfs() << endl;
}
