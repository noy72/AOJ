#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
using namespace std;

const int INF = 200000;
const int MAX_V = 505;

class Node{
    public:
        bool isUsed;
        int prenum; //DFSの訪問の順番
        int parent; //DFS Treeにおける親
        int lowest; //min(自分のprenum, 逆辺がある場合の親のprenum, すべての子のlowest)
        Node(){ this->isUsed = 0; }
};

vector<int> edge[MAX_V];
int blink;

void dfs(int current, int prev, int &cnt, vector<Node> &node){
    node[current].prenum = node[current].lowest = cnt;
    cnt++;

    node[current].isUsed = true;

    int next;
    rep(i,edge[current].size()){
        next = edge[current][i];
        if(next == blink) continue;
        if(not node[next].isUsed){
            node[next].parent = current;
            dfs(next, current, cnt, node);
            node[current].lowest = min(node[current].lowest, node[next].lowest);
            //if(node[current].prenum < node[next].lowest){
            //    bridge.emplace_back(make_pair(min(current, next), max(current, next)));
            //}
        }else if(next != prev){
            node[current].lowest = min(node[current].lowest, node[next].prenum);
        }
    }
}

int art_points(int v,int &cnt, vector<Node> &node){
    if(blink == 0){
        blink = 1;
        swap(edge[0], edge[1]);
    }
    dfs(0, -1,cnt,node);

    set<int> ap;
    int np = 0;
    range(i,1,v){
        if(i == blink) continue;
        if(blink == 0 && i == 1) continue;
        int p = node[i].parent;
        //show(i) show(ap.size()) show(p)
        if(p == 0) np++;
        else if(node[p].prenum <= node[i].lowest) ap.insert(p);
    }
    if(np > 1) ap.insert(0);
    //for(auto it:ap){ cout << it << endl; } //関節点の全列挙
    return ap.size();
    //sort(all(bridge));
    //for(auto it:bridge){ cout << it.first << ' ' << it.second << endl; } //橋の全列挙

}

bool check(int n){
    for(int i = n - 1; i >= 0; i--){
        int cnt = 1;
        vector<Node> node(MAX_V);
        blink = i; //i番目のノードを削除(使えないように)する
        if(art_points(n,cnt,node) != 0) return false; //関節点があったら、パスは3本以上ない
    }
    return true;
}

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m),n||m){
        rep(i,n) edge[i] = vector<int>(MAX_V);
        rep(i,m){
            int a,b;
            scanf("%d%d",&a,&b);
            edge[a].push_back(b);
            edge[b].push_back(a);
        }
        puts(check(n) ? "YES" : "NO");
    }
}
