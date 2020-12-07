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

typedef vector<vector<bool>> Map;
typedef tuple<pair<int, int>, Map, int> T;

const int h = 20, w = 17;
const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

int ans;
Map c;

bool impossible(int y, Map& c){
	vector<bool> no(h,0);
	range(i,y + 1,18){
		bool f = false;
		rep(j,w){
			if(c[i][j]) f = true;
		}
		if(not f) no[i] = true;
	}
	rep(i,h - 1){
		if(no[i] and no[i + 1]) return true;
	}
	return false;
}

map<Map, map<pair<int, int>, int>> memo;

void dfs(int y, int x, int cost){
	if(ans <= cost) return;
	if(memo.count(c) and memo[c].count(make_pair(y,x)) and memo[c][make_pair(y,x)] <= cost) return;
	memo[c][make_pair(y,x)] = cost;

	if(y == 18 or y == 19){
		ans = min(ans, cost);
		return;
	}

	if(impossible(y, c)) return;

	rep(i,8){
		int ny = y + dy[i];
		int nx = x + dx[i];
		if(ny < 0 || ny >= h || nx < 0 || nx >= w) continue;
		if((nx == 0 && ny <= 18) or (nx == w - 1 && ny <= 18)) continue;
		if(c[ny][nx] == 1){
			vector<pair<int, int>> tmp;
			while(true){
				if(ny < 0 || ny >= h || nx < 0 || nx >= w) {
					ny = -1;
					break;
				}
				if((nx == 0 && ny <= 18) or (nx == w - 1 && ny <= 18)){
					ny = -1;
					break;
				}
				if(c[ny][nx] == 0) break;
				tmp.emplace_back(ny,nx);
				//pc[ny][nx] = 0;
				ny = ny + dy[i];
				nx = nx + dx[i];
			}
			if(ny == -1) continue;

			for(auto i : tmp) c[i.first][i.second] = 0;
			dfs(ny, nx, cost + 1);
			for(auto i : tmp) c[i.first][i.second] = 1;
		}
	}
}

int main(){
	pair<int, int> s;
	c = Map(h, vector<bool>(w));
	rep(i,h - 1){
		rep(j,w - 2){
			char a;
			cin >> a;
			if(a == 'X') c[i][j + 1] = 1;
			else c[i][j + 1] = 0;
			if(a == 'O'){
				s = make_pair(i,j + 1);
			}
		}
	}

	ans = 1e9;
	dfs(s.first, s.second, 0);
	cout << (ans == 1e9 ? -1 : ans) << endl;
}
