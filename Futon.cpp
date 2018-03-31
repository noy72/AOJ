#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int getValue(map<int,map<int,int>>& m, int a, int b){
	if(m.count(a)){
		if(m[a].count(b)){
			return m[a][b];
		}
	}
	return -1;
}

const int gmax_n = 80000;

int par[gmax_n]; //親
int depth[gmax_n];//木の深さ

void init(int n){
	rep(i,n){
		par[i] = i;
		depth[i] = 0;
	}
}

int find(int x){
	if(par[x] == x){
		return x;
	}else {
		return par[x] = find(par[x]);
	}
}

void unite(int x, int y){
	x = find(x);
	y = find(y);
	if(x == y) return;

	if(depth[x] < depth[y]){
		par[x] = y;
	}else{
		par[y] = x;
		if(depth[x] == depth[y]) depth[x]++;
	}
}

bool same(int x, int y){
	return find(x) == find(y);
}

const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};

void connect(map<int,map<int,int>>& m, int n, int p, int x, int y, int c){
	rep(i,4){
		int nx = x + dx[i];
		int ny = y + dy[i];
		int np = getValue(m, nx, ny);
		if(np == -1) continue;
		if(np == p + n){
			unite(p, np + n);
			unite(p + n, np);
		}else{
			unite(p, np);
			unite(p + n, np + n);
		}
	}

	p += n;
	rep(i,4){
		int nx = x + dx[i] + (c == 'x' ? 1 : 0);
		int ny = y + dy[i] + (c == 'y' ? 1 : 0);
		int np = getValue(m, nx, ny);
		if(np == -1) continue;
		if(np != p - n){
			unite(p, np);
			unite(p + n, np + n);
		}
	}
}

bool f(int n){
	rep(i,n){
		if(same(i, i + n)) return false;
	}
	return true;
}

int main(){
	int n;
	while(cin >> n,n){
		init(n * 4);
		vector<int> x(n), y(n);
		vector<char> c(n);
		rep(i,n){
			cin >> x[i] >> y[i] >> c[i];
		}

		map<int,map<int,int>> ma;
		rep(i,n){
			ma[x[i]][y[i]] = i;
			if(c[i] == 'x') ma[x[i] + 1][y[i]] = i + n;
			else ma[x[i]][y[i] + 1] = i + n;
		}

		rep(i,n){
			connect(ma, n, i, x[i], y[i], c[i]);
		}
		cout << (f(n) ? "Yes" : "No") << endl;
	}
}
