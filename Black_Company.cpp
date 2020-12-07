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

class UnionFind{
	private:
	public:
		vector<int> par, depth;
		vector<int> cnt; // その集合の頂点数
		UnionFind() {}
		UnionFind(int n){
			init(n);
		}
		void init(int n){
			par = vector<int>(n);
			depth = vector<int>(n, 0);
			cnt = vector<int>(n, 1);
			rep(i,n){
				par[i] = i;
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
				cnt[y] += cnt[x];
			}else{
				par[y] = x;
				cnt[x] += cnt[y];
				if(depth[x] == depth[y]) depth[x]++;
			}
		}
		bool same(int x, int y){
			return find(x) == find(y);
		}
};

int main(){
	int n;
	cin >> n;

	vector<int> c(n);
	cin >> c;

	int m;
	cin >> m;

	vector<vector<int>> nv(n);
	vector<pair<int, int>> e(m);
	rep(i,m){
		int a, b;
		cin >> a >> b;
		a--; b--;
		e[i] = make_pair(a,b);
		nv[a].emplace_back(b);
		nv[b].emplace_back(a);
	}

	UnionFind uni(n);
	vector<vector<int>> g(n);

	vector<vector<pair<int, int>>> p(n);
	rep(i,n){
		if(nv[i].empty()) continue;
		p[i] = vector<pair<int, int>>(nv[i].size());
		rep(j,nv[i].size()){
			p[i][j] = make_pair(c[ nv[i][j] ], nv[i][j]);
		}

		sort(all(p[i]));

		rep(j,p[i].size() - 1){
			if(p[i][j].first == p[i][j + 1].first) uni.unite(p[i][j].second, p[i][j + 1].second);
		}
	}

	rep(i,n){
		if(p[i].empty()) continue;
		rep(j,p[i].size() - 1){
			int a = uni.find(p[i][j].second);
			int b = uni.find(p[i][j + 1].second);
			if(a == b) continue;
			g[a].emplace_back(b);
		}
	}

	rep(i,m){
		if(c[ e[i].first ] > c[ e[i].second ]) swap(e[i].first, e[i].second);
		g[ uni.find(e[i].first) ].emplace_back( uni.find(e[i].second) );
	}

	vector<pair<int, int>> P(n);
	rep(i,n){
		P[i] = make_pair(c[i], i);
	}
	sort(all(p));

	vector<long long> cost(n,0);
	vector<bool> used(n, 0);
	rep(i,n){
		int pos = P[i].second;
		//if(used[uni.find(pos)]) continue;
		//used[uni.find(pos)] = true;

		if(cost[pos] == 0) cost[pos]++;
		for(auto to : g[pos]){
			//show(to)
			assert(c[pos] <= c[to]);
			if(c[pos] > c[to]) continue;
			cost[to] = max(cost[to], cost[pos] + (c[pos] < c[to] ? 1 : 0));
		}
	}
	//cout << cost << endl;

	long long ans = 0;
	rep(i,n){
		ans += cost[uni.find(i)];
	}

	cout << ans << endl;
	//
	//	map<int,vector<int>> s;
	//	rep(i,n){
	//		s[p[i].first].emplace_back(p[i].second);
	//	}
	//
	//	long long ans = 0;
	//	for(auto pr : s){
	//		long long maxi = 0;
	//		for(auto v : pr.second){
	//			maxi = max<long long>(maxi, cost[ v ]);
	//		}
	//		ans += maxi * pr.second.size();
	//	}
	//	cout << ans << endl;
}
