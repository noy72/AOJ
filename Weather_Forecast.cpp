#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

#define int long long

bool getBit(int num, int i){
	return ((num & (1 << i)) != 0);
}

int setBit(int num, int i){
	if(i < 0) return num;
	return num | (1 << i);
}

int toInteger(int r[4][4]){
	int k = 1;
	int res = 0;
	rep(i,4){
		rep(j,4){
			res += r[i][j] * k;
			k *= 10;
		}
	}
	return res;
}

void toRow(int num, int r[4][4]){
	rep(i,4){
		rep(j,4){
			r[i][j] = num % 10;
			num /= 10;
		}
	}
}

const int dy[16] = { 0,-1, 0, 1, 0,-2, 0, 2, 0 };
const int dx[16] = { 1, 0,-1, 0, 2, 0,-2, 0, 0 };

int n;
bool fes[366][4][4];
set<pair<int,pair<int,int>>> m;

bool check(long long& rain, int ty, int tx ,int day){
	int r[4][4] = {{0}};

	toRow(rain, r);
	assert(rain == toInteger(r));

	rep(i,4){//全ての場所を+1する
		rep(j,4){
			r[i][j]++;
		}
	}

	range(i,ty, ty + 2){ //雨を降らす部分のみ0にする
		range(j,tx, tx + 2){
			r[i][j] = 0;
			if(fes[day][i][j]) return false; //雨を降らせる部分でまつりがおこなわれる
		}
	}

	rep(i,4){//一箇所でも7カウント以上ならfalse
		rep(j,4){
			if(r[i][j] >= 7) return false;
		}
	}

	rain = toInteger(r);
	return true;
}

bool dfs(long long rain, int y, int x, int day){
	if(m.count(make_pair(rain,make_pair(y * 4 + x,day)))) return false;
	m.emplace(make_pair(rain,make_pair(y * 4 + x,day)));

	if(not check(rain, y, x, day)) return false;
	if(day == n){ return true; }

	bool res = false;
	rep(i,9){
		int ny = y + dy[i];
		int nx = x + dx[i];
		if(ny < 0 || ny >= 3 || nx < 0 || nx >= 3) continue;

		res |= dfs(rain, ny, nx, day + 1);
	}
	return res;
}

signed main(){
	while(cin >> n,n){
		m.clear();
		memset(fes, 0, sizeof(fes));
		rep(i,n){
			rep(j,4){
				rep(k,4){
					cin >> fes[i][j][k];
				}
			}
		}
		cout << dfs(0, 1, 1, 0) << endl;
	}
}
