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

const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

int n;

typedef tuple<int,int,int> T;


bool getBit(int b, int y, int x){
	return b >> (y * n + x) & 1;
}
void setBit(int& b, int y, int x){
	b |= 1 << (y * n + x);
}

int bfs(int bit, int sy, int sx){
	map<T, int> memo;

	queue<T> q;
	q.emplace(bit, sy, sx);

	while(not q.empty()){
		int s, y, x;
		tie(s, y, x) = q.front(); q.pop();

		if(s == 0) return memo[T(s, y, x)];

		rep(vd, 8){
			int vy = y + dy[vd];
			int vx = x + dx[vd];
			if(getBit(s, vy, vx)) continue;
			if(vy < 0 || vy >= n || vx < 0 || vx >= n) continue;

			int nxt = 0;
			rep(i,n){
				rep(j,n){
					if(vy == i and vx == j) continue;

					int cnt = 0;
					rep(d,8){
						int ny = i + dy[d];
						int nx = j + dx[d];
						if(ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
						if(getBit(s, ny, nx)) cnt++;
						if(vy == ny and vx == nx) cnt++;
					}

					if((cnt == 2 or cnt == 3) and getBit(s, i, j) == 1){
						setBit(nxt, i, j);
					}else if(cnt == 3 and getBit(s, i, j) == 0){
						setBit(nxt, i, j);
					}
				}
			}

			auto t = T(nxt, vy, vx);
			if(memo.count(t) and memo[t] > memo[T(s, y, x)] + 1){
				memo[t] = memo[T(s, y, x)] + 1;
				q.emplace(t);
			}else if(not memo.count(t)){
				memo[t] = memo[T(s, y, x)] + 1;
				q.emplace(t);
			}
		}
	}

	return -1;
}

int main(){
	while(cin >> n,n){
		int bit = 0, y, x;
		rep(i,n){
			rep(j,n){
				char a;
				cin >> a;
				if(a == '#'){
					setBit(bit, i, j);
				}
				if(a == '@'){
					y = i;
					x = j;
				}
			}
		}

		cout << bfs(bit, y, x) << endl;
	}
}
