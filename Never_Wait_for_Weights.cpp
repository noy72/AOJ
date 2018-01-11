#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int INF = 1e8;


static const int MAX_N = 100005;
static const int MAX_M = 100005;

class Union{
	public:
		int par[MAX_N]; //親
		int depth[MAX_N];//木の深さ
		int w[MAX_N];

		void init(int n){
			rep(i,n){
				par[i] = i;
				depth[i] = 0;
				w[i] = 0;
			}
		}

		pair<int, int> find(int x){
			if(par[x] == x){
				return x;
			}else {
				pair<int, int> tmp = make_pair(find(par[x]));
				par[x] = tmp.first;
				w[x] += tmp.second;
				return return 
			}
		}

		void unite(int x, int y, int c){
			int tmp = w[x];
			w[find(x)] = w[find(y)] - w[x] - c + w[y];
			x = find(x);
			y = find(y);
			if(x == y) return;

			if(depth[x] < depth[y]){
				par[x] = y;
			}else{
				par[y] = x;
				if(depth[x] == depth[y]) depth[x]++;
			}
		}

		int weight(int x){
			return w[find(x)] + w[x];
		}

		bool same(int x, int y){
			return find(x) == find(y);
		}
};

class Edge{
	public:
		int to, cost;
		Edge(int to, int cost) : to(to) ,cost(cost) {}
};

class Node{
	public:
		int dis;
		bool isUsed;
		int label;
		Node(){
			this->dis = INF;
			this->isUsed = 0;
		}
};

typedef vector<vector<Edge>> AdjList;

void bfs(AdjList& g, int cur, vector<Node>& node){
	queue<int> q;
	q.push(cur);
	node[cur].isUsed = true;
	node[cur].dis = 0;

	while(not q.empty()){
		int u = q.front(); q.pop();
		for(auto e : g[u]){
			if(node[e.to].isUsed) continue;
			node[e.to].isUsed = true;
			node[e.to].dis = node[u].dis + e.cost;
			q.push(e.to);
		}
	}
}

signed main(){
	int n, q;
	while(cin >> n >> q,n||q){
		int a[MAX_M], b[MAX_M], c[MAX_M];
		char com[MAX_M];

		Union uni;
		uni.init(n);
		rep(i,q){
			cin >> com[i];
			if(com[i] == '!'){
				cin >> a[i] >> b[i] >> c[i];
				a[i]--; b[i]--;
				uni.unite(a[i], b[i], c[i]);
				rep(i,n){ cout << uni.weight(i) << ' '; } cout << endl;
			}else{
				cin >> a[i] >> b[i];
				a[i]--; b[i]--;
				if(uni.same(a[i], b[i])){
					cout << uni.weight(b[i]) - uni.weight(a[i]) << endl;
				}else{
					cout << "UNKNOWN" << endl;
				}
			}
		}

	}
}
