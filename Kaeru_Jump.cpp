#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

template<typename T>
ostream& operator << (ostream& os, vector<T>& v){
	rep(i,v.size()){ os << v[i] << (i == v.size() - 1 ? "" : " "); } return os;
}
template<typename T>
istream& operator >> (istream& is, vector<T>& v){
	for(T& x: v){ is >> x; } return is;
}

int h, w;

const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};
const char C[4] = {'R', 'U', 'L', 'D'};

struct Data{
	vector<vector<char>> c;
	int leves;
	int y, x, d;
	string s;
	Data(vector<vector<char>>& c, int leves, int y, int x, int d, string s) : c(c), leves(leves), y(y), x(x), d(d), s(s) {}
};

string bfs(Data& start){
	queue<Data> q;
	q.emplace(start);

	while(not q.empty()){
		Data p = q.front(); q.pop();
		//cout << p.y << ' ' << p.x <<' ' << p.d << endl;
		//for(auto i : p.c){ for(auto j : i){ cout << j << ' '; } cout << endl; } cout << endl;


		if(p.leves == 1) return p.s;
		if(p.s.size() >= 30) continue;

		rep(dir,4){
			if((p.d + 2) % 4 == dir) continue;
			int ny = p.y + dy[dir];
			int nx = p.x + dx[dir];
			if(ny < 0 || ny >= h || nx < 0 || nx >= w) continue;

			bool f = true;
			while(p.c[ny][nx] == '.'){
				ny += dy[dir];
				nx += dx[dir];
				if(ny < 0 || ny >= h || nx < 0 || nx >= w){
					f = false;
					break;
				}
			}
			if(not f) continue;

			p.c[p.y][p.x] = '.';
			q.emplace(p.c, p.leves - 1, ny, nx, dir, p.s + C[dir]);
			p.c[p.y][p.x] = 'o';
		}
	}
	assert(false);
	return "null";
}

int main(){
	cin >> h >> w;

	vector<vector<char>> c(h, vector<char>(w));
	int y, x, leves = 0;
	char dir;
	rep(i,h) rep(j,w){
		cin >> c[i][j];
		if(isupper(c[i][j])){
			y = i;
			x = j;
			dir = c[i][j];
			c[i][j] = 'o';
		}
		if(c[i][j] == 'o') leves++;
	}

	rep(i,4) if(C[i] == dir){
		Data data(c, leves, y, x, i, "");
		cout << bfs(data) << endl;
		return 0;
	}
}
