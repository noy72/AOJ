#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;


class Edge {
	public:
		int to, cost;
		Edge(int to, int cost) : to(to), cost(cost) { }
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

int prim(const Graph &g, int s = 0) {
	int n = g.size();
	int total = 0;

	vector<bool> visited(n);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	//priority_queue<pair<int, int> > q;

	q.push(make_pair(0,s));

	vector<int> res;
	while (not q.empty()) {
		pair<int, int> u = q.top(); q.pop();
		if (visited[u.second]) continue;
		total += u.first;
		res.emplace_back(u.first);
		visited[u.second] = true;
		for(auto it : g[u.second]) {
			if (not visited[it.to]) q.push(make_pair(it.cost, it.to));
		}
	}
	sort(all(res));
	//for(auto i : res){ show(i) }
	return res[res.size() / 2];
}

int main(){
	int n, m;
	while(cin >> n >> m, n){
		Graph g(n);
		rep(i,m){
			int a, b, c;
			cin >> a >> b >> c;
			a--; b--;
			g[a].emplace_back(b,c);
			g[b].emplace_back(a,c);
		}
		cout << prim(g) << endl;
	}
}
