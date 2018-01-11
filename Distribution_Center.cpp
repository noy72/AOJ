#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

vector<pair<int, int>> v[200005]; //min - max
pair<int, int> IN[200005];

int main(){
    int n, m;
    cin >> n >> m;

    rep(i,m){
        cin >> IN[i].first >> IN[i].second;
        IN[i].second--;
    }
    sort(IN, IN + m);

    rep(i,m){
        int y = IN[i].second;
        //show(IN[i].first)
        //show(y)
        int s = y, t = y + 1;
        if(y != n - 2){
            if(not v[y + 1].empty()){
                s = min(v[y + 1].back().first, s);
                t = max(v[y + 1].back().second, t);
            }
        }
        if(y != 0){
            if(not v[y - 1].empty()){
                s = min(v[y - 1].back().first, s);
                t = max(v[y - 1].back().second, t);
            }
        }
        //show(s)
        //show(t)
        //show(y)
        v[y].emplace_back(make_pair(s,t));
    }

    rep(i,n){
        if(i) cout << ' ';
        if(i == 0) {
            if(v[i].empty()) cout << 1;
            else cout << v[i].back().second - v[i].back().first + 1;
        } else if(i == n - 1) {
            if(v[i - 1].empty()) cout << 1;
            else cout << v[i - 1].back().second - v[i - 1].back().first + 1;
        } else{
            if(v[i].empty() && v[i - 1].empty()) cout << 1;
            else if(v[i].empty()) cout << v[i - 1].back().second - v[i - 1].back().first + 1;
            else if(v[i - 1].empty()) cout << v[i].back().second - v[i].back().first + 1;
            else cout << v[i].back().second - v[i - 1].back().first + 1;
        }
    }
    cout << endl;
}
