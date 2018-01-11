#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

#define int long long
const int M = 1000000007;

int r;
vector<int> g[100005];
map<int,int> m;

int dfs(int cur){

	int res = 0;
	for(auto to : g[cur]){
		res += dfs(to);
		res %= M;
	}
	res = res * r + 1;
	res %= M;
	m[res]++;
	return res;
}


signed main(){
	int n;
	cin >> n;
	rep(i,n - 1){
		int a, b;
		cin >> a >> b;
		a--; b--;
		g[a].emplace_back(b);
	}

	r = 8731873;
	dfs(0);

	int ans = 0;
	for(auto i : m){
		//show(i.second)
		ans += (i.second * (i.second - 1)) / 2;
	}
	cout << ans << endl;
}
