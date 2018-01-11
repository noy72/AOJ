#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

#define int long long
const int M = 1000000007;

class Scc{
	private:
		static const int MAX_V = 10000;
		vector<int> g[MAX_V];	//グラフ
		vector<int> rg[MAX_V];	//辺が逆になったグラフ
		vector<int> vs;			//帰りがけ順の並び
		vector<pair<int, int>> edge;
		bool used[MAX_V];

		void rdfs(int v, int k){
			used[v] = true;
			cmp[v] = k;
			rep(i,rg[v].size()){
				if(not used[rg[v][i]]) rdfs(rg[v][i], k);
			}
		}
		void dfs(int v){
			used[v] = true;
			rep(i,g[v].size()){
				if(not used[g[v][i]]) dfs(g[v][i]);
			}
			vs.emplace_back(v);
		}
		void buildGraph(){
			for(auto i : edge){
				if(cmp[i.first] == cmp[i.second]) continue;
				dag[ cmp[i.first] ].emplace_back(cmp[i.second]);
			}
		}
	public:
		vector<int> dag[MAX_V]; //強連結成分分解を行った後のDAGグラフ
		int cmp[MAX_V]; //属する強連結成分のトポロジカル順序

		void addEdge(int from, int to){
			edge.emplace_back(from,to);
			g[from].emplace_back(to);
			rg[to].emplace_back(from);
		}
		int solve(int v){ //scc後の頂点数を返す
			memset(used, 0, sizeof(used));
			vs.clear();
			rep(i,v){
				if(not used[i]) dfs(i);
			}
			memset(used, 0, sizeof(used));
			int k = 0;
			for(int i = vs.size() - 1; i >= 0; i--){
				if(not used[vs[i]]) rdfs(vs[i], k++);
			}
			buildGraph();
			return k;
		}
};

pair<int, int> dfs(int cur, vector<bool>& used, Scc& scc){
	used[cur] = true;
	pair<int, int> res = make_pair(1,1);
	for(auto to : scc.dag[cur]){
		if(used[to]) continue;
		pair<int, int> tmp = dfs(to, used, scc);
		res.first *= tmp.first + tmp.second;
		res.first %= M;
	}
	return res;
}

signed main(){
	int n, m;
	while(cin >> n >> m){
		Scc scc;
		rep(i,m){
			int a, b;
			cin >> a >> b;
			a--; b--;
			scc.addEdge(b,a);
		}

		int k = scc.solve(n);

		int ans = 1;
		vector<bool> used(n,0);
		rep(i,k){
			if(used[i]) continue;
			pair<int, int> tmp = dfs(i, used, scc);
			//show(tmp.first + tmp.second)
			ans *= tmp.first + tmp.second;
			ans %= M;
		}
		cout << ans << endl;
	}
}
