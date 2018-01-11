#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int MAX_N = 100005;

//[1, n]
int bit[MAX_N + 1] = {0};

int sum(int i){
    int s = 0;
    while(i > 0){
        s = max(s,bit[i]);
        i -= i & -i;
    }
    return s;
}

void add(int i, int x, int n){
    while(i <= MAX_N){
        //bit[i] += x;
        bit[i] = max(bit[i], x);
        i += i & - i;
    }
}

int main(){
    int n,m;
    while(cin >> n,n){
        memset(bit,0,sizeof(bit));
        pair<int, int> p[MAX_N];
        rep(i,n) cin >> p[i].first >> p[i].second;
        cin >> m;
        range(i,n,n + m) cin >> p[i].first >> p[i].second;

        rep(i,n + m) p[i].second *= -1;
        sort(p, p + n + m);
        rep(i,n + m) p[i].second *= -1;

        int dp[MAX_N] = {0};
        rep(i,n + m){
            dp[i] = sum(p[i].second - 1) + 1;
            add(p[i].second, dp[i], n + m);
        }
        cout << *max_element(dp, dp + MAX_N) << endl;
    }
}
