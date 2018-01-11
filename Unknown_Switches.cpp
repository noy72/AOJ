#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int main(){
    int n, m, q;
    while(cin >> n >> m >> q, n||m||q){
        int a[37][1005];
        memset(a, -1, sizeof(a)); //1:可能性あり 0:可能性なし -1:わからない

        if(q == 0 && n == 1){
            rep(i,m) cout << 0;
            cout << endl;
            continue;
        }
        string sb, bb;
        rep(i,n) sb+='0';
        rep(j,m) bb+='0';
        rep(i,q){
            string s, b;
            cin >> s >> b;
            rep(j,n){
                if(s[j] == '1'){
                    rep(k,m){
                        if(b[k] != bb[k]){
                            //cout << j << ' ' << k << endl;
                            if(a[j][k] != 0) a[j][k] = 1;
                        }else{
                            if(a[j][k] != 0) a[j][k] = 0;
                        }
                    }
                }else{
                    rep(k,m){
                        if(b[k] != bb[k]){
                            //cout << j << ' ' << k << endl;
                            if(a[j][k] != 0) a[j][k] = 0;
                        }else{
                            if(a[j][k] != 0) a[j][k] = 1;
                        }
                    }
                }
            }
            sb = s;
            bb = b;
        //rep(i,3){ rep(j,10){ cout << a[i][j]; } cout << endl; } cout << endl;
        }

        rep(j,m){
            int is_not_zero = 0;
            char c = '?';
            rep(i,n){
                if(a[i][j] != 0) {
                    is_not_zero++;
                    if(c == '?'){
                        if(i >= 0 && i <= 9) c = i + '0';
                        else c = (i - 10) + 'A';
                    }
                }
            }
            if(is_not_zero == 1) cout << c;
            else cout << '?';
        }
        cout << endl;
    }
}
