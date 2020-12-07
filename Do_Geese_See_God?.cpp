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

map<string,int> m;
int dfs(string s){
	if(m.count(s)) return m[s];
	if(s.size() == 1) return 1;

	string u, v;
	u = v = s;
	u.erase(u.begin());
	v.erase(--v.end());

	int res = dfs(u);
	if(u != v) res += dfs(v);

	return m[s] = res;
}

int main(){
	string s;
	int k;
	cin >> s >> k;

	show(dfs(s));
	for(auto p : m){
		cout << p.first << ' ' << p.second << endl;
	}
}
