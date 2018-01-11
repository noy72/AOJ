#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const long long INF = (1LL << 60);

int main(){
    int w;
    cin >> w;

    long long a[100005];
    rep(i,w){
        cin >> a[i];
    }

    long long away[100005] = {0};
    long long cur = 0, ans = 0;
    rep(i,w){
        if(a[i] == 0) cur = INF;
        else if(a[i] < 0){
            cur = min(cur, -a[i]);
        }else{
            long long tmp = min(a[i], cur);
            ans += tmp;
            away[i] += tmp;
        }
        if(cur > 0) cur--;
    }
    cur = 0; 
    for(int i = w - 1; i >= 0; i--){
        if(a[i] == 0) cur = INF;
        else if(a[i] < 0){
            cur = min(cur, -a[i]);
        }
        else{
            long long tmp = min(a[i], cur);
            tmp = max(tmp - away[i], 0LL);
            ans += tmp;
        }
        if(cur > 0) cur--;
    }
    cout << ans << endl;
}
