#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int IN[200005];

int main(){
    int n,m;
    cin >> n >> m;

    vector<int> v;
    rep(i,m) cin >> IN[i];
    for(int i = m - 1; i >= 0; i--){
        if(find(all(v),IN[i]) == v.end()) v.emplace_back(IN[i]);
    }
    static bool used[200005] = {0};
    rep(i,v.size()){
        used[ v[i] ] = true;
        cout << v[i] << endl;
    }
    range(i,1,n + 1){
        if(not used[i]) cout << i << endl;
    }
}
