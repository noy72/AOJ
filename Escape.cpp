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

void dfs(vector<vector<int>>& g, vector<int>& in, vector<bool>& used, int pos, vector<bool>& p){
	used[pos] = true;
	for(auto to : g[pos]){
		if(used[to]) continue;
		dfs(g, in, used, to, p);
	}
	if(in[pos] == 1 and pos != 0){
		for(auto i : g[pos]){
			in[i]--;
		}
		p[pos] = true;
	}
}

int bfs(vector<vector<int>>& g, vector<bool>& used, vector<int>& w){
	int n = g.size();

	queue<int> q;
	rep(i,n){
		if(not used[i]) q.emplace(i);
	}

	vector<int> dis(n,0);
	while(not q.empty()){
		int pos = q.front(); q.pop();
		for(auto to : g[pos]){
			if(not used[to]) continue;
			used[to] = false;
			dis[to] = dis[pos] + w[to];
			q.emplace(to);
		}
	}

	return *max_element(all(dis));
}

int main(){
	int n, m;
	cin >> n >> m;

	vector<int> w(n);
	cin >> w;

	vector<vector<int>> g(n);
	rep(i,m){
		int a, b;
		cin >> a >> b;
		a--; b--;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}

	vector<int> in(n);
	rep(i,n) in[i] = g[i].size();

	vector<bool> p(n,0);
	vector<bool> used(n,0);
	dfs(g, in, used, 0, p);

	int res = 0;
	rep(i,n){
		if(not p[i]) res += w[i];
	}

	cout << bfs(g, p, w) + res << endl;
}
