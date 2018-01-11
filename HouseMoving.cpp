#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

#define int long long

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

void add(int i, int x){
    while(i <= MAX_N){
        //bit[i] += x;
        bit[i] = max(bit[i], x);
        i += i & - i;
    }
}

signed main(){
    int n;
    cin >> n;

    rep(i,n){
        int a;
        cin >> a;
        add(a, sum(a) + a);
    }
    cout << ((n * n + n) / 2) - sum(MAX_N) << endl;
}
