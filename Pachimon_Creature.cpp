#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

static vector<pair<int, int>> v[5];


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    int w, h;
    while(cin >> w >> h, w){
        rep(i,5) v[i].clear();
        pair<int, int> s, g;
        rep(i,h){
            rep(j,w){
                char x;
                cin >> x;
                if(x == '.') continue;
                if(x == 'S') s = make_pair(i,j);
                else if(x == 'G') g = make_pair(i,j);
                else v[ x - '0' - 1 ].emplace_back(i,j);
            }
        }

        int ans = INF, p = -1;
        rep(i,5){
            int num = i;

            rep(i,1005) rep(j,1005) rep(k,5) dp[i][j][k] = INF;
            dp[s.first][s.second][0] = 0;

            queue<pair<pair<int, int>, int>> q;
            q.push(make_pair(s,num % 5));
            pair<pair<int, int>,int> u;
            while(not q.empty()){
                u = q.front(); q.pop();
                pair<int, int> cur = u.first;
                int next = (u.second + 1) % 5;
                int have = (next - num + 5) % 5;

                if(have == 4){
                    dp[g.first][g.second][4] = min(dp[g.first][g.second][4],
                            dp[cur.first][cur.second][have - 1] + abs(cur.first - g.first) + abs(cur.second - g.second));
                    continue;
                }
                for(auto p : v[next]){
                    //cout << p.first << ' ' << p.second << endl;
                    int dis = abs(p.first - cur.first) + abs(p.second - cur.second);
                    if(dp[p.first][p.second][have] > dp[cur.first][cur.second][have - 1] + dis){
                        dp[p.first][p.second][have] = dp[cur.first][cur.second][have - 1] + dis;
                        q.push(make_pair(p,next % 5));
                    }
                }
            }

            int tmp = dp[g.first][g.second][4];
            if(ans > tmp){
                ans = tmp;
                p = i + 1;
            }
        }
        if(p == -1) cout << "NA" << endl;
        else cout << p << ' ' << ans << endl;
    }
}
