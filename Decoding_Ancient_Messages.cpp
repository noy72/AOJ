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
const int MAX_V = 10005;

class Edge{
	public:
		int to, cap, rev;
		Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};

class Flow{
	private:
		bool used[MAX_V];
		int level[MAX_V]; //sからの距離
		int iter[MAX_V]; //どこまで調べ終わったか
		int dfs(int v, int t, int f){
			if(v == t) return f;
			used[v] = true;
			rep(i,G[v].size()){
				Edge &e = G[v][i];
				if(not used[e.to] && e.cap > 0){
					int d = dfs(e.to, t, min(f, e.cap));
					if(d > 0){
						e.cap -= d;
						G[e.to][e.rev].cap += d;
						return d;
					}
				}
			}
			return 0;
		}
		int dfs_(int v, int t, int f){
			if(v == t) return f;
			for(int &i = iter[v]; i < G[v].size(); i++){
				Edge &e = G[v][i];
				if(e.cap > 0 && level[v] < level[e.to]){
					int d = dfs_(e.to, t, min(f, e.cap));
					if(d > 0){
						e.cap -= d;
						G[e.to][e.rev].cap += d;
						return d;
					}
				}
			}
			return 0;
		}
		void bfs(int s){
			memset(level, -1, sizeof(level));
			queue<int> que;
			level[s] = 0;
			que.push(s);
			while(not que.empty()){
				int v = que.front(); que.pop();
				rep(i,G[v].size()){
					Edge &e = G[v][i];
					if(e.cap > 0 && level[e.to] < 0){
						level[e.to] = level[v] + 1;
						que.push(e.to);
					}
				}
			}
		}
	public:
		vector<Edge> G[MAX_V];
		void addEdge(int from, int to, int cap){
			//cout << from << ' ' << to << ' ' << cap << endl;
			G[from].push_back(Edge(to, cap, static_cast<int>(G[to].size())));
			G[to].push_back(Edge(from, 0, static_cast<int>(G[from].size() - 1)));
		}
		int fordFulkerson(int s, int t){
			int flow = 0;
			while(true){
				memset(used, 0, sizeof(used));
				int f = dfs(s, t, INF);
				if(f == 0) return flow;
				flow += f;
			}
		}
		int dinic(int s, int t){
			int flow = 0;
			while(true){
				bfs(s);
				if(level[t] < 0) return flow;
				memset(iter, 0, sizeof(iter));
				int f;
				while( (f = dfs_(s, t, INF)) > 0){
					flow += f;
				}
			}
		}
};

void output(Flow& f, int n, vector<vector<char>>& m){
	vector<char> ans;
	rep(i,n){
		for(auto e : f.G[i]){
			//cout << i << ' ' << e.to << endl;
			if(e.cap == 0 and e.to != n + n){
				ans.emplace_back(m[i][e.to - n]);
				break;
			}
		}
	}

	sort(all(ans));
	for(auto i : ans) cout << i;
	cout << endl;
}

int main(){
	int n;
	cin >> n;

	vector<vector<char>> mat(n, vector<char>(n));
	map<char, vector<pair<int, int>>> m;
	rep(i,n){
		rep(j,n){
			char c;
			cin >> c;
			mat[i][j] = c;
			m[c].emplace_back(i,j);
		}
	}

	Flow f;
	int s = n + n, t = s + 1;
	rep(i,n){
		f.addEdge(s, i, 1);
		f.addEdge(i + n, t, 1);
	}

	int totalFlow = 0;
	auto solve = [&](char start, char end) -> bool {
		for(char i = start; i <= end; i++){
			for(auto p : m[i]){
				f.addEdge(p.first, p.second + n, 1);
			}

			totalFlow += f.fordFulkerson(s, t);
			if(totalFlow > 0){
				output(f,n,mat);
			}
			//show(totalFlow)
			if(totalFlow == n){
				output(f,n,mat);
				return true;
			}
		}
		return false;
	};

	if(not solve('A', 'Z')) solve('a', 'z');
}
