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

int p, t, r;

vector<vector<int>> makeGraph(vector<vector<int>>& g, vector<int>& remain, vector<vector<int>>& need){
	rep(i,p){
		rep(j,r){
			if(need[i][j] <= remain[j]) break;
			rep(
		}
	}
}

void addEdge(vector<vector<int>>& g, int a, int b){
	g[a].emplace_back(b);
}

int main(){
	cin >> p >> r >> t;

	vector<int> remain(r);
	cin >> remain;

	vector<vector<int>> need(p, vector<int>(r));
	rep(i,p){
		cin >> need[i];
	}

	vector<vector<int>> g(p), rev(p);
	vector<priority_queue<int>> q(r);
	vector<vector<int>> have(all(need));
	rep(i,t){
		int P, R;
		cin >> P >> R;
		p--; R--;
	}
}
