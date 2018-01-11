#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

#define int long long
const int INF = 1e8;
typedef pair<int, int> P;

int n, m;
vector<int> a(n), b(n);

map<pair<P,vector<P>>, P> ma;

P refresh(vector<P> st){
	int res = 0;
	for(int i = st.size() - 1; i >= 0; i--){
		if(st[i].second == 0){
			if(st[i].first == -1) break;
			continue;
		}
		if(st[i].first == -1) continue;
		res += st[i].first;
	}

	int a = res;
	res = 0;
	for(int i = st.size() - 1; i >= 0; i--){
		if(st[i].second == 1){
			if(st[i].first == -1) break;
			continue;
		}
		if(st[i].first == -1) continue;
		res += st[i].first;
	}
	return make_pair(a,res);
}

P add(P a, P b){
	return make_pair(a.first + b.first, a.second + b.second);
}

/*
P min(P a, P b){
	if(a.first < b.first){
		return a;
	}else if(a.first > b.first){
		return b;
	}else{
		if(a.second < b.second) return b;
		return a;
	}
}
P max(P a, P b){
	if(a.first > b.first){
		return a;
	}else if(a.first < b.first){
		return b;
	}else{
		if(a.second > b.second) return b;
		return a;
	}
}
*/

P dfs(int i, int j, bool turn, vector<pair<int, int>> st){
	//if(ma.count(make_pair(P(i,j), st))) return ma[make_pair(P(i,j), st)];
	//for(auto i : st){ cout << i.first << ' '; } cout << endl;

	P res;
	if(turn){
		res = make_pair(INF,INF);
		if(not st.empty()){
			res = min(res, add(dfs(i, j, turn ^ 1, vector<P>()), refresh(st)));
		}
		st.emplace_back(b[j], 0);
		if(j < m){
			res = min(res, dfs(i, j + 1, turn ^ 1, st));
		}
		if(res == make_pair(INF,INF)) res = make_pair(0,0);
	}else{
		res = make_pair(0,0);
		if(not st.empty()){
			res = max(res, add(dfs(i, j, turn ^ 1, vector<P>()), refresh(st)));
		}
		st.emplace_back(a[i], 1);
		if(i < n){
			res = max(res, dfs(i + 1, j, turn ^ 1, st));
		}
		if(res == make_pair(0LL,0LL)) res = make_pair(INF,INF);
	}

	//cout << i << ' ' << j << ' ' << res << endl;
	//cout <<turn << ' ' <<res <<  endl;
	return ma[make_pair(P(i,j), st)] = res;
}

signed main(){
	cin >> n >> m;

	a = vector<int>(n);
	b = vector<int>(m);
	rep(i,n) cin >> a[i];
	rep(i,m) cin >> b[i];

	vector<P> tmp;
	tmp.emplace_back(0,1);

	P ans = dfs(0,0,0,tmp);
	show(ans.first)
	show(ans.second)
	cout << ans.first - ans.second << endl;
}
