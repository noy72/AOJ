#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int MAX = 55;
char rm[MAX][MAX], lm[MAX][MAX];
int w, h;

struct Point{
    int x,y;
};
bool u[MAX][MAX][MAX][MAX];
bool ans;

const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

void bfs(Point a, Point b){
    queue<pair<Point,Point>> q;
    q.push(make_pair(a, b));

    auto f = [](Point p, char m[MAX][MAX]){
        if(p.y < 0 || p.y >= h || p.x < 0 || p.x >= w) return 1;
        if(m[p.y][p.x] == '#') return 1;
        return 0;
    };

    while(not q.empty()){
        Point rp = q.front().first;
        Point lp = q.front().second;
        //cout << lp.x << ' ' << lp.y << "  /  " << rp.x << ' ' << rp.y << endl;
        q.pop();

        if(rm[rp.y][rp.x] == '%' && lm[lp.y][lp.x] == '%'){
            ans = true;
            return;
        }
        if(rm[rp.y][rp.x] == '%' || lm[lp.y][lp.x] == '%') continue;
        rep(i,4){
            Point l,r;
            l = Point{lp.x + dx[i], lp.y + dy[i]};
            r = Point{rp.x - dx[i], rp.y + dy[i]};
            if(f(l, lm)) l = lp;
            if(f(r, rm)) r = rp;

            if(u[r.y][r.x][l.y][l.x]) continue;
            u[r.y][r.x][l.y][l.x] = true;
            q.push(make_pair(r,l));
        }
    }
}

int main(){
    while(cin >> w >> h, w){
        ans = false;
        Point rp, lp;
        memset(u, 0, sizeof(u));
        rep(i,h) cin >> lm[i] >> rm[i];

        rep(i,h){
            rep(j,w){
                if(lm[i][j] == 'L') lp = Point{j,i};
                if(rm[i][j] == 'R') rp = Point{j,i};
            }
        }
        bfs(rp,lp);
        cout << (ans ? "Yes" : "No") << endl;
    }
}
