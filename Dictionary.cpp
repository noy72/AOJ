#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int MAX_V = 30;

vector<int> g[MAX_V]; //????????
vector<int> tp; //????????????????????????????????????

bool visit(int v, vector<int> &color){
    color[v] = 1;
    rep(i,g[v].size()){
        int d = g[v][i];
        if(color[d] == 2) continue;
        if(color[d] == 1) return false;
        if(not visit(d, color)) return false;
    }
    tp.emplace_back(v);
    color[v] = 2;
    return true;
}

bool topologicalSort(int v){
    vector<int> color(v);
    rep(i,v){
        if(not color[i] && not visit(i, color)) return false;
    }
    reverse(all(tp));
    return true;
}

int main(){
    int n;
    while(cin >> n,n){
        rep(i,MAX_V) g[i].clear();
        tp.clear();
        char s[505][15];
        rep(i,505) rep(j,15) s[i][j] = '\0';
        rep(i,n) cin >> s[i];

        bool ans = true;
        rep(i,n){
            range(j,i + 1, n){
                rep(k,15){
                    if(s[i][k] != '\0' && s[j][k] == '\0'){
                        ans = false;
                        break;
                    }else if(s[i][k] == '\0' || s[j][k] == '\0'){
                        break;
                    }else if(s[i][k] != s[j][k]){
                        //cout << s[i][k] << ' ' << s[j][k] << endl;
                        g[s[i][k] - 'a'].emplace_back(s[j][k] - 'a');
                        break;
                    }
                }
            }
        }

        cout << (topologicalSort(30) && ans ? "yes" : "no") << endl;
    }
}
