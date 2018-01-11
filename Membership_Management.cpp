#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

vector<string> split(string s){
    vector<string> res;
    int right = 0, left = 0;
    while(s[right] != ':') right++;
    right = left = right + 1;

    while(right < s.size()){
        while(s[right] != ',' && s[right] != '.') right++;
        //show(s.substr(left,(right - left)));
        res.emplace_back(s.substr(left, (right - left) ));
        right = left = right + 1;
    }
    return res;
}

string requestParent(string s){
    rep(i,s.size()){
        if(s[i] == ':'){
            return s.substr(0,i);
        }
    }
}

void dfs(map<string, vector<string>> m, string cur, set<string> &s, int &cnt){
    if(s.find(cur) != s.end()) return;
    s.insert(cur);

    if(m[cur].size() == 0) cnt++;
    else{
        rep(i,m[cur].size()){
            dfs(m,m[cur][i],s,cnt);
        }
    }
}

int main(){
    int n;
    while(cin >> n,n){
        cin.ignore();

        string first;
        map<string, vector<string> > m;
        rep(i,n){
            string tmp;
            getline(cin, tmp);

            string par = requestParent(tmp);
            if(i == 0) first = par;
            vector<string> s = split(tmp);
            rep(j,s.size()){
                m[ par ].emplace_back(s[j]);
            }
        }

        int cnt = 0;
        set<string> s;
        for(auto it:m[first]){
            dfs(m,it,s,cnt);
        }
        cout << cnt << endl;
    }
}
