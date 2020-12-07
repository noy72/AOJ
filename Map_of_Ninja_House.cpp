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

void addEdge(int a, int b, vector<vector<int>>& g, vector<int>& in){
	g[a].emplace_back(b);
	g[b].emplace_back(a);
	in[a]--; in[b]--;
	assert(in[a] >= 0 and in[b] >= 0 and "invalid edge");
}

void dfs(int& idx, int& num, vector<int>& d, vector<int>& in, vector<int>& par, vector<vector<int>>& g){
	int pos = num++;
	//cout << pos << endl;
	while(in[pos] > 0 and idx < d.size()){
		if(d[idx] >= 0){
			idx++; 
			addEdge(pos, num, g, in);
			par[num] = pos;
			dfs(idx, num, d, in, par, g);
		}else{
			int p = pos;
			rep(i,-d[idx]){
				p = par[p];
			}
			idx++;
			assert(p >= 0 and "invalid par");
			addEdge(p, pos, g, in);
		}
	}
}

int main(){
	int n;
	cin >> n;
	rep(_,n){
		int a;
		vector<int> d, in;
		while(cin >> a, a){
			if(a >= 0){
				in.emplace_back(a);
			}
			d.emplace_back(a);
		}

		vector<int> par(in.size(), - 1);
		vector<vector<int>> g(in.size());
		int idx = 1, num = 0; 
		dfs(idx, num, d, in, par, g);

		rep(i,in.size()){
			sort(all(g[i]));
		}

		rep(i,in.size()){
			cout << i + 1;
			rep(j,g[i].size()){
				cout << ' ' << g[i][j] + 1;
			}
			cout << endl;
		}
	}
}
