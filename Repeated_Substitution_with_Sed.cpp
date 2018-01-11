#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;
const int INF = 10000000;

string replaceAll(string s, string from, string to){
    vector<int> all;
    string tmp = s, tmp_space = s;

    string::size_type pos = tmp.find(from);
    while(pos != string::npos){
        all.emplace_back(pos);
        pos = tmp.find(from, pos + from.size());
    }
    if(all.empty()) return "0";

    //string space(from.size(), ' ');
    rep(j,all.size()){
        tmp.replace(all[j] + (to.size() - from.size()) * j, from.size(), to);
        //tmp_space.replace(all[j] + (from.size() - to.size()) * j, from.size(), space);
    }
    //if(tmp_space.find(to) != string::npos) return "0";

    return tmp;
}

int bfs(int n, string s, string t, pair<string, string> p[11], int cnt){
    queue<pair<string,int>> q;
    q.push(make_pair(s,0));

    while(not q.empty()){
        pair<string, int> u = q.front(); q.pop();
        if(u.first == t) return u.second;
        if(u.first.size() > 10) continue;

        string tmp;
        rep(i,n){
            tmp = replaceAll(u.first, p[i].first, p[i].second);
            if(tmp == "0" || u.first == tmp) continue;
            q.push(make_pair(tmp, u.second + 1));
        }
    }
    return -1;
}

int main(){
    int n;
    while(cin >> n,n){
        pair<string, string> p[11];
        rep(i,n){
            string a, b;
            cin >> a >> b;
            p[i] = make_pair(a,b);
        }
        string s, t;
        cin >> s >> t;
        cout << bfs(n,s,t,p,0) << endl;
        //int tmp = dfs(n,s,t,p,0);
        //cout << (tmp == INF ? -1 : tmp) << endl;
    }
}
