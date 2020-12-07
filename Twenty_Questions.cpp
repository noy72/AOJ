#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int INF = 1e8;
map<vector<bool>, int> memo;

set<int> res;

void dfs(int idx, int& use, vector<vector<bool>>& b, vector<bool> c){

	if(idx  == b.size()){
		int cnt = 0, p;
		rep(i,c.size()){
			if(c[i]){
				cnt++;
				p = i;
			}
		}
		if(cnt == 1){
			res.emplace(p);
		}
		return;
	}

	//if(not any_of(all(c), [](bool b){ return b; })) return;

	if(not (use >> idx & 1)){
		dfs(idx + 1, use, b, c);
		return;
	}

	vector<bool> tmp = c;
	rep(i,tmp.size()){
		tmp[i] = tmp[i] and b[idx][i];
	}
	dfs(idx + 1, use, b, tmp);

	tmp = c;
	rep(i,tmp.size()){
		tmp[i] = tmp[i] and not b[idx][i];
	}
	dfs(idx + 1, use ,b, tmp);
}

int main(){
	int m, n;
	while(cin >> m >> n, n){
		vector<string> s(n);
		rep(i,n){
			cin >> s[i];
		}

		//rep(i,m + m){
		//	rep(j,n){
		//		cout << b[i][j];
		//	}
		//	cout << endl;
		//}

		int ans = 1e9;
		dfs(0, s, b, vector<bool>(n, 1));
		cout << ans << endl;
	}
}
