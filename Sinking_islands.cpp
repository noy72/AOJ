#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e9;
using namespace std;

class UnionFind{
	static const int gmax_n = 505;

	int par[gmax_n]; //親
	int depth[gmax_n];//木の深さ

	public:
	void init(int n){
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

bool connected(int n, UnionFind uni){
	rep(i, n){
		if(not uni.same(0,i)) return false;
	}
	return true;
}

struct Edge{
	int u, v, cost, id;
	Edge() {}
	Edge(int u, int v, int cost) : u(u), v(v), cost(cost) {}

	bool operator < ( const Edge &right ) const {
		if(cost < right.cost){
			return 1;
		}else if(cost == right.cost){
			if(u < right.u){
				return 1;
			}else if(u == right.u){
				if(v == right.v){
					return 1;
				}else {
					return 0;
				}
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}
};

class Kruskal{
	private:
		static const int MAX_E = 50005;
		UnionFind unionFind;
	public:
		vector<Edge> edge;
		vector<int> mst; //edge[ mst[i] ] := 最小全域木を構築するi番目の辺
		int solve(int v, int e, vector<bool> use){
			sort(all(edge));
			unionFind.init(v);

			int res = 0;
			rep(i,e){
				Edge c = edge[i];
				if(not unionFind.same(c.u, c.v) and use[c.u] and use[c.v]){
					unionFind.unite(c.u, c.v);
					res += c.cost;
					mst.emplace_back(i);
				}
			}
			rep(i,v){
				if(not unionFind.same(0,i)) return INF;
			}
			return res;
		}
};

int main(){
	int n, m;
	while(cin >> n >> m, n){
		vector<int> h(n);
		set<pair<int, int>> t;
		rep(i,n){
			cin >> h[i];
			t.emplace(make_pair(h[i], i));
		}

		Kruskal krus;
		rep(i,m){
			int a, b, c;
			cin >> a >> b >> c;
			a--; b--;
			krus.edge.emplace_back(Edge{a,b,c});
		}

		set<pair<int, int>>::iterator it = t.end();
		UnionFind uni;
		for(auto i = t.begin(); i != t.end(); i++){
			uni.init(n);
			for(auto e: krus.edge){
				if(h[e.u] >= i->first and h[e.v] >= i->first){
					uni.unite(e.u, e.v);
				}
			}
			if(connected(n, uni)){
				it = i;
			}else{
				break;
			}
		}

		if(it == t.end()){
			cout << 0 << endl;
			continue;
		}

		vector<bool> use(n,0);
		rep(i,n){
			if(h[i] >= it->first){
				use[i] = true;
			}
		}

		long long ans = krus.solve(n,m,use);
		for(; it != t.end(); it++){

		}
	}
}
