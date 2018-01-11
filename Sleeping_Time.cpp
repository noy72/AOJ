#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

double p, e, t;

double dfs(int k, double r, double l){
    double h = (r + l) / 2;

    if(k == 0){
        if(abs(t - h) < e) return 1;
        else return 0;
    }

    if(t - e <= l && r <= t + e) return 1;
    else if(r < t - e || t + e < l) return 0;

    if(h >= t){
        return  p * dfs(k - 1, r, h) + (1 - p) * dfs(k - 1, h, l);
    }else{
        return  p * dfs(k - 1, h, l) + (1 - p) * dfs(k - 1, r, h);
    }
}

int main(){
    int k;
    double r,l;
    cin >> k >> l >> r >> p >> e >> t;
    cout <<fixed << setprecision(10)<< dfs(k, r, l) << endl;
}
