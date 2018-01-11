#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

bool dfs(string s){
    if(s == "ABC") return true;
    else if(s.find("ABC") == string::npos) return false;

    string ABC = "A";
    bool res = false;
    rep(i,3){
        string tmp = s;
        string::size_type pos = tmp.find("ABC");
        while(pos != string::npos){
            tmp.replace(pos, 3, ABC);
            pos = tmp.find("ABC", pos + 1);
            cnt++;
        }
        res |= dfs(tmp);
        ABC[0]++;
    }
    return res;
}

int main(){
    string s;
    cin >> s;
    if(dfs(s)) cout << "Yes" << endl;
    else cout << "No" << endl;
}
