#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

const int MAX_V = 10000;

vector<int> g[MAX_V]; //グラフ
vector<int> tp; //トポロジカルソートの結果

void bfs(int s, int indeg[MAX_V], bool used[MAX_V]){
	queue<int> q;

	q.push(s);
	used[s] = true;

	while(not q.empty()){
		int u = q.front(); q.pop();
		tp.emplace_back(u);
		rep(i,g[u].size()){
			int v = g[u][i];
			indeg[v]--;
			if(indeg[v] == 0 && not used[v]){
				used[v] = true;
				q.push(v);
			}
		}
	}
}

//グラフに閉路がある場合、0を返す
bool topologicalSort(int v){
	int indeg[MAX_V]; //入次数
	bool used[MAX_V];
	memset(indeg, 0, sizeof(indeg));
	memset(used, 0, sizeof(used));

	rep(i,v) rep(j,g[i].size()) indeg[ g[i][j] ]++;
	rep(i,v) if(indeg[i] == 0 && not used[i]) bfs(i, indeg, used);

	for(auto it:tp) cout << it + 1 << endl;

	if(tp.size() == v) return true;
	else return false;
}

int main(){
	int m, n;
	cin >> m >> n;

	rep(i,m){
		if(i == 1) continue;
		g[i].emplace_back(1);
	}
	rep(i,n){
		int a, b;
		cin >> a >> b;
		a--; b--;
		g[a].emplace_back(b);
	}

	topologicalSort(m);
	vector<int> ans(m);
	rep(i,m) ans[tp[i]] = i + 1;
	//rep(i,m){ cout << ans[i] << endl; }
}
