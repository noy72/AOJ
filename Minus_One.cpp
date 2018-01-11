#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int INF = 1e8;


class Edge{
    public:
        int to, cost;
        Edge(int to, int cost) : to(to) ,cost(cost) {}
};

class Node{
    public:
        int dis;
        bool isUsed;
        Node(){
            this->dis = INF;
            this->isUsed = 0;
        }
};

typedef vector<vector<Edge>> AdjList;

void dijkstra(AdjList const g, int start, int n, int f, int t,vector<Node> node[2]){
    priority_queue<int, vector<pair<int, int>>, greater<pair<int, int>>> q;

    q.push(make_pair(0, start));
    node[f][start].dis = 0;

    pair<int, int> u;
    while(not q.empty()){
        u = q.top(); q.pop();
        int current = u.second;
        node[f][current].isUsed = 1;

        rep(i,g[current].size()){
            int next = g[current][i].to;
            if(node[f][next].isUsed == 0){
                if(node[f][next].dis > node[f][current].dis + g[current][i].cost){
                    node[f][next].dis = node[f][current].dis + g[current][i].cost;
                    q.push(make_pair(node[f][next].dis, next));
                }
            }
        }
    }
}

int main(){
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--;

    AdjList g(n);
    rep(i,m){
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].emplace_back(Edge{b,1});
        g[b].emplace_back(Edge{a,1});
    }
    vector<Node> node[2];
    node[0] = vector<Node>(n);
    node[1] = vector<Node>(n);
    dijkstra(g,s,n,0,t,node);
    dijkstra(g,t,n,1,t,node);

    long long cnt[2][100005] = {{0}};
    rep(i,n){
        if(node[0][i].dis != INF) cnt[0][node[0][i].dis]++;
        if(node[1][i].dis != INF) cnt[1][node[1][i].dis]++;
    }
    int dist = node[0][t].dis;

    long long ans = 0;
    rep(i,dist - 1) ans+=cnt[0][i] * cnt[1][dist - i - 2];

    cout << ans << endl;
}
