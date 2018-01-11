#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const double INF = 1e8;

class Edge{
    public:
        int to;
        double cost,limit;
        Edge(int to, double cost, double limit) : to(to) ,cost(cost) ,limit(limit) {}
};

class Node{
    public:
        double dis;
        bool isUsed;
        Node(){
            this->dis = INF;
            this->isUsed = 0;
        }
};

typedef vector<vector<Edge>> AdjList;

double dijkstra(AdjList g, int n,int s, int t){
    vector<vector<vector<Node>>> node(35,vector<vector<Node>>(35,vector<Node>(35)));
    //時間、速さ、頂点、前回の頂点
    typedef pair<pair<double,double>,pair<int,int>> p;

    priority_queue<p, vector<p>, greater<p>> q;

    q.push(make_pair(make_pair(0.0, 0.0), make_pair(s,34)));
    node[s][0][34].dis = 0.0;

    p u;
    while(not q.empty()){
        u = q.top(); q.pop();
        int current = u.second.first;
        int prev = u.second.second;
        double speed = u.first.second;
        node[current][speed][prev].isUsed = 1;

        rep(i,g[current].size()){
            int next = g[current][i].to;
            //if(node[next][speed][current].isUsed) continue;
            if(next == prev) continue;

            for(double j = -1; j <= 1; j++){
                int ns = speed + j;
                if(ns > 0){
                    if(ns > g[current][i].limit) continue;
                    if(node[next][ns][current].dis > node[current][static_cast<int>(speed)][prev].dis + g[current][i].cost / static_cast<double>(ns)){
                        node[next][ns][current].dis = node[current][static_cast<int>(speed)][prev].dis + g[current][i].cost / static_cast<double>(ns);
                        q.push(make_pair(
                                    make_pair(node[next][ns][current].dis, ns),
                                    make_pair(next,current)
                                    )
                              );
                    }
                }
            }
        }
    }
///    cout << endl;
///    rep(i,n){
///        rep(j,30){
///            cout << node[i][j].dis << ' ';
///        }
///        cout << endl;
///    show("------------")
///    }
    double mini = INF;
    rep(i,n){
        mini = min(mini, node[t][1][i].dis);
    }
    return mini;
}

int main(){
    int n, m;
    while(cin >> n >> m, n||m){
        int s, t;
        cin >> s >> t;
        s--; t--;
        AdjList g(n);
        rep(i,m){
            int a, b;
            double c, d;
            cin >> a >> b >> c >> d;
            a--; b--;
            g[a].emplace_back(Edge{b,c,d});
            g[b].emplace_back(Edge{a,c,d});
        }
        double tmp = dijkstra(g,n,s,t);
        if(tmp == INF) cout << "unreachable" << endl;
        else cout <<fixed << setprecision(12) <<  tmp << endl;
    }
}
