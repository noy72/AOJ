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

const int INF = 1e8;

const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

vector<pair<int, int>> getBlock(vector<string>& v, int& h, int& w, int y, int x, int num, vector<vector<bool>>& used, bool f){
	if(used[y][x]) return vector<pair<int, int>>();
	used[y][x] = true;

	vector<pair<int, int>> res;
	rep(d,4){
		int ny = y + dy[d];
		int nx = x + dx[d];
		if(ny < 0 || ny >= h || nx < 0 || nx >= w) continue;

		if((v[ny][nx] == num) xor f) continue;

		for(auto p : getBlock(v, h, w, ny, nx, num, used, f)){
			res.emplace_back(p);
		}
	}
	return res;
}


void solve(vector<string>& v, int& h, int& w, int posy, int posx){
	vector<vector<bool>> used(h, vector<bool>(w, false));
	auto block = getBlock(v, h, w, posy, posx, v[posy][posx] - '0', used, true);

	int l = INF, r = -INF;
	for(auto p : block){
		if(v[p.first + 1][p.second] == '.') continue;
		l = min(l, p.second);
		r = max(r, p.second);
	}

	for(auto& p : block){
		if(p.first - 1 < 0) continue;
		if(v[p.first - 1][p.second] == v[posy][posx]) continue;

	}
}

int main(){
	int h, w;
	while(cin >> h >> w, h||w){
		h++;
		vector<string> v(h);
		rep(i,h) cin >> v[i];
		rep(i,w) v[h] += '@'; // 地面

		rep(i,h){
			rep(j,w){
				if(v[i][j] == '.') continue;
				solve(v,h,w,i,j);
			}
		}
	}
}
