#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

struct Point{
    double x, y, z;
    double r;
};


double dist(Point a, Point b){
    auto pow = [](double a){return a * a; };
    return sqrt(pow(b.x - a.x) + pow(b.y - a.y) + pow(b.z - a.z)) - (a.r + b.r);
}

class Edge {
    public:
        int to;
        double cost;
        Edge(int to, double cost) : to(to), cost(cost) { }
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

double prim(const Graph &g, int s = 0) {
    int n = g.size();
    double total = 0;

    vector<bool> visited(n);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
    //priority_queue<pair<double, int> > q;

    q.push(make_pair(0.0,s));
    while (not q.empty()) {
        pair<double, int> u = q.top(); q.pop();
        if (visited[u.second]) continue;
        total += u.first;
        visited[u.second] = true;
        for(auto it : g[u.second]) {
            if (not visited[it.to]) q.push(make_pair(it.cost, it.to));
        }
    }
    return total;
}

int main(){
    int n;
    while(cin >> n,n){
        Point p[105];
        rep(i,n) cin >> p[i].x >> p[i].y >> p[i].z >> p[i].r;

        Graph g(n);
        rep(i,n){
            rep(j,n){
                double tmp = dist(p[i], p[j]);
//                cout << i << ' ' << j << endl;
//                show(tmp)
                g[i].emplace_back(Edge{j,tmp < 0 ? 0 : tmp});
            }
        }
        cout <<fixed << setprecision(3) <<  prim(g,0) << endl;
    }
}
