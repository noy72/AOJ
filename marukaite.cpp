#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;


const int MAX_V = 10005;

class Edge{
	public:
		//行き先、容量、コスト、逆辺
		int to, cap, cost, rev;
		Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev){}
};

vector<vector<Edge>> G(MAX_V);
int h[MAX_V]; //ポテンシャル
int dist[MAX_V]; //最短距離
int prev_v[MAX_V], prev_e[MAX_V]; //直前の頂点と辺

void addEdge(int from, int to, int cap, int cost){
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

int main(){
	int n;
	cin >> n;

	int w[105][105], e[105][105];
	rep(i,n) rep(j,n) cin >> w[i][j];
	rep(i,n) rep(j,n) cin >> e[i][j];

		int t[105][105];
		string s[105];
		rep(i,n) cin >> s[i];

		rep(i,n){
			rep(j,n){
				int sum = 0;
				if(s[i][j] == '.'){
					sum += w[i][j] * 2;
				}
				rep(k,n){
					if(k == j) continue;
					if(s[i][k] == 'o'){
						sum += e[i][k];
					}
				}
				rep(k,n){
					if(k == i) continue;
					if(s[k][j] == 'o'){
						sum += e[i][k];
					}
				}
				t[i][j] = sum;
			}
		}

	//rep(i,n){ rep(j,n){ cout << t[i][j] << ' '; } cout << endl; }

	const int MID = 0;
	const int LEFT = n * n + n;
	const int RIGHT = n * n;

	int S = n * n + 2 * n + 1;
	int T = S - 1;
	rep(i,n){
		addEdge(S, LEFT + i, 1, 0);
		//cout << S << ' ' << LEFT + i << endl;
	}
	rep(i,n){
		rep(j,n){
			addEdge(LEFT + i, MID + n * j + i, 1, 0);
			//cout << LEFT + i << ' ' << MID + n * j + i << endl;
		}
	}
	rep(i,n * n){
		addEdge(MID + i, RIGHT + i / n, 1, t[i / n][i % n]);
		//cout << MID + i << ' ' << RIGHT + i / n << endl;
	}
	rep(i,n){
		addEdge(RIGHT + i, T, 1, 0);
		//cout << RIGHT + i << ' ' << T << endl;
	}
	cout << minCostFlow(S, S, T, n) / 2 << endl;

	int cnt = 0;
	rep(i,n * n){
		if(G[i][0].cap == 1){
			if(s[i / n][i % n] == '.'){
				cnt++;
			}
		}else{
			if(s[i / n][i % n] == 'o'){
				cnt++;
			}
		}
	}
	cout << cnt << endl;

	rep(i,n * n){
		if(G[i][0].cap == 1){
			if(s[i / n][i % n] == '.'){
				cout << i / n + 1 << ' ' << i % n + 1 << ' ' << "write" << endl;
			}
		}else{
			if(s[i / n][i % n] == 'o'){
				cout << i / n + 1 << ' ' << i % n + 1 << ' ' << "erase" << endl;
			}
		}
	}
}
