#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int INF = 1e8;

const int MAX_V = 105;
const int MAX_C = 10005;

struct Edge{
    int to, cost;
};

int M[MAX_V][MAX_V];

bool C(int n, int low, int high){
    bool used[MAX_V] = {0};
    queue<int> q; //訪問した点を入れる

    q.push(0);
    used[0] = true;

    int u, cnt = 1;
    while(!q.empty()){
        u = q.front(); q.pop();
        rep(v,n){
            if(M[u][v] >= low && M[u][v] <= high && used[v] == false){
                used[v] = true;
                cnt++;
                q.push(v);
            }
        }
    }
    return n == cnt;
}

int binarySearch(int n, int low, int &ans){
    int right = MAX_C, left = low;
    rep(i,20){
        int mid = (right + left) / 2;
        if(C(n,low,mid)) right = mid;
        else left = mid;
    }
    return right;
}

int main(){
    int n, m;
    while(cin >> n >> m, n){
        memset(M, -1, sizeof(M));
        vector<int> v;
        rep(i,m){
            int a, b, w;
            cin >> a >> b >> w;
            a--; b--;
            M[a][b] = M[b][a] = w;
            v.emplace_back(w);
        }
        sort(all(v));

        int ans = INF;
        rep(i,v.size()){
            int high = binarySearch(n,v[i],ans);
            if(C(n,v[i],high)) ans = min(ans, high - v[i]);
            else break;
        }

        //int ans = INF;
        cout << (ans == INF ? -1 : ans) << endl;
    }
}
