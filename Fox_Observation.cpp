#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int dy[4] = {0,1,1};
int dx[4] = {1,0,1};
int my[4] = {1, 1, -1, -1};
int mx[4] = {1, -1, -1, 1};

int main(){
    int n;
    cin >> n;

    map<pair<int, int>,int> m;
    rep(i,n){
        int x, y, w;
        cin >> x >> y >> w;
        m[make_pair(x,y)] = w;
    }

    int maxi = 0;
    for(auto it:m){
        rep(j,4){
            int sum = m[ make_pair(it.first.first, it.first.second) ];
            rep(i,3){
                if(m.count(make_pair(it.first.first + dx[i] * mx[j], it.first.second + dy[i] * my[j]))){
                    sum += m[ make_pair(it.first.first + dx[i] * mx[j], it.first.second + dy[i] * my[j]) ];
                }
            }
            maxi = max(maxi, sum);
        }
    }
    cout << maxi << " / 1" << endl;
}
