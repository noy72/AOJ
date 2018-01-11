#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

long long n, k;

bool C(long long x){
    rep(i,n - 1){
        x = x - (x - 1) / k - 1;
        if(x <= 0) return true;
    }
    return false;
}

int main(){
    cin >> n >> k;

    long long right = 1e18, left = 0;
    rep(i,200){
        long long mid = (right + left ) / 2;
        if(C(mid)) left = mid;
        else right = mid;
    }
    cout << left << endl;
}
