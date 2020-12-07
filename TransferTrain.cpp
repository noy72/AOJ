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

const int INF = 1e9 + 5;

struct Edge{
	int to;
	int cost;
	int other;
	Edge(int to, int cost, int other) : to(to), cost(cost), other(other) {}
};

struct Node{
	int dis;
	bool used;
	Node() : dis(INF), used(false) { }
	Node(int d, bool f) : dis(d), used(f) { }
};

map<int, map<int, Node>> node;

typedef vector<vector<Edge>> graph;
typedef tuple<int,int,int> T;

pair<int, int> dijkstra(graph& g, int s, int t){
	node[s][0] = Node{0, true};

	priority_queue<T, vector<T>, greater<T>> q;
	q.emplace(0, 0, s);

	while(not q.empty()){
		int dis, trans, pos;
		tie(dis, trans, pos) = q.top(); q.pop();
		node[pos][trans].used = true;

		for(auto e : g[pos]){
			int nt = trans + e.other;
			int nd = dis + e.cost;

			if(node.count(e.to) and node[e.to].count(nt)) continue;
			if(node[e.to][nt].dis > nd){
				node[e.to][nt].dis = nd;
				q.emplace(nd, nt, e.to);
			}
		}
	}

	int minDis = 1e9, minTrans;
	for(auto p : node[t]){
		if(p.second.dis > minDis){
			minDis = p.second.dis;
			minTrans = p.first;
		}else if(p.first == minDis){
			minTrans = p.first;
		}
	}

	return make_pair(minDis, minTrans);
}

void addEdge(graph& g, int a, int b, int c, int d){
	g[a].emplace_back(b, c, d);
	g[b].emplace_back(a, c, d);
}

int main(){
	int n, t;
	string a, b;
	cin >> n >> t >> a >> b;

	vector<int> x(n);
	vector<vector<int>> ti(n);
	vector<vector<string>> s(n);
	rep(i,n){
		cin >> x[i];

		s[i] = vector<string>(x[i]);
		cin >> s[i];

		ti[i] = vector<int>(x[i] - 1);
		cin >> ti[i];
	}

	map<string, int> toId;
	rep(i,n){
		for(auto name : s[i]){
			if(not toId.count(name)) toId[name] = toId.size();
		}
	}

	int verSize = accumulate(all(x), 0);
	int p = 0;
	graph g(verSize + toId.size());
	rep(i,n){
		rep(j,x[i] - 1){
			addEdge(g, p + j, p + j + 1, ti[i][j], 0);
		}
		rep(j,x[i]){
			addEdge(g, p + j, verSize + toId[s[i][j]], 0, 1);
		}
		p += x[i];
	}

	//for(auto i : g){ for(auto j : i){ cout << j.to <<  ' '; } cout << endl; }

	pair<int, int> ans = dijkstra(g, toId[a] + verSize, toId[b] + verSize);

	if(ans.first == INF){
		cout << -1 << endl;
	}else{
		cout << ans.first << ' ' << ans.second << endl;
		ans.second = ans.second / 2 - 1;
		cout << ans.first + ans.second * t << ' ' << ans.second  << endl;
	}
}
