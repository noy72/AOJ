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


const int INF = 1e9;

class Edge{
	public:
		//行き先、容量、コスト、逆辺
		int to, cap, cost, rev;
		Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev){}
};

class MinCostFlow {
	int v;
	vector<vector<Edge>> G;
	vector<int> h; //ポテンシャル
	vector<int> dist; //最短距離
	vector<int> prev_v, prev_e; //直前の頂点と辺

	public:
	MinCostFlow(int n = 500) : v(n), G(n), h(n), dist(n), prev_v(n), prev_e(n) { }
	void output(int n, vector<string>& s){
		vector<pair<int, int>> p;
		vector<string> st;
		rep(i,n){
			for(auto j : G[i]){
				if(j.cap == 0){
					if(s[i][j.to - n] == '.'){
						p.emplace_back(i,j.to - n);
						st.emplace_back("write");
					}
				}else{
					if(s[i][j.to - n] == 'o'){
						p.emplace_back(i,j.to - n);
						st.emplace_back("erase");
					}
				}
			}
		}
		cout << p.size() << endl;
		rep(i,p.size()){
			cout << p[i].first + 1 << ' ' << p[i].second + 1 << ' ' << st[i] << endl;
		}
	}
	void addEdge(int from, int to, int cap, int cost){
		//cout << from << ' ' << to << ' ' << cap << ' ' << cost << endl;
		G[from].emplace_back(Edge(to, cap, cost, static_cast<int>(G[to].size())));
		G[to].emplace_back(Edge(from, 0, -cost, static_cast<int>(G[from].size() - 1)));
	}
	int bellmanFord(int s, int t, int f){
		int res = 0;
		while(f > 0){
			dist = vector<int>(v,INF);
			dist[s] = 0;
			bool update = true;
			while(update){
				update = false;
				rep(i,v){
					if(dist[i] == INF) continue;
					rep(j,G[i].size()){
						Edge &e = G[i][j];
						if(e.cap > 0 and dist[e.to] > dist[i] + e.cost){
							dist[e.to] = dist[i] + e.cost;
							prev_v[e.to] = i;
							prev_e[e.to] = j;
							update = true;
						}
					}
				}
			}
			if(dist[t] == INF){
				return -1;
			}

			int d = f;
			for(int u = t; u != s; u = prev_v[u]){
				d = min(d, G[prev_v[u]][prev_e[u]].cap);
			}
			f -= d;
			res += d * dist[t];
			for(int u = t; u != s; u = prev_v[u]){
				Edge &e = G[prev_v[u]][prev_e[u]];
				e.cap -= d;
				G[u][e.rev].cap += d;
			}
		}
		return res;
	}
	int dijkstra(int s, int t, int f){
		int res = 0;
		h = vector<int>(v, 0);
		while(f > 0){
			priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
			dist = vector<int>(v,INF);
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
	cin >> n;

	vector<vector<int>> w(n, vector<int>(n)), e(n, vector<int>(n));
	vector<string> s(n);
	rep(i,n) cin >> w[i];
	rep(i,n) cin >> e[i];
	rep(i,n) cin >> s[i];

	vector<vector<int>> d(n, vector<int>(n,0));
	int sum = 0;
	rep(i,n){
		rep(j,n){
			if(s[i][j] == 'o'){
				sum += e[i][j];
				d[i][j] = -e[i][j];
			}else{
				d[i][j] = w[i][j];
			}
		}
	}

	MinCostFlow f;
	int S = n + n, T = S + 1;
	rep(i,n) f.addEdge(S, i, 1, 0);
	rep(i,n) f.addEdge(i + n, T, 1, 0);
	rep(i,n) rep(j,n){
		f.addEdge(i, j + n, 1, d[i][j]);
	}

	cout << sum + f.bellmanFord(S, T, n) << endl;
	f.output(n,s);
}
