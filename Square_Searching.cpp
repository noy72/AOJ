#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int main(){
    int n;
    while(cin >> n, n){
        char m[1005][1005];
        int c[1005][1005] = {{0}};
        rep(i,n){
            rep(j,n){
                cin >> m[i + 1][j + 1];
            }
        }
        rep(i,n) m[i][0] = m[0][i] = m[i][n + 1] = m[n + 1][i] = '*';
        
        range(i,1,n + 1){
            range(j,1,n + 1){
                if(m[i][j] == '*') c[i][j] = 0;
                else c[i][j] = min(min(c[i - 1][j], c[i][j - 1]), c[i - 1][j - 1]) + 1;
            }
        }

        int maxi = 0;
        rep(i,n){
            rep(j,n){
                maxi = max(maxi, c[i + 1][j + 1]);
            }
        }
        cout << maxi << endl;
    }
}
