#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

const int MAX_N = 1000;

typedef pair<int, int> P;

void compress(vector<int> &v) {
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
}

int lb(vector<int> v, int num){
	return lower_bound(all(v), num) - v.begin();
}

const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};
void bfs(int y, int x, bool used[MAX_N][MAX_N], int m[MAX_N][MAX_N]){
	queue<pair<int, int>> q;
	q.push(make_pair(y,x));

	while(not q.empty()){
		pair<int, int> cur = q.front(); q.pop();
		if(used[cur.first][cur.second]) continue;
		used[cur.first][cur.second] = true;

		rep(i,4){
			int ny = cur.first + dy[i];
			int nx = cur.second + dx[i];
			if(ny < 0 || ny >= MAX_N || nx < 0 || nx >= MAX_N) continue;
			if(m[ny][nx] == 0){
				q.push(make_pair(ny,nx));
			}
		}
	}
}

int main(){
	int n;
	while(cin >> n,n){
		pair<P,P> p[55];
		vector<int> x,y;
		rep(i,n){
			int a, b, c, d;
			cin >> a >> d >> c >> b;
			p[i] = make_pair(P{a,b}, P{c,d});

			range(i,-1,2) x.emplace_back(a + i);
			range(i,-1,2) x.emplace_back(c + i);
			range(i,-1,2) y.emplace_back(b + i);
			range(i,-1,2) y.emplace_back(d + i);
		}

		compress(x);
		compress(y);

		int m[MAX_N][MAX_N] = {{0}};
		rep(i,n){ //左下が原点の座標系なので、y軸について逆の大小関係になる
			int lx = lb(x, p[i].first.first);
			int ly = lb(y, p[i].first.second);
			int rx = lb(x, p[i].second.first);
			int ry = lb(y, p[i].second.second);
			lx *= 2; rx *= 2; ly *= 2; ry *= 2;

			//cout << lx << ' ' << ry << ' ' << rx << ' ' << ly << endl;
			//range(j,ry,ly + 1){ range(k,lx,rx + 1){ m[j][k]++; } }
			range(j,ry,ly + 1){
				m[j][lx]++;
				m[j][rx]++;
			}
			range(j,lx,rx + 1){
				m[ry][j]++;
				m[ly][j]++;
			}
		}
		rep(i,n * 10){ rep(j, n * 10){ cout << (m[i][j] == 0 ? '_' : '*') << ' ' ; } cout << endl; }

		bool used[MAX_N][MAX_N] = {{0}};
		int cnt = 0;
		rep(i,MAX_N){
			rep(j,MAX_N){
				if(not used[i][j] && m[i][j] == 0){
					cnt++;
					bfs(i,j,used,m);
					//show(i) show(j) rep(k,n * 5){ rep(l,n * 5){ cout << (used[k][l] ? '*' : '_') << ' '; } cout << endl; }
				}
			}
		}
		cout << cnt << endl;
	}
}
