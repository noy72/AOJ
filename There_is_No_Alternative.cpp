#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
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
		int solve(int v, int e, int d = -1){
			if(d == -1) sort(all(edge));
			if(d == -1){
				//for(auto i : edge){ cout << i.u << ' ' << i.v << ' ' << i.cost << endl; }
			}
			unionFind.init(v);
			int res = 0;
			rep(i,e){
				if(d == i) continue;
				Edge c = edge[i];
				if(not unionFind.same(c.u, c.v)){
					unionFind.unite(c.u, c.v);
					//cout << i << ' ';
					res += c.cost;
					if(d == -1) mst.emplace_back(i);
				}
			}
				//cout << endl;
			rep(i,v){
				if(not unionFind.same(0,i)) return INF;
			}
			return res;
		}
};


int main(){
	int n, m;
	scanf("%d%d", &n, &m);

	Kruskal krus;
	rep(i,m){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a--; b--;
		krus.edge.emplace_back(Edge{a,b,c});
	}

	int mini = krus.solve(n,m);

	int cnt = 0, cost = 0;
	rep(i,n - 1){
		if(mini < krus.solve(n,m, krus.mst[i])){
			cnt++;
			cost += krus.edge[ krus.mst[i] ].cost;
		}
	}
	printf("%d %d\n", cnt, cost);
}
