#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

template<typename T>
ostream& operator << (ostream& os, vector<T>& v){
	rep(i,v.size()){ os << v[i] << (i == v.size() - 1 ? "" : " "); } return os;
}
template<typename T>
istream& operator >> (istream& is, vector<T>& v){
	for(T& x: v){ is >> x; } return is;
}

const int MAX_N = 100;

// 0 >, 1 v, 2 <, 3 ^
void getMaze(int n, vector<vector<bool>>& w, bool wall[MAX_N][MAX_N][4]){
	memset(wall, 0, sizeof(bool) * MAX_N * MAX_N * 4);
	for (int i = 1; i < w.size(); i+=2) {
		rep(j,n){
			if(w[i][j]) wall[i / 2][j][2] = true;
			if(w[i][j + 1]) wall[i / 2][j][0] = true;

			if(w[i - 1][j]) wall[i / 2][j][3] = true;
			if(w[i + 1][j]) wall[i / 2][j][1] = true;
		}
	}
}

// 右手法
// right[d] := d方向（東から時計回り）を向いているときの優先順序
const int rightHand[4][4] = {
	{1,0,3,2},
	{2,1,0,3},
	{3,2,1,0},
	{0,3,2,1}
};

const int dy[16] = { 0, 1, 0,-1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

const char dir[] = {'R', 'D', 'L', 'U'};

int main(){
	int n = 6;

	vector<vector<bool>> w(n * 2 + 1, vector<bool>(n + 1));
	rep(i,n * 2 + 1){
		string s;
		if(i <= 1 or i >= n * 2 - 1) s = "0000";
		else cin >> s;
		s = "0" + s + "0";
		rep(j,s.size()) w[i][j] = s[j] == '1' ? true : false;
	}

	bool wall[MAX_N][MAX_N][4];
	getMaze(n, w, wall);

	int y = 0, x = 1, d = 0;
	string ans;
	while(not (not ans.empty() and y == 0 and x == 0)){
		//show(ans)
		//cout << y << ' ' << x << endl;
		//auto p = wall[y][x];
		//cout << p[0] << p[1]  << p[2]  << p[3] << endl;
		rep(i,4){
			int rh = rightHand[d][i];
			if(wall[y][x][rh]) continue;

			int ny = y + dy[rh];
			int nx = x + dx[rh];
			if(ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			y = ny;
			x = nx;
			d = rh;
			ans += dir[rh];
			break;
		}
	}
	cout << ans << endl;
}
