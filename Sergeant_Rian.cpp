#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int MAX_V = 25;
const int INF = 1e8;

void init(int m[MAX_V][MAX_V]){
    rep(i,MAX_V) rep(j,MAX_V) m[i][j] = INF;
    rep(i,MAX_V) m[i][i] = 0;
}

void warshallFloyd(int m[MAX_V][MAX_V], int n, bool ignore[MAX_V]){
    rep(k,n){
        rep(i,n){
            rep(j,n){
                if(ignore[i] || ignore[j] || ignore[k]) continue;
                m[i][j] = min(m[i][j], m[i][k] + m[k][j]);
            }
        }
    }
}

int main(){
    int n;
    while(cin >> n,n){
        int g[MAX_V][MAX_V] = {0};
        vector<int> v[MAX_V];
        rep(i,n - 1){
            int a, b, c;
            cin >> a >> b >> c;
            a--; b--;
            g[a][b] = g[b][a] = c;
            v[a].emplace_back(b);
            v[b].emplace_back(a);
        }

        bool ignore[MAX_V] = {0};
        range(i,1,n){
            if(v[i].size() == 1) ignore[i] = true;
        }

        int m[MAX_V][MAX_V];
        rep(i,n) rep(j,n) m[i][j] = g[i][j] == 0 ? INF : g[i][j];
        rep(i,n) m[i][i] = 0;
        warshallFloyd(m, n, ignore);

        int sum = 0;
        int maxi = 0;
        rep(i,n){
            rep(j,n){
                if(ignore[i] || ignore[j]) continue;
                sum += g[i][j];
            }
        }
        rep(i,n){
            if(ignore[i]) continue;
            maxi = max(maxi, m[0][i]);
        }
        //show(sum)
         //   show(maxi)
        cout << sum - maxi << endl;
    }
}
