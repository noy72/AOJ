#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

typedef pair<pair<int, int>,int> P;

static const int MAX_V = 3005;

class Edge{
	public:
		//行き先、容量、コスト、逆辺
		int to, cap, cost, rev;
		Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev){}
		Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev){}
};


class Flow{
	private:
		vector<Edge> G[MAX_V];
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
		void addEdge(int from, int to, int cap){
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


class MinFlow{
	public:
		vector<vector<Edge>> G;
		int h[MAX_V]; //ポテンシャル
		int dist[MAX_V]; //最短距離
		int prev_v[MAX_V], prev_e[MAX_V]; //直前の頂点と辺

		MinFlow(){
			G = vector<vector<Edge>>(3000);
		}

		void addEdge(int from, int to, int cap, int cost){
			cout << from << ' ' << to << ' ' << cap << ' ' << cost << endl;
			G[from].emplace_back(Edge(to, cap, cost, static_cast<int>(G[to].size())));
			G[to].emplace_back(Edge(from, 0, -cost, static_cast<int>(G[from].size() - 1)));
		}

		int minCostFlow(int v, int s, int t, int f){
			int res = 0;
			fill(h, h + v, 0);
			while(f > 0){
				priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
				fill(dist, dist + v, INF);
				dist[s] = 0;
				q.push(make_pair(0, s));
				while(not q.empty()){
					pair<int, int> p = q.top(); q.pop();
					int u = p.second;
					if(dist[u] < p.first) continue;
					rep(i,G[u].size()){
						Edge &e = G[u][i];
						if(e.cap > 0 && dist[e.to] > dist[u] + e.cost + h[u] - h[e.to]){
							dist[e.to] = dist[u] + e.cost + h[u] - h[e.to];
							prev_v[e.to] = u;
							prev_e[e.to] = i;
							q.push(make_pair(dist[e.to], e.to));
						}
					}
				}
				if(dist[t] == INF){
					return -1;
				}
				rep(i,v) h[i] += dist[i];

				int d = f;
				for(int u = t; u != s; u = prev_v[u]){
					d = min(d, G[prev_v[u]][prev_e[u]].cap);
				}
				f -= d;
				res += d * h[t];
				for(int u = t; u != s; u = prev_v[u]){
					Edge &e = G[prev_v[u]][prev_e[u]];
					e.cap -= d;
					G[u][e.rev].cap += d;
				}
			}
			return res;
		}
};

int main(){
	int n;
	while(cin >> n, n){
		vector<P> t[105];
		vector<int> m(3000,0);
		rep(i,n - 1){
			cin >> m[i * 2 + 1];
			rep(j,m[i * 2 + 1]){
				int a, b, c;
				cin >> a >> b >> c;
				t[i].emplace_back(make_pair(make_pair(a,b),c));
			}
			sort(all(t[i]));
		}

		map<int,int> ma[105];
		int cnt = 0;
		rep(i,n - 1){
			rep(j,t[i].size()){
				if(ma[i].count(t[i][j].first.second)) continue;
				ma[i][t[i][j].first.second] = cnt++;
			}
			m[(i + 1) * 2] = ma[i].size();
		}
		//rep(i,10){ show(m[i]) }

		rep(i,(n - 1) * 2){
			m[i + 1] += m[i];
			//show(m[i + 1])
		}

		int g;
		cin >> g;

		Flow flow;
		MinFlow minFlow;
		int S = m[(n - 1) * 2], T = S + 1;
		show(S)
		rep(i,m[1]){
			flow.addEdge(S,i,1);
			minFlow.addEdge(S,i,1,0);
		}

		show("JI")
		rep(i,n - 1){
			range(j,m[i], m[i + 1]){
				range(k,m[i + 1], m[i + 2]){
					flow.addEdge(j, k, 1);
					minFlow.addEdge(j, k, 1, t[i][j - m[i]].second);
				}
			}
		}
		show("her")


		rep(i,n - 1){
			rep(j,t[n - 2].size()){
				flow.addEdge(m[i * 2] + j, ma[i][t[i + 1][j].first.second] + m[n - 1], 1);
				minFlow.addEdge(m[i * 2] + j, ma[i][t[i + 1][j].first.second] + m[n - 1], 1, 0);
			}
		}

		range(i,m[n - 1], m[n]){
			flow.addEdge(i, T, 1);
			minFlow.addEdge(i, T, 1, 0);
		}

		int f = min(g, flow.dinic(S,T));
		cout << f << ' ' << minFlow.minCostFlow(T + 1, S, T, f) << endl;
	}
}
