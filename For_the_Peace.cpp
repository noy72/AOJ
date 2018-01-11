#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

vector<int> a[105];
int sum[105];
int n, d;

int maxSum(){
    int maxi = 0;
    int ret;
    rep(i,n){
        if(maxi < sum[i]){
            maxi = sum[i];
            ret = i;
        }
    }
    return ret;
}

bool C(){
    rep(i,n){
        if(not a[i].empty()) return false;
    }
    return true;
}

bool deleteMax(int p){
    int next_p = sum[p] - a[p].back();
    rep(i,n){
        if(i == p) continue;
        if(not (sum[i] - d <= next_p && sum[i] + d >= next_p)){
            return false;
        }
    }
    return true;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    while(cin >> n >> d,n){
        rep(i,105) a[i].clear();
        rep(i,105) sum[i] = 0;
        rep(i,n){
            int m;
            cin >> m;
            rep(j,m){
                int x;
                cin >> x;
                a[i].emplace_back(x);
                sum[i]+=x;
            }
        }

        bool f = true;
        while(f){
            int p = maxSum();
            f = false;
            int limit = sum[p] - d;
            rep(i,n){
                if(i == p || a[i].empty()) continue;
                while(sum[i] - a[i].back() >= limit){
                    f = true;
                    sum[i] -= a[i].back();
                    a[i].pop_back();
                    if(a[i].empty()) break;
                }
            }
            if(C()) break;
            //rep(i,n) show(sum[i])
            p = maxSum();
            while(not a[p].empty() && deleteMax(p)){
                f = true;
                sum[p] -= a[p].back();
                a[p].pop_back();
            }
            if(C()) break;
        }

        cout << (C() ? "Yes" : "No") << endl;
    }
}
