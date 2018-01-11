#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

long long dfs(string s[25], int n, int y, int x) {
    //cout << y << ' ' << x << endl;;
    if(isdigit(s[y][x])){
        return s[y][x] - '0';
    }else if(s[y][x] == '.'){
        assert(0);
    }else{
        long long res;
        //show(s[y][x])
        if(s[y][x] == '+'){
            res = 0;
            range(i,y + 1,n){
                //cout << i << ' ' << x + 1 << endl;
                if(x + 1 >= s[i].size()) break;
                if(s[i][x + 1] == '.') continue;
                res += dfs(s,n,i,x + 1);
            }
        }else{
            res = 1;
            range(i,y + 1,n){
                if(x + 1 >= s[i].size()) break;
                if(s[i][x + 1] == '.') continue;
                res *= dfs(s,n,i,x + 1);
            }
        }
        //show(res)
        return res;
    }
    assert(0);
    return 0;
}

int main(){
    int n;
    while(cin >> n,n){
        string s[25];
        rep(i,n) cin >> s[i];
        cout << dfs(s,n,0,0) << endl;
    }
}
