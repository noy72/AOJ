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

map<pair<int, int>, vector<int>> memo;
vector<int> bfs(int n, vector<vector<int>>& g, int pos, int k){
	if(memo.count(make_pair(pos, k))) return memo[make_pair(pos, k)];
	queue<pair<int, int>> q;
	q.emplace(pos, k);

	vector<vector<bool>> used(n, vector<bool>(101, 0));

	vector<int> res;
	while(not q.empty()){
		int cur, t;
		tie(cur, t) = q.front(); q.pop();
		used[cur][t] = true;
		if(t == 0){
			res.emplace_back(cur);
			continue;
		}

		for(auto to : g[cur]){
			if(not used[to][t - 1]){
				q.emplace(to, t - 1);
			}
		}
	}
	return memo[make_pair(pos, k)] = res;
}

inline bool isGoal(vector<vector<bool>>& cnt, int pos){
	rep(i,3){
		if(not cnt[pos][i]) return false;
	}
	return true;
}

int main(){
	int n, m, a[3];
	cin >> n >> m >> a[0] >> a[1] >> a[2];

	vector<vector<int>> g(n);
	rep(i,m){
		int s, t;
		cin >> s >> t;
		s--; t--;
		g[s].emplace_back(t);
	}

	vector<int> dis(n, 1e9);
	dis[n - 1] = 0;

	rep(_,n){
		rep(v,n - 1){
			int maxi = 0;
			rep(i,3){
				int mini = 1e9;
				for(auto j : bfs(n, g, v, a[i])){
					mini = min(mini, dis[j] + 1);
				}
				maxi = max(maxi, mini);
			}
			dis[v] = maxi;
		}
	}

	if(dis[0] != 1e9) cout << dis[0] << endl;
	else cout << "IMPOSSIBLE" << endl;
}
