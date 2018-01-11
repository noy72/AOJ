#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

const int N = 25;
struct Point{ int x, y; };

int w, h;
int cost[N][N];
char m[N][N];
vector<Point> t(N);


int dy[4] = {0,1,0,-1}, dx[4] = {1,0,-1,0};

int bfs(int h, int w, Point p, Point g){
	int dis[N][N];
	queue<Point> q;
	rep(i,N) rep(j,N) dis[i][j] = INF;

	dis[p.y][p.x] = 0;
	q.push(p);

	Point u;
	while(not q.empty()){
		u = q.front(); q.pop();
		rep(i,4){
			Point next;
			next.x = u.x + dx[i];
			next.y = u.y + dy[i];
			if(next.x < 0 || next.x >= w || next.y < 0 || next.y >= h) continue;
			if(dis[next.y][next.x] == INF && m[next.y][next.x] != 'x'){
				dis[next.y][next.x] = dis[u.y][u.x] + 1;
				q.push(next);
			}
		}
	}
	return dis[g.y][g.x];
}

int main(){
	while(cin >> w >> h, w){
		t.clear();
		Point s;
		rep(i,h) rep(j,w){
			cin >> m[i][j];
			if(m[i][j] == 'o') s = Point{j,i};
			else if(m[i][j] == '*') t.emplace_back(Point{j,i});
		}
		t.emplace_back(s);

		rep(i,t.size()){
			rep(j,t.size()){
				cost[i][j] = bfs(h, w, t[i], t[j]);
			}
		}

		vector<int> v(t.size() - 1);
		iota(all(v),0);

		int ans = INF;
		do{
			int cnt = 0;
			rep(i,v.size() - 1){
				cnt += cost[v[i]][v[i + 1]];
			}
			cnt += cost[t.size() - 1][v[0]];
			ans = min(ans, cnt);
		}while(next_permutation(all(v)));

		cout << (ans == INF ? -1 : ans) << endl;
	}
}
