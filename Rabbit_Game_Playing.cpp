#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;
const int M = 1000000007;

int main(){
    int n;
    long long t;
    cin >> n >> t;

    vector<long long> a(n);
    rep(i,n) cin >> a[i];
    sort(all(a));

    long long ans = 1;
    for(auto it = a.begin(); it != a.end(); it++){
        ans *= (upper_bound(a.begin(), it, *it) - lower_bound(a.begin(), it, (*it) - t)) + 1;
        ans %= M;
    }
    cout << ans << endl;
}
