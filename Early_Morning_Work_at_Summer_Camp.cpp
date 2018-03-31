#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

class StronglyConnectedComponents{
	private:
		vector<bool> used;
		vector<int> vs; //帰りがけ順の並び
		void dfs(int v){
			used[v] = true;
			rep(i,g[v].size()){
				if(not used[g[v][i]]) dfs(g[v][i]);
			}
			vs.emplace_back(v);
		}
		void rdfs(int v, int k){
			used[v] = true;
			cmp[v] = k;
			rep(i,rg[v].size()){
				if(not used[rg[v][i]]) rdfs(rg[v][i], k);
			}
		}
	public:
		typedef vector<vector<int>> graph;
		const int v; // 頂点数
		int nv; // SCCした後の頂点数
		graph g, rg; // グラフ、辺が逆になったグラフ
		vector<int> cmp; //属する強連結成分のトポロジカル順序

		StronglyConnectedComponents(int v) : used(v), v(v), g(v), rg(v), cmp(v) { }

		void addEdge(int from, int to){
			g[from].emplace_back(to);
			rg[to].emplace_back(from);
		}
		int solve(){ // 強連結成分分解をしたあとのグラフの頂点数を返す
			fill(all(used),0);
			vs.clear();
			rep(i,v){
				if(not used[i]) dfs(i);
			}
			fill(all(used),0);
			int k = 0;
			for(int i = vs.size() - 1; i >= 0; i--){
				if(not used[vs[i]]) rdfs(vs[i], k++);
			}
			return nv = k;
		}
		graph getCssGraph(vector<vector<int>>& node){
			node = vector<vector<int>>(nv); // node[i]:=SCCによって頂点iに同一視された頂点
			graph res(nv); // CSSしたあとのグラフ
			rep(i,v){
				node[cmp[i]].emplace_back(i);
				for(auto to : g[i]){
					if(cmp[i] == cmp[to]) continue;
					res[cmp[i]].emplace_back(cmp[to]);
				}
			}
			return res;
		}
		void out(){
			rep(i,v){ cout << cmp[i] << ' '; } cout << endl;
		}
};

void dfs(int pos, vector<bool>& used, vector<vector<int>>& g){
	used[pos] = true;
	for(auto to : g[pos]){
		if(used[to]) continue;
		dfs(to, used, g);
	}
}

int main(){
	int n;
	while(cin >> n,n){
		StronglyConnectedComponents scc(n);
		vector<double> p(n); // 寝坊する確率
		rep(i,n){
			int m;
			cin >> p[i] >> m;
			rep(j,m){
				int a;
				cin >> a;
				scc.addEdge(i, a - 1);
			}
		}
		scc.solve();

		vector<vector<int>> node;
		StronglyConnectedComponents::graph g = scc.getCssGraph(node);
		double ans = 1;

		vector<bool> used(scc.nv,0);
		rep(i,scc.nv){
			if(used[i]) continue;

			double tmp = 1.00;
			rep(j,node[i].size()){
				tmp *= p[node[i][j]];
			}
			ans *= 1.00 - tmp;
			dfs(i, used, g);
		}
		cout << fixed << setprecision(9) << ans << endl;
	}
}
