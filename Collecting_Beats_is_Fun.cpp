#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

int k;
map<int,int> m;
bool solve(){
    for(auto it:m){
        if(it.second > k * 2) return 0;
    }
    return 1;
}

int main(){
    cin >> k;

    rep(i,4){
        rep(j,4){
            char x;
            cin >> x;
            if(x == '.') continue;
            m[x - '0']++;
        }
    }
    cout << (solve() ? "YES" : "NO") << endl;
}
