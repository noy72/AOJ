#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

template<typename T>
istream& operator >> (istream& is, vector<T>& vec){
	for(T& x: vec) is >> x;
	return is;
}

template<typename T>
ostream& operator << (ostream& os, vector<T>& v){
	rep(i,v.size()){
		if(i) cout << ' ';
		os << v[i];
	}
	return os;
}

typedef tuple<int,int,int> T;

vector<vector<char>> room;
vector<vector<int>> c, on, off;
vector<vector<int>> pre;

const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

int bfs(int h, int w, pair<int, int> s, pair<int, int> g){
	vector<vector<int>> dis(h, vector<int>(w, INF));
	vector<vector<bool>> used(h, vector<bool>(w,false));
	dis[s.first][s.second] = 0;

	queue<T> q;
	q.emplace(T(s.first, s.second, pre[s.first][s.second]));

	vector<vector<pair<int, int>>> preVer(h, vector<pair<int, int>>(w,make_pair(-1,-1)));
	while(not q.empty()){
		int y, x, time;
		tie(y, x, time) = q.front(); q.pop();
		used[y][x] = true;
		rep(d,4){
			int ny = y + dy[d];
			int nx = x + dx[d];
			if(ny < 0 || ny >= h || nx < 0 || nx >= w) continue;
			if(room[ny][nx] == '#' or used[ny][nx] == true) continue;

			int cost = dis[y][x] + on[ny][nx] + off[ny][nx];
			if(pre[ny][nx] != -1){
				cost = min(cost, dis[y][x] + (time + 1 - pre[ny][nx]) * c[ny][nx]);
			}
			if(dis[ny][nx] > cost){
				preVer[ny][nx] = make_pair(y,x);
				dis[ny][nx] = cost;
				q.emplace(ny, nx, time + 1);
			}
		}
	}

	vector<pair<int, int>> path;
	path.emplace_back(g);
	int time = pre[s.first][s.second];
	int y, x;
	tie(y,x) = g;
	while(preVer[y][x].first != -1){
		tie(y,x) = preVer[y][x];
		path.emplace_back(y,x);
	}
	for(auto i = path.rbegin(); i != path.rend(); i++){
		pre[i->first][i->second] = time++;
	}
	//for(auto i : pre){ cout << i << endl; }
	return dis[g.first][g.second];
}

int main(){
	int h, w, m;
	cin >> h >> w >> m;

	room = vector<vector<char>>(h, vector<char>(w,'.'));
	c = vector<vector<int>>(h, vector<int>(w,0));
	on = vector<vector<int>>(h, vector<int>(w,0));
	off = vector<vector<int>>(h, vector<int>(w,0));
	pre = vector<vector<int>>(h, vector<int>(w,-1));
	cin >> room >> c >> on >> off;

	vector<pair<int, int>> p(m);
	rep(i,m){
		cin >> p[i].first >> p[i].second;
	}

	int y, x;
	tie(y, x) = p[0];
	int ans = on[y][x] + off[y][x];
	pre[y][x] = 0;

	rep(i,m - 1){
		ans += bfs(h, w, p[i], p[i + 1]);
	}
	cout << ans << endl;
}
