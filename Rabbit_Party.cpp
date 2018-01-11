#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

#define int long long

int n, m;
int g[105][105];
int ans;
set<vector<bool>> memo;

void dfs(vector<bool> used){
	if(not (memo.emplace(used)).second) return;
	//for(auto i : used){ cout << i << ' ' ; } cout << endl;

	vector<int> to;
	rep(i,n){
		if(used[i]) continue;
		bool f = true;
		rep(j,n){
			if(not used[j]) continue;
			if(i == j || g[j][i] == 0){
				f = false;
				break;
			}
		}
		if(f) to.emplace_back(i);
	}

	for(auto i : to){
		used[i] = true;
		dfs(used);
		used[i] = false;
	}

	int sum = 0;
	rep(i,n){
		if(not used[i]) continue;
		int mini = INF;
		rep(j,n){
			if(not used[j]) continue;
			if(g[i][j] == 0) continue;
			mini = min(mini, g[i][j]);
		}
		if(mini == INF) continue;
		sum += mini;
	}
	ans = max(ans, sum);
}

signed main(){
	cin >> n >> m;

	vector<int> v;
	rep(i,m){
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		g[a][b] = g[b][a] = c;
	}

	rep(i,n){
		vector<bool> tmp(n,0);
		tmp[i] = true;
		dfs(tmp);
	}
	cout << ans << endl;

	//for(auto i : memo){ for(auto j : i){ cout << j << ' '; } cout << endl; }
}
