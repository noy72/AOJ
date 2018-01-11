#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
const long long INF = 2000000000;
using namespace std;

const long long MAX_N = 4005;
long long g[MAX_N][MAX_N] = {0};
long long imos[MAX_N][MAX_N] = {0};

void compress(vector<long long> &v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
}

long long lb(vector<long long> v, long long num){
    return lower_bound(all(v), num) - v.begin();
}

int main(){
    long long n;
    cin >> n;

    pair<pair<long long, long long>, pair<long long, long long>> inp[MAX_N];
    vector<long long> x, y;
    rep(i,n){
        cin >> inp[i].first.first >> inp[i].first.second >> inp[i].second.first >> inp[i].second.second;
        x.emplace_back(inp[i].first.first);
        x.emplace_back(inp[i].second.first);
        y.emplace_back(inp[i].first.second);
        y.emplace_back(inp[i].second.second);
    }
    compress(x);
    compress(y);

    rep(i,n){
        long long lx = lb(x, inp[i].first.first);
        long long ly = lb(y, inp[i].first.second);
        long long rx = lb(x, inp[i].second.first);
        long long ry = lb(y, inp[i].second.second);

        for(long long j = ly; j < ry; j++) g[j][lx]++;
        for(long long j = ly; j < ry; j++) g[j][rx]--;
    }

    rep(i,y.size()){
        long long c = 0;
        rep(j,x.size()){
            c+=g[i][j];
            imos[i][j] = c;
        }
    }

    //rep(i,5){ rep(j,5){ cout << imos[i][j] << ' '; } cout << endl; }

    long long sum = 0;
    range(i,0,y.size()){
        range(j,0,x.size()){
            if(imos[i][j] != 0){
            //if(imos[i][j] != 0 && imos[i][j + 1] != 0 && imos[i + 1][j] != 0 && imos[i + 1][j + 1] != 0){
                //cout << (y[i + 1] - y[i]) << ' ' <<   (x[j + 1] - x[j])  << endl;;
                //sum += (y[i + 1] - y[i]) * (x[j + 1] - x[j]);
                sum += abs(y[i + 1] - y[i]) * abs(x[j + 1] - x[j]);
            }
        }
    }
    cout << sum << endl;

}
