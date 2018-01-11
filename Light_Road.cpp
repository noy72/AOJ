#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

const int N = 105;

int h, w, a;
char m[N][N];
bool dis[N][N][15][15][4];

struct Point{ int x, y, p, q, d; };
int dy[4] = {0,1,0,-1}, dx[4] = {1,0,-1,0};

int bfs(int h, int w, Point p, Point g){
	queue<Point> q;

	if(p.y + 1 > h) return INF;

	dis[p.y + 1][p.x][a][a][1] = 1;
	Point tmp = Point{p.x, p.y + 1, a, a, 1};
	q.push(tmp);

	while(not q.empty()){
		Point u = q.front(); q.pop();
		//cout << u.x << ' ' << u.y << ' ' << u.p << ' ' << u.q << ' ' << u.d << endl;
		rep(i,4){
			if((u.d + 2) % 4 == i) continue;

			Point next;
			next.x = u.x + dx[i];
			next.y = u.y + dy[i];
			next.d = i;
			next.p = u.p;
			next.q = u.q;
			if(u.d == 0 || u.d == 2){
				if((u.d + 1) % 4 == i){
					next.p = u.p - 1;
				}else if((u.d - 1 + 4) % 4 == i){
					next.q = u.q - 1;
				}
			}else{
				if((u.d + 1) % 4 == i){
					next.q = u.q - 1;
				}else if((u.d - 1 + 4) % 4 == i){
					next.p = u.p - 1;
				}
			}
			if(next.p < 0 || next.q < 0) continue;

			if(next.x < 0 || next.x >= w || next.y < 0 || next.y >= h) continue;
				//cout << next.x << ' ' << next.y << ' ' << next.p << ' ' << next.q << ' ' << next.d << endl;
			if(not dis[next.y][next.x][next.p][next.q][next.d] && m[next.y][next.x] != '#'){
				//cout << next.x << ' ' << next.y << ' ' << next.p << ' ' << next.q << ' ' << next.d << endl;
				dis[next.y][next.x][next.p][next.q][next.d] = 1;
				q.push(next);
			}
		}
	}

	int ans = INF;
	rep(i,a + 1){
		rep(j,a + 1){
			rep(k,4){
				if(dis[g.y][g.x][i][j][k] == false) continue;
				ans = min(ans, a - i + a - j);
			}
		}
	}

	return ans;
}

int main(){
	cin >> h >> w >> a;

	Point s, g;
	rep(i,h) rep(j,w){
		cin >> m[i][j];
		if(m[i][j] == 'S') s = Point{j,i};
		if(m[i][j] == 'G') g = Point{j,i};
	}

	int ans = bfs(h, w, s, g);
	cout << (ans == INF ? -1 : ans) << endl;
}
