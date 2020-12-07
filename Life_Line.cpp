#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;
//const int INF = 1e8;

template<typename T>
ostream& operator << (ostream& os, vector<T>& v){
	rep(i,v.size()){ os << v[i] << (i == v.size() - 1 ? "" : " "); } return os;
}
template<typename T>
istream& operator >> (istream& is, vector<T>& v){
	for(T& x: v){ is >> x; } return is;
}

vector<vector<int>> g;
const int dy[16] = { 0,-1, 0, 1, 1,-1};
const int dx[16] = { 1, 0,-1, 0, 1,-1};

void bfs(int k, int t, vector<bool>& used, const vector<int>& node){
	queue<int> q;
	q.emplace(k);
	while(not q.empty()){
		int pos = q.front(); q.pop();
		used[pos] = true;
		for(auto to : g[pos]){
			if(used[to] or node[to] != t) continue;
			q.emplace(to);
		}
	}
}

vector<vector<int>> getGraph(int n, int v){
	vector<vector<int>> res(v), mat(n, vector<int>(n, -1));
	int ver = 0;
	rep(i,n){
		for(int j = 0; j <= i; j++, ver++){
			mat[i][j] = ver;
		}
	}
	rep(i,n){
		rep(j,i + 1){
			rep(d,6){
				int ny = i + dy[d];
				int nx = j + dx[d];
				if(ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
				if(mat[ny][nx] == -1) continue;
				res[mat[ny][nx]].emplace_back(mat[i][j]);
				res[mat[i][j]].emplace_back(mat[ny][nx]);
			}
		}
	}
	return res;
}

int main(){
	int n, c;
	while(cin >> n >> c,n||c){
		int v = (1 + n) * n / 2;
		g = getGraph(n, v);

		vector<int> node(v);
		cin >> node;

		int ans = -1e8;
		rep(i,v){
			vector<bool> used(v,0);
			if(node.at(i) == 0){
				node.at(i) = c;
				rep(j,v){
					if(node.at(j) == 0){
						for(auto k : g.at(j)){
							if(node[k] == 0) continue;
							bfs(k, node[k], used, node);
						}
					}
				}
				int sum = 0;
				rep(j,v){
					if(used[j] or node[j] == 0) continue;
					if(node[j] == c) sum--;
					else sum++;
				}
				ans = max(ans, sum);
				node.at(i) = 0;
			}
		}
		cout << ans << endl;
	}
}
