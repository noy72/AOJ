#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e9;
using namespace std;

class UnionFind{
	private:
		vector<int> par, depth;
	public:
		UnionFind() {}
		UnionFind(int n){
			init(n);
		}
		void init(int n){
			par = vector<int>(n);
			depth = vector<int>(n);
			rep(i,n){
				par[i] = i;
				depth[i] = 0;
			}
		}
		int find(int x){
			if(par[x] == x){
				return x;
			}else {
				return par[x] = find(par[x]);
			}
		}
		void unite(int x, int y){
			x = find(x);
			y = find(y);
			if(x == y) return;

			if(depth[x] < depth[y]){
				par[x] = y;
			}else{
				par[y] = x;
				if(depth[x] == depth[y]) depth[x]++;
			}
		}
		bool same(int x, int y){
			return find(x) == find(y);
		}
};

struct Edge{
	int u, v, cost, id;
	Edge() {}
	Edge(int u, int v, int cost) : u(u), v(v), cost(cost) {}

	bool operator < ( const Edge &right ) const {
		return cost < right.cost ? 1 : (cost == right.cost ? (u < right.u ? 1 : (u == right.u ? (v == right.v) : 0)) : 0);
	}
};

class Kruskal{
	private:
		static const int MAX_E = 50005;
		UnionFind unionFind;
	public:
		int v;
		vector<Edge> edge;
		vector<int> mst; //edge[ mst[i] ] := 最小全域木を構築するi番目の辺
		Kruskal(vector<Edge>& e, int _v){
			v = _v;
			unionFind.init(v);
			edge = e;
			sort(all(edge));
		}
		void reset(int v){
			unionFind.init(v);
		}
		long long solve(vector<bool> sinked){
			long long res = 0;
			rep(i,edge.size()){
				Edge c = edge[i];
				if(not unionFind.same(c.u, c.v) and not sinked[c.u] and not sinked[c.v]){
					unionFind.unite(c.u, c.v);
					res += c.cost;
					mst.emplace_back(i);
				}
			}
			int b = 0;
			rep(i,v){
				if(sinked[i]) continue;
				b = i;
				break;
			}
			rep(i,v){
				if(not unionFind.same(b,i) and not sinked[i]){
					return INF;
				}
			}
			return res;
		}
};

int main(){
	int n, m;
	while(cin >> n >> m, n||m){
		map<int,vector<int>> h;
		rep(i,n){
			int a;
			cin >> a;
			h[a].emplace_back(i);
		}

		vector<Edge> e(m);
		rep(i,m){
			int a, b, c;
			cin >> a >> b >> c;
			e[i] = Edge{a - 1, b - 1, c};
		}

		Kruskal krus(e, n);
		vector<bool> sinked(n,0);
		if(krus.solve(sinked) == INF){
			cout << 0 << endl;
			continue;
		}

		for(auto it = h.begin(); it != h.end(); it++){
			krus.reset(n);
			vector<bool> cp = sinked;
			for(auto p : it->second) cp[p] = true;
			//for(auto i : cp) cout << i << ' '; cout << endl;
			if(krus.solve(cp) == INF){
				break;
			}
			sinked = cp;
		}


		krus.reset(n);
		//for(auto i : sinked) cout << i << ' '; cout << endl;
		long long ans = 0;
		for(auto it = h.rbegin(); it != h.rend(); it++){
			for(auto p : it->second) sinked[p] = false;
		//for(auto i : sinked) cout << i << ' '; cout << endl;
			ans += krus.solve(sinked);
			//show(ans)
			assert(ans <= INF);
		}
		cout << ans << endl;
	}
}
