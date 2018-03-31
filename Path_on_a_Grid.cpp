#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

const int N = 20;

void printMaze(int w, int h, bool M[N][N], int x, int y){
	rep(i,h + h + 1){
		rep(j,w + w + 1){
			if(i == y and j == x) cout << "*";
			else cout << M[i][j];
		}
		cout << endl;
	}
}

void extensionOfMaze(int w, int h, bool M[N][N]){
	string s[N];
	rep(i,N) cin >> s[i];

	rep(i,N) rep(j,N) M[i][j] = 0;
	rep(i,h + h - 1){
		auto it = s[i].begin();
		if(i % 2 == 0){ //横線
			for(int j = 0; j < w + w - 1; j++){
				if(j % 2 == 0) M[i + 1][j + 1] = 1;
				else{
					M[i + 1][j + 1] = *it == '1' ? true : false;
					it++;
				}
			}
		}else{ //縦線
			for(int j = 0; j < w + w; j++){
				if(j % 2 == 1) M[i + 1][j + 1] = 0;
				else{
					M[i + 1][j + 1] = *it == '1' ? true : false;
					it++;
				}
			}
		}
	}
}

const char dir[4] = {'R', 'D', 'L', 'U'};
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

vector<pair<int,char>> getCommand(bool m[N][N]){
	int y = 0, x = 0;
	m[y + 1][x] = 1;

	int d = 0;
	vector<pair<int,char>> res;
	while(true){
		if(y == 2 and x == 0) break;

		rep(i,4){
			int rh = rightHand[d][i];

			int ny = y + dy[rh];
			int nx = x + dx[rh];
			if(m[ny][nx] == 0){
				d = rh;
				y = y + dy[rh] * 2;
				x = x + dx[rh] * 2;

				int nrh = rightHand[d][0];
				int ny = y + dy[nrh];
				int nx = x + dx[nrh];
				if(m[ny][nx] == 0){
					y = y + dy[nrh] * 0;
					x = x + dx[nrh] * 0;
				}
				if(res.empty() or res.back().second != dir[d]) res.emplace_back(make_pair(1, dir[d]));
				else res.back().first++;
				break;
			}else{ 
				if(i == 0) continue;;
				if(res.empty() or res.back().second != dir[rh]) res.emplace_back(make_pair(1, dir[rh]));
				else res.back().first++;

			}
				//break;
		
		//printMaze(5,5,m,x,y); cout << endl;

	}
	return res;
}

int main(){
	bool m[N][N];
	extensionOfMaze(5, 5, m);
	//printMaze(5, 5, m);
	
	vector<pair<int,char>> tmp = getCommand(m);
	int f = 1;
	for(auto p : tmp){
		//cout << p.first << ' ' << p.second << endl;
		if(p.first == 1) f = 0;
		rep(i,p.first - f){
			cout << p.second;
		}
	}
	cout << endl;
}
