#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

#define int long long

class Grid{
	private:
		const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
		const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

		vector<int> x,y;
		void compress(vector<int> &v) {
			sort(v.begin(), v.end());
			v.erase(unique(v.begin(),v.end()),v.end());
		}
		int lb(vector<int> v, int num){
			return lower_bound(all(v), num) - v.begin();
		}
	public:
		static const int MAX_H = 500, MAX_W = 500;
		int grid[MAX_H][MAX_W] = {{0}};
		//~Grid(){ memset(grid, 0, sizeof(grid)); }
		void bfs(int x, int y, int c = -1){ //(x,y)からbfsしてグリッドにcを埋める
			if(grid[x][y] != 0) return;
			queue<pair<int, int>> q;
			q.push(make_pair(x,y));

			while(not q.empty()){
				pair<int, int> u = q.front(); q.pop();
				rep(i,4){
					int nx, ny;
					nx = u.first + dx[i];
					ny = u.second + dy[i];
					if(nx < 0 || nx >= MAX_W || ny < 0 || ny >= MAX_H) continue;
					if(grid[ny][nx] == 0){
						grid[ny][nx] = c;
						q.push(make_pair(nx,ny));
					}
				}
			}
		}
		void setXY(vector<int> a, vector<int> b){
			compress(a);
			x = a;
			compress(b);
			y = b;
		}
		void write(pair<int, int> a, pair<int, int> b){ //一直線の線を引く
			//show("rite")
			//cout << a.first << ' ' << a.second << endl;
			//cout << b.first << ' ' << b.second << endl;
			int ly = lb(y, a.second);
			int lx = lb(x, a.first);
			int ry = lb(y, b.second);
			int rx = lb(x, b.first);
			if(ly > ry) swap(ly, ry);
			if(lx > rx) swap(lx, rx);
			//cout << ly << ' ' << lx << ' ' << ry << ' ' << rx << endl;
			range(i,ly * 2,ry * 2 + 1){ //外側
				grid[i][lx * 2] = 1;
				grid[i][rx * 2] = 1;
			}
			range(j,lx * 2, rx * 2 + 1){
				grid[ly * 2][j] = 1;
				grid[ry * 2][j] = 1;
			}
		}
		void overWrite(Grid a){
			rep(i,MAX_H){
				rep(j,MAX_W){
					if(a.grid[i][j] != -1){
						grid[i][j] = -1;
					}
				}
			}
		}
		int sum(){
			int res = 0;
			//for(auto i : y){ show(i) }
			range(i,0,y.size() - 1){
				range(j,0,x.size() - 1){
					if(grid[i * 2 + 1][j * 2 + 1] == 0){
						//show(x.size())
						//	show(y.size())
						//cout << i << ' ' << j << endl;
						//show(y[i])
							//show(x[j])
						//	show(y[i - 1])
						//show(y[i] - y[i - 1])
						//int tmpy = i - 1 < 0 ? 20000 : y[i - 1];
						//int tmpx = j - 1 < 0 ? 20000 : x[j - 1];
						res += (y[i + 1] - y[i]) * (x[j + 1] - x[j]);
						//show(res)
					}
				}
			}
			return res;
		}
		void output(){
			rep(i,10){
				rep(j,10){
					if(grid[i][j] == 0) cout << "_ ";
					else if(grid[i][j] == -1) cout << "# ";
					else cout << "* ";
				}
				cout << endl;
			}
		}
};

signed main(){
	int n;
	while(cin >> n,n){
		vector<int> x, y;
		vector<pair<int, int>> p, r;
		rep(i,n){
			int a, b;
			cin >> a >> b;
			a += 20000;
			b += 20000;
			x.emplace_back(a);
			y.emplace_back(b);
			p.emplace_back(make_pair(a,b));
		}
		rep(i,4){
			int a, b;
			cin >> a >> b;
			a += 20000;
			b += 20000;
			x.emplace_back(a);
			y.emplace_back(b);
			r.emplace_back(make_pair(a,b));
		}
		//x.emplace_back(20000);
		//y.emplace_back(20000);

		Grid win, cur;
		//win.output();
		win.setXY(x,y);
		cur.setXY(x,y);

		rep(i,n){
			win.write(p[i], p[(i + 1) % n]);
		}
		rep(i,4){
			cur.write(r[i], r[(i + 1) % 4]);
		}
		win.bfs(0,0);
		cur.bfs(0,0);
		win.bfs(400,400);
		cur.bfs(400,400);
		//win.output();
		//cur.output();

		win.overWrite(cur);
		//win.output();

		cout << win.sum() << endl;
	}
}
