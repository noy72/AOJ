#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

class Edge{
	public:
		int to, cap, rev;
		Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};

class Flow{
	private:
		const int v;
		vector<vector<Edge>> G;
		vector<bool> used;
		vector<int> level, iter; // s からの距離、どこまで調べ終わったか
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
			level = vector<int>(v, -1);
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
		Flow(int v) : v(v + 2), G(v + 2) { }
		void addEdge(int from, int to, int cap){
			G[from].push_back(Edge(to, cap, static_cast<int>(G[to].size())));
			G[to].push_back(Edge(from, cap, static_cast<int>(G[from].size() - 1)));
		}
		int addCapacity(int s, int t, int u, int v){
			for(auto& e : G[u]){
				if(e.to == v){
					e.cap = G[v][e.rev].cap = 1;
					return fordFulkerson(s, t);
				}
			}
			assert(false and "invalid u, v");
			return -INF;
		}
		int subCapacity(int s, int t, int u, int V){
			for(auto& e : G[u]){
				if(e.to == V){
					int d = e.cap;
					e.cap = G[V][e.rev].cap = 0;
					if(d == 1) return 0;
					if(d == 2){
						used = vector<bool>(v,0);
						if(dfs(V, u, 1)) return 0;
						used = vector<bool>(v,0);
						dfs(t, u, 1);
						used = vector<bool>(v,0);
						dfs(V, s, 1);
					}else{
						used = vector<bool>(v,0);
						if(dfs(u, V, 1)) return 0;
						used = vector<bool>(v,0);
						dfs(t, V, 1);
						used = vector<bool>(v,0);
						dfs(u, s, 1);
					}
					return -1;
				}
			}
			assert(false);
			return -INF;
		}

		int fordFulkerson(int s, int t, int F = INF){
			int flow = 0;
			while(true){
				used = vector<bool>(v,0);
				int f = dfs(s, t, F);
				if(f == 0) return flow;
				flow += f;
			}
		}
		int dinic(int s, int t){
			int flow = 0;
			while(true){
				bfs(s);
				if(level[t] < 0) return flow;
				iter = vector<int>(v,0);
				int f;
				while( (f = dfs_(s, t, INF)) > 0){
					flow += f;
				}
			}
		}
};


int main(){
	int n, e, q;
	cin >> n >> e >> q;

	Flow flow(n);
	vector<vector<bool>> use(n, vector<bool>(n,false));
	rep(i,e){
		int f, t;
		cin >> f >> t;
		f--; t--;
		flow.addEdge(f, t, 1);
		use[t][f] = use[f][t] = true;
	}

	vector<int> com(q), a(q), b(q);
	rep(i,q){
		cin >> com[i] >> a[i] >> b[i];
		a[i]--; b[i]--;
		if(not use[a[i]][b[i]]){
			flow.addEdge(a[i], b[i], 0);
			use[a[i]][b[i]] = use[b[i]][a[i]] = true;
		}
	}

	int s = n, t = s + 1;
	flow.addEdge(s,0,INF);
	flow.addEdge(n - 1, t, INF);

	int ans = flow.fordFulkerson(s, t);
	rep(i,q){
		if(com[i] == 1) ans += flow.addCapacity(s, t, a[i], b[i]);
		else ans += flow.subCapacity(s, t, a[i], b[i]);
		
		cout << ans << endl;
	}
}
