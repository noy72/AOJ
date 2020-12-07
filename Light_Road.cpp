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
int dis[N][N][15][15][4];

struct T{
	int c, y, x, p, q, d;
	T(int c, int y, int x, int p, int q, int d) : c(c),y(y),x(x),p(p),q(q),d(d) {}
	void tie(int& C, int& Y, int& X, int& P, int& Q, int& D){
		C=c;Y=y;X=x;P=p;Q=q;D=d;
	}

	bool operator < ( const T &right ) const {
		return c < right.c;
	}
	bool operator > ( const T &right ) const {
		return c > right.c;
	}
};

//typedef tuple<int,int,int,int,int,int> T;
int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};

int bfs(int h, int w, pair<int, int> s, pair<int, int> g){
	memset(dis, -1, sizeof(dis));
	dis[s.first][s.second][a][a][1] = 0;

	priority_queue<T, vector<T>, greater<T>> que;
	que.push(T(0, s.first, s.second, a, a, 1));

	while(not que.empty()){
		int c, y, x, p, q, d;
		T tmp = que.top(); que.pop();
		tmp.tie(c,y,x,p,q,d);
		dis[y][x][p][q][d] = c;
		if(y == g.first and x == g.second) return dis[y][x][p][q][d];

		rep(i,4){
			if((d + 2) % 4 == i) continue;

			int ny = y + dy[i];
			int nx = x + dx[i];
			int np = p, nq = q;
			int nc = c;
			
			if(d == 0 || d == 2){
				if((d + 1) % 4 == i){
					np = p - 1;
					nc++;
				}else if((d - 1 + 4) % 4 == i){
					nq = q - 1;
					nc++;
				}
			}else{
				if((d + 1) % 4 == i){
					nq = q - 1;
					nc++;
				}else if((d - 1 + 4) % 4 == i){
					np = p - 1;
					nc++;
				}
			}
			if(np < 0 || nq < 0) continue;

			if(nx < 0 || nx >= w || ny < 0 || ny >= h) continue;

			if(m[y][x] == 'S' and d != i) continue;
			if(m[ny][nx] == 'S' and i % 2 == 1) continue;
			//cout << ny << ' ' << nx << ' ' << np << ' ' << nq << endl;
				//cout << next.x << ' ' << next.y << ' ' << next.p << ' ' << next.q << ' ' << next.d << endl;
			if(dis[ny][nx][np][nq][i] == -1 && m[ny][nx] != '#'){
				//cout << next.x << ' ' << next.y << ' ' << next.p << ' ' << next.q << ' ' << next.d << endl;
				que.emplace(nc,ny,nx,np,nq,i);
			}
		}
	}

	return -1;
}


int main(){
	cin >> h >> w >> a;

	pair<int, int> s, g;
	rep(i,h) rep(j,w){
		cin >> m[i][j];
		if(m[i][j] == 'S') s = make_pair(i,j);
		if(m[i][j] == 'G') g = make_pair(i,j);
	}

	int ans = bfs(h, w, s, g);
	cout << (ans == INF ? -1 : ans) << endl;
}
