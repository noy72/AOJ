#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

struct Edge{
	int to;
	int cost;
	int time, com;
	Edge(int to, int cost, int time, int com) : to(to), cost(cost), time(time), com(com) {}
};

struct Node{
	int dis;
	bool used;
	Node() : dis(INF), used(false) { }
	Node(int d, bool f) : dis(d), used(f) { }
};


typedef vector<vector<Edge>> graph;
typedef tuple<int,int,int> T;

int dijkstra(graph g, int s, int t, int n, int k, int bit){
	vector<vector<Node>> node(n, vector<Node>(25));
	priority_queue<int, vector<T>, greater<T>> q;

	q.push(T(0, 0, s));
	node[s][0] = Node{0, true};

	while(not q.empty()){
		int dis, t, pos;
		tie(dis, t, pos) = q.top(); q.pop();
		node[pos][t].used = true;

		for(auto e : g[pos]){
			if((bit >> e.com) & 1){
                //cout <<"asdf  " <<  bit << " " << e.com <<endl;
				 e.cost = 0;
			}
            if(t + e.time > k) continue;
            int nt = t + e.time;
			if(node[e.to][nt].used == true) continue;
			if(node[e.to][nt].dis > dis + e.cost){
				node[e.to][nt].dis = dis + e.cost;
				q.emplace(node[e.to][nt].dis, nt, e.to);
			}
		}
	}

	//show("s");
	//for(auto i : node){ for(auto j : i){ cout << j.dis << ' '; } cout << endl; }

    int mini = INF;
    rep(i,k + 1) {
        mini = min(mini, node[t][i].dis);
    }
	return mini;
}

int main(){
	int n, m, h, k;
	while(cin >> n >> m >> h >> k,n) {

		graph g(n);
		rep(i, m) {
			int a, b, c, h, r;
			cin >> a >> b >> c >> h >> r;
			a--;
			b--;
            r--;
			g[a].emplace_back(Edge{b, c, h, r});
			g[b].emplace_back(Edge{a, c, h, r});
		}
		int s, t;
		cin >> s >> t;
		s--;
		t--;

		int p;
		cin >> p;
		vector<int> ticket(p), d(p);
		rep(i, p) {
			int l;
			cin >> l >> d[i];
			rep(j, l) {
				int k;
				cin >> k;
				k--;
				ticket[i] |= 1 << k;
			}
		}

		vector<int> dp(1 << k, INF);
		dp[0] = 0;
		rep(i, 1 << k) {
			if (dp[i] == INF) continue;
			rep(j, p) {
				dp[i bitor ticket[j]] = min(dp[i bitor ticket[j]], dp[i] + d[j]);
			}
		}

		int ans = INF;
		rep(i, 1 << k){
			if(dp[i] == INF) continue;
            //cout << i << " " << dp[i] << endl;
			ans = min(ans, dijkstra(g, s, t, n, h, i) + dp[i]);
		}

		cout << (ans == INF ? -1 : ans)  << endl;
	}
}

