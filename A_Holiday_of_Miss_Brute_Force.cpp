#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

int n;
int sx, sy, gx, gy;
int lx, ly;

struct Point{
	int cost, t;
	int x, y;
	bool operator < ( const Point &right ) const {
		return cost <= right.cost;
	}
	bool operator > ( const Point &right ) const {
		return cost > right.cost;
	}
};

//typedef pair<pair<int,int>,Point> P;
const int dx[16] = { 0, 1, 1, 0,-1,-1, 0, 0, 1, 1, 0,-1,-1, 0};
const int dy[16] = { 1, 0,-1,-1,-1, 0, 0, 1, 1, 0,-1, 0, 1, 0};
bool m[300][300];
const int BASE = 150;

const int N = 300;
const int T = 6;
int dis[N][N][T];

int bfs(Point p, Point g){
	priority_queue<Point, vector<Point>, greater<Point>> q;
	rep(i,N) rep(j,N) rep(k,T) dis[i][j][k] = INF;

	dis[p.y][p.x][0] = 0;
	Point tmp = Point{0,0,p.x,p.y};
	q.push(tmp);

	while(not q.empty()){
		Point c = q.top(); q.pop();

		int order = abs((c.x - BASE) * (c.y - BASE) * c.t) % 6;
		rep(i,7){
			Point next;
			next.x = c.x + dx[i + (c.x % 2 ? 7 : 0)];
			next.y = c.y + dy[i + (c.x % 2 ? 7 : 0)];
			next.t = c.t + 1;
			if(next.x < BASE - lx || next.x > BASE + lx || 
			   next.y < BASE - ly || next.y > BASE + ly) continue;

			int add = i == order ? 0 : 1;
			if(m[next.y][next.x] == false && dis[next.y][next.x][next.t % 6] > dis[c.y][c.x][c.t % 6] + add){
				dis[next.y][next.x][next.t % 6] = dis[c.y][c.x][c.t % 6] + add;
				Point tmp = Point{dis[next.y][next.x][next.t % 6], next.t, next.x, next.y};
				q.push(tmp);
			}
		}

	}
	int ans = INF;
	rep(i,T) ans = min(ans, dis[g.y][g.x][i]);
	return ans;
}

int main(){
	Point s, g;
	cin >> s.x >> s.y >> g.x >> g.y >> n;
	s.x += BASE;
	s.y += BASE;
	g.x += BASE;
	g.y += BASE;
	rep(i,n){
		int x, y;
		cin >> x >> y;
		m[BASE + y][BASE + x] = true;
	}
	cin >> lx >> ly;
	int ans = bfs(s,g);
	cout << (ans == INF ? -1 : ans) << endl;
}
