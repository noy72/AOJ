#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

long long w, m, k;

long long SSum(long long n){
    long long ret = 0;
    long long j = 19;
    for(long long i = 1e18; i > 0; i /= 10,j--){
        if(n - i < 0) continue;
        ret += (n - i + 1) * j;
        n = i - 1;
    }
    return ret;
}

bool C(long long mid){
    return (SSum(mid) - SSum(m) <= w / k);
}

bool CC(long long mid){
    return (SSum(m + 1) - SSum(mid) <= w / k);
}

long long solve(){
    long long right = 1e18, left = 0;
    rep(i,200){
        long long mid = (right + left ) / 2;
        if(CC(mid)) right = mid;
        else left = mid;
    }
    return right;
}

int main(){
    cin >> w >> m >> k;
    m--;

    long long right = 1e18, left = 0;
    rep(i,200){
        long long mid = (right + left ) / 2;
        if(C(mid)) left = mid;
        else right = mid;
    }
    cout << left - m << endl;
}
