#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int MAX = 55;

const int dy[16] = { 0, 1, 0,-1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

// 右手法
// right[d] := d方向（東から時計回り）を向いているときの優先順序
const int rightHand[4][4] = {
{1,0,3,2},
{2,1,0,3},
{3,2,1,0},
{0,3,2,1}
};

int main(){
    int h, w;
    cin >> h >> w;

    char m[MAX][MAX];
    rep(i,h + 2) rep(j, w + 2) m[i][j] = '#';

    int dir = -1;
	int y = -1, x = -1;
    range(i,1,h + 1){
        range(j,1,w + 1){
            cin >> m[i][j];
            if(m[i][j] == '>') dir = 0;
            else if(m[i][j] == 'v') dir = 1;
            else if(m[i][j] == '<') dir = 2;
            else if(m[i][j] == '^') dir = 3;
            if(dir != -1 && x == -1){
				y = i;
				x = j;
			}
        }
    }
    m[y][x] = '.';

	bool u[MAX][MAX] = {{0}};
	int move = 1e4;
    while(m[y][x] != 'G'){
		//cout << x << ' ' << y << endl;
		move--;
		if(move == 0) break;
		u[y][x] = true;
        rep(i,4){
			int rh = rightHand[dir][i];
            int ny = y + dy[rh];
            int nx = x + dx[rh];
            if(ny < 1 || ny > h || nx < 1 || nx > w) continue;
            if(m[ny][nx] == '#') continue;
			x = nx;
			y = ny;
			dir = rh;
			break;
        }
    }

	if(move == 0){
		cout << -1 << endl;
		return 0;
	}

	int cnt = 1;
	rep(i,MAX) rep(j,MAX) if(u[i][j]) cnt++;
    cout << cnt << endl;
}
