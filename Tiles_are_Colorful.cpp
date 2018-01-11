#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

char m[505][505];
int h, w;

const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

vector<pair<pair<int, int>,char>> extends(int y, int x){
    vector<pair<pair<int,int>,char>> ret;
    rep(i,4){
        int ny = y, nx = x;
        while(true){
            ny += dy[i];
            nx += dx[i];
            if(ny < 0 || ny >= h || nx < 0 || nx >= w) break;
            if(m[ny][nx] != '.'){
                ret.emplace_back(make_pair(make_pair(ny,nx),m[ny][nx]));
                break;
            }
        }
    }
    return ret;
}

void compress(vector<int> &v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
}

int lb(vector<int> v, int num){
    return lower_bound(all(v), num) - v.begin();
}

int main(){
    cin >> h >> w;

    vector<pair<pair<int, int>,char>> v;
    vector<int> x,y;
    rep(i,h){
        rep(j,w){
            char c;
            cin >> c;
            m[i][j] = c;
            if(c != '.'){
                v.emplace_back(make_pair(make_pair(i,j),c));
                y.emplace_back(i);
                x.emplace_back(j);
            }
        }
    }
    //compress(x);
    //compress(y);
    //h = y.size();
    //w = x.size();

    //rep(i,h + 1) rep(j,w + 1) m[i][j] = '.';
    //rep(i,v.size()){
    //    int fy = lb(y,v[i].first.first);
    //    int fx = lb(x,v[i].first.second);
    //    m[fy][fx] = v[i].second;
    //}
    //cout << endl; rep(i,h){ rep(j,w){ cout << m[i][j]; } cout << endl; } cout << endl;

    bool f = true;
    int cnt = 0;
    while(f){
        f = false;
        rep(i,h){
            rep(j,w){
                vector<pair<pair<int, int>,char>> v;
                if(m[i][j] == '.') v = extends(i,j);
                rep(i,v.size()){
                    rep(j,v.size()){
                        if(i == j) continue;
                        if(v[i].second == v[j].second){
                            if(m[ v[i].first.first ][ v[i].first.second ] == '.') continue;
                            m[ v[i].first.first ][ v[i].first.second ] = '.';
                            m[ v[j].first.first ][ v[j].first.second ] = '.';
                            f = true;
                            cnt++;
                        }
                    }
                }
            }
        }
    }
    cout << cnt * 2 << endl;
}
