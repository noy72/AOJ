#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

char C[2000];

bool check(int n, int p,int maxi, map<char,int> m){
    int cnt = 0;
    for(auto it:m){
        if(it.second + n - p > maxi) cnt++;
    }
    return (cnt == 1);
}

int main(){
    int n;
    while(cin >> n,n){
        map<char,int> m;
        bool f = false;
        int maxi = 0;
        char maxi_c;
        m['1'] = 0; //候補者が二人以上いると仮定
        rep(i,n) cin >> C[i];
        rep(i,n){
            m[C[i]]++;
            if(maxi < m[C[i]]){
                maxi = m[C[i]];
                maxi_c = C[i];
            }
            if(check(n,i,maxi,m)){
                cout << maxi_c << ' ' << i + 1 << endl;
                f = true;
                break;
            }
        }
        if(not f){
            cout << "TIE" << endl;
        }
    }
}
