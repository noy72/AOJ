#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int v;
string m[1005];
int edge[1005];

void dfs(int cur, vector<bool>& used, vector<int>& s){
	used[cur] = true;
	rep(i,v){
		if(m[cur][i] == 'Y' && not used[i]){
			s.emplace_back(i);
			dfs(i, used, s);
		}
	}
}

int main(){
	cin >> v;

	rep(i,v){
		cin >> m[i];
	}

	rep(i,v){
		rep(j,v){
			if(m[i][j] == 'Y'){
				edge[i]++;
			}
		}
	}

	rep(i,v) show(edge[i])

	vector<bool> used(v,0);
	int odd = 0;
	int edges = 0;
	rep(i,v){
		if(used[i]) continue;
		vector<int> s;
		s.emplace_back(i);
		dfs(i, used, s);
		if(s.size() % 2 == 1) odd++;

		int use_edges = 0;
		for(auto j : s){
			use_edges += edge[j];
		}
		show(s.size())
		use_edges /= 2;
		show(use_edges)

		int size = static_cast<int>(s.size());
		edges += (size - 1) * size / 2 - use_edges;
	}
	show(edges)
		show(odd)

	if(edges % 2){
		if(odd == 3) cout << "Hanako" << endl;
		else cout << "Taro" << endl;
	}else{
		if(odd == 2 || odd == 3) cout << "Taro" << endl;
		else cout << "Hanako" << endl;
	}
}
