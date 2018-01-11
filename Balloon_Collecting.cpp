#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int g_dis;
int ng;
int n;
pair<int, int> p[50]; //位置、時刻

void dfs(int i, int d, int k){
    if(k > 3) return;
//    show(t)
//        show(i)
    int c = i == 0 ? 0 : p[i - 1].first;
    int t = i == 0 ? 0 : p[i - 1].second;
    if(g_dis < d) return;
    if(i == n){
        g_dis = min(g_dis, d + c);
        return;
    }

    //show(p[i].second)
    //show(dist * (k + 1))
    //show(c * (k + 1) + p[i].first)

    int dist = abs(p[i].first - c);
    ng = max(ng, i);
    if(p[i].second >= t + dist * (k + 1)) dfs(i + 1, d + dist, k + 1);
    if(p[i].second >= t + c * (k + 1) + p[i].first) dfs(i + 1, d + c + p[i].first, 1);
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    while(cin >> n,n){
        g_dis = 1e8;
        ng = 0;
        rep(i,n) cin >> p[i].first >> p[i].second;
        dfs(0,0,0);
        if(g_dis == 1e8) cout << "NG " << ng + 1 << endl;
        else cout << "OK " << g_dis << endl;
    }
}
