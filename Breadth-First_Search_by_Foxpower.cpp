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

#define int long long

class LCA{
	private:
		vector<vector<int>> g, parent;
		int n, root, log_n;
		bool inited;
		vector<int> depth;
		void dfs(int v, int p, int d){
			parent[0][v] = p;
			depth[v] = d;
			rep(i,g[v].size()){
				if(g[v][i] != p) dfs(g[v][i], v, d + 1);
			}
		}
		void init(){
			inited = true;
			dfs(root, -1, 0);
			rep(k,log_n - 1){
				rep(i,n){
					if(parent[k][i] < 0) parent[k + 1][i] = -1;
					else parent[k + 1][i] = parent[k][ parent[k][i] ];
				}
			}
		}
	public:
		LCA(int n, int root = 0) : g(n), parent(log2(n) + 1, vector<int>(n)), n(n), root(root), log_n(log2(n) + 1), inited(false), depth(n) { }
		void addEdge(int u, int v){
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
		int get(int u, int v){
			if(not inited) init();
			if(depth[u] > depth[v]) swap(u, v);
			rep(k,log_n){
				if( (depth[v] - depth[u]) >> k & 1){
					v = parent[k][v];
				}
			}
			if(u == v) return u;
			for(int k = log_n - 1; k >= 0; k--){
				if(parent[k][u] != parent[k][v]){
					u = parent[k][u];
					v = parent[k][v];
				}
			}
			return parent[0][u];
		}
};

signed main(){
	int n;
	cin >> n;

	vector<vector<int>> g(n);
	LCA lca(n);
	rep(i,n - 1){
		int p;
		cin >> p;
		p--;
		g[p].emplace_back(i + 1);
		lca.addEdge(i + 1, p);
	}

	queue<int> q;
	q.emplace(0);

	vector<int> dis(n);
	dis[0] = 0;

	vector<int> ord;
	while(not q.empty()){
		int pos = q.front(); q.pop();
		ord.emplace_back(pos);
		for(auto to : g[pos]){
			dis[to] = dis[pos] + 1;
			q.emplace(to);
		}
	}

	int ans = 0;
	rep(i,ord.size() - 1){
		ans += dis[ord[i]] + dis[ord[i + 1]] - 2 * dis[lca.get(ord[i], ord[i + 1])];
	}
	cout << ans << endl;
}
