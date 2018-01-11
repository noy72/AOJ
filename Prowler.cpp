#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int MAX = 55;

struct P{
    int x, y;
};

P d[4][3] = {
    {P{1,0}, P{0,-1}, P{-1,0}},
    {P{0,1}, P{1,0}, P{0,-1}},
    {P{-1,0}, P{0,1}, P{1,0}},
    {P{0,-1}, P{-1,0}, P{0,1}}
};

int main(){
    int h, w;
    cin >> h >> w;

    char m[MAX][MAX];
    rep(i,h + 2) rep(j, w + 2) m[i][j] = '#';
    int dir = -1;
    P s = {-1,-1};

    range(i,1,h + 1){
        range(j,1,w + 1){
            cin >> m[i][j];
            if(m[i][j] == '^') dir = 0;
            else if(m[i][j] == '>') dir = 1;
            else if(m[i][j] == 'v') dir = 2;
            else if(m[i][j] == '<') dir = 3;
            if(dir != -1 && s.x == -1) s = P{j,i};
        }
    }
    m[s.y][s.x] = '.';

    int cnt = -1;
    cout << s.y << ' ' << s.x << endl;
    while(m[s.y][s.x] != 'G'){
        show("JI")
        cnt++;
        show(dir)
        cout << s.y << ' ' << s.x << endl;
        int g;
        cin >> g;
        rep(i,3){
            int ny = s.y + d[dir][i].y;
            int nx = s.x + d[dir][i].x;
            show(m[ny][nx])
            if(ny < 1 || ny > h || nx < 1 || nx > w) continue;
            if(m[ny][nx] != '#'){
                cout << nx << ' ' << ny << endl;
                s = {nx,ny};
                continue;
            }
        }
        cnt--;
        dir = (dir + 1) % 4;
    }
    cout << cnt << endl;
}
