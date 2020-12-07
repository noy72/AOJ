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

typedef vector<vector<char>> Line;
typedef vector<Line> Block;

const int dy[] = { 0, 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[] = { 0, 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

int h, n;
int ans;

Block getMovedBlock(const Block& b, int dir){
	Block res(2, Line(2, vector<char>(2, '.')));
	rep(i,2){
		rep(j,2){
			rep(k,2){
				if(b[i][j][k] == '#'){
					int ny = j + dy[dir];
					int nx = k + dx[dir];
					if(ny < 0 || ny >= 2 || nx < 0 || nx >= 2) return Block();
					res[i][ny][nx] = '#';
				}
			}
		}
	}
	return res;
}

bool canDown(const vector<Line>& m, const Block& b, int h){
	rep(i,2){
		if(h == m.size() and i == 1) break;
		rep(j,2){
			rep(k,2){
				if(m[h - 1 + i][j][k] == '#' and b[i][j][k] == '#') {
					return false;
				}
			}
		}
	}
	return true;
}

void output(Block d){
	show("JI")
	rep(i,2){
		rep(j,2){
			rep(k,2){
				cout << d[i][j][k];
			}
		cout << endl;
		}
	}
	show("JI")
}

void dfs(vector<Line>& m, const vector<Block>& d, int idx, int cnt){
	if(idx == n){
		ans = max(ans, cnt);
		return;
	}

	//show(idx)
	const auto& b = d[idx];
	//output(b);

	vector<Line> save = m;
	rep(dir,9){
		Block moved = getMovedBlock(b, dir);
		//show(dir)
		if(moved.empty()) continue;

		//output(moved);

		int h = 1;
		for(int i = m.size(); i >= 1; i--){
			if(not canDown(m, moved, i)){
				h = i + 1;
				break;
			}
		}

		if(h == m.size() + 1){
			m.emplace_back(moved[0]);
			m.emplace_back(moved[1]);
		}else if(h == m.size()){
			rep(j,2){
				rep(k,2){
					if(moved[0][j][k] == '#') m[h - 1][j][k] = '#';
				}
			}
			m.emplace_back(moved[1]);
		}else{
			rep(i,2){
				rep(j,2){
					rep(k,2){
						if(moved[i][j][k] == '#') m[h - 1 + i][j][k] = '#';
					}
				}
			}
		}

		int deleteLine = 0;
		for(auto it = next(m.begin(), 1); it != m.end();){
			Line& tmp = *it;
			if(tmp[0][0] == '#' and tmp[0][1] == '#' and tmp[1][0] == '#' and tmp[1][1] == '#'){
				it = m.erase(it);
				deleteLine++;
			}else{
				it++;
			}
		}

		//rep(i,m.size()){ rep(j,2){ rep(k,2){ cout << m[i][j][k]; } cout << endl; } }

		dfs(m, d, idx + 1, deleteLine + cnt);
		m = save;
	}
}

int main(){
	while(cin >> h >> n, h||n){
		vector<Line> m;
		m.emplace_back(Line(2, vector<char>(2, '#')));

		rep(i,h){
			Line a(2, vector<char>(2));
			rep(i,2){
				rep(j,2){
					cin >> a[i][j];
				}
			}
			m.emplace_back(a);
		}

		vector<Block> d;
		rep(i,n){
			Block a(2, Line(2, vector<char>(2)));
			rep(i,2){
				rep(j,2){
					rep(k,2){
						cin >> a[i][j][k];
					}
				}
			}
			d.emplace_back(a);
		}

		ans = 0;
		dfs(m,d,0,0);
		cout << ans << endl;
	}
}
