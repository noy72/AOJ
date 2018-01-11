#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

template <typename X, typename T>
auto vectors(X x, T a) {
	return vector<T>(x, a);
}

template <typename X, typename Y, typename Z, typename... Zs>
auto vectors(X x, Y y, Z z, Zs... zs) {
	auto cont = vectors(y, z, zs...);
	return vector<decltype(cont)>(x, cont);
}

#define int long long

const int MAX_V = 805;

class Edge{
	public:
		int to, dis;
		Edge(){}
		Edge(int to, int dis): to(to), dis(dis)  {}
};

vector<Edge> g[MAX_V];
int dis[MAX_V];

void bfs(int s, int n){
	queue<int> q;

	rep(i,n) dis[i] = INF;
	dis[s] = 0;
	q.push(s);

	int u;
	while(not q.empty()){
		u = q.front(); q.pop();
		rep(i,g[u].size()){
			Edge e = g[u][i];
			if(dis[e.to] == INF){
				dis[e.to] = dis[u] + e.dis;
				q.push(e.to);
			}
		}
	}
}

int solve(int n, int s){
	int maxi = 0;
	int tgt = 0; //ある点sから最も遠い点

	bfs(s, n);
	rep(i,n){
		if(dis[i] == INF) continue;
		if(maxi < dis[i]){
			maxi  = dis[i];
			tgt = i;
		}
	}

	bfs(tgt, n);
	maxi = 0; //tgtから最も遠い接点の距離maxi
	rep(i,n){
		if(dis[i] == INF) continue;
		maxi = max(maxi, dis[i]);
	}

	return maxi;
}

signed main(){
	int n;
	while(cin >> n,n){
		rep(i,MAX_V) g[i].clear();
		memset(dis, 0, sizeof(dis));

		vector<int> a(n), c(n);
		rep(i,n - 1) cin >> a[i];
		rep(i,n - 1) cin >> c[i];

		rep(i,n - 1){
			g[i + 1].emplace_back(Edge{a[i] - 1, c[i]});
			g[a[i] - 1].emplace_back(Edge{i + 1, c[i]});
		}

		vector<int> leves;
		int s = -1;
		rep(cur,n){
			if(g[cur].size() == 1){
				leves.emplace_back(cur);
			}else{
				s = cur;
			}
		}

		int leaf = 0;
		for(auto i : leves){
			leaf += g[i].back().dis;

			int to = g[i].back().to;
			g[i].clear();
			for(auto it = g[to].begin(); true; it++){
				if((*it).to == i){
					g[to].erase(it);
					break;
				}
			}
		}

		//for(auto i : g[1]){ cout << i.to << endl; }
		//for(auto i : g[2]){ cout << i.to << endl; }

		int sum = accumulate(all(c), 0);
		//cout << sum << ' ' << leaf << ' ' << solve(n,s) << endl;
		cout << sum * 3 - 2 * leaf - solve(n,s) << endl;
	}
}
