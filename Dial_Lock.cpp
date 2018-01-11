#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int n;
string a, b;

int dfs(string a, int i, int cnt){
    if(i >= n) return cnt;
    if(a[i] == b[i]){
        return dfs(a,i + 1, cnt);
    }

    int ret = 1e8;
    int dif = (b[i] - a[i] + 10) % 10;
    for(int j = i; j < n; j++){
        a[j] = '0' + (a[j] + dif - '0') % 10;
        ret = min(ret, dfs(a,i + 1, cnt + 1));
    }
    return ret;
}

int main(){
    while(cin >> n,n){
        map<string,int> m;
        cin >> a >> b;

        queue<pair<int,string>> q;
        q.push(make_pair(0,a));
        cout << dfs(a,0,0) << endl;
    }
}
