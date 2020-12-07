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

const int INF = 1e8;

struct Edge{
	int to;
	int cost;
	Edge(int to, int cost) : to(to), cost(cost) {}
};

struct Node{
	int dis;
	bool used;
	Node() : dis(INF), used(false) { }
	Node(int d, bool f) : dis(d), used(f) { }
};

typedef vector<vector<Edge>> graph;

vector<Node> dijkstra(graph g, int s, int n){
	vector<Node> node(n);
	priority_queue<int, vector<pair<int, int>>, greater<pair<int, int>>> q;

	q.push(make_pair(0, s));
	node[s] = Node{0, true};

	while(not q.empty()){
		int dis, pos;
		tie(dis, pos) = q.top(); q.pop();
		node[pos].used = true;

		for(auto e : g[pos]){
			if(node[e.to].used == true) continue;
			if(node[e.to].dis > dis + e.cost){
				node[e.to].dis = dis + e.cost;
				q.emplace(node[e.to].dis, e.to);
			}
		}
	}
	return node;
}


pair<int,int> e[3005];
int d[3005];
int t[305];

int input(int n, int m){
	map<string,int> id;

	string src, dist;
	cin >> src >> dist;
	id[src] = id.size();
	id[dist] = id.size();

	rep(i,n){
		string c1, c2;
		cin >> c1 >> c2 >> d[i];
		if(not id.count(c1)) id[c1] = id.size();
		if(not id.count(c2)) id[c2] = id.size();
		e[i] = make_pair(id[c1], id[c2]);
	}

	rep(i,m){
		string s;
		cin >> s;
		if(not id.count(s)) id[s] = id.size();
		t[i] = id[s];
	}

	t[m] = id[src];
	t[m + 1] = id[dist];
	return id.size();
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);

	int n, m, cap;
	while(cin >> n >> m >> cap, n||m||cap){
		cap *= 10;

		int v = input(n, m) + 5;

		graph g(v), ng(v);
		rep(i,n){
			int x = e[i].first, y = e[i].second;
			g[x].emplace_back(y, d[i]);
			g[y].emplace_back(x, d[i]);
		}

		rep(i,m + 2){
			int x = t[i];
			auto dis = dijkstra(g, x, v);
			rep(j,m + 2){
				int y = t[j];
				if(dis[y].dis > cap) continue;
				ng[x].emplace_back(y, dis[y].dis);
			}
		}

		//rep(i,v){
		//	rep(j,v){
		//		if(ng[i][j] == 1e8) cout << "_ ";
		//		else cout << ng[i][j] << ' ';
		//	}
		//	cout << endl;
		//}

		int ans = dijkstra(ng, t[m], v).at(t[m + 1]).dis;
		cout << (ans == 1e8 ? -1 : ans) << endl;
	}
}
