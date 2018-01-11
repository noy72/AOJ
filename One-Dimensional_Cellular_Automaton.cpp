#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int M;
typedef vector<vector<int>> mat;

mat mul(mat &a, mat &b){
	mat c(a.size(), vector<int>(b[0].size()));
	rep(i,a.size()){
		rep(k,b.size()){
			rep(j,b[0].size()){
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % M;
			}
		}
	}
	return c;
}

mat pow(mat a, int n){
	mat b(a.size(), vector<int>(a.size()));
	rep(i,a.size()){
		b[i][i] = 1;
	}
	while(n > 0){
		if(n & 1) b = mul(b,a);
		a = mul(a, a);
		n >>= 1;
	}
	return b;
}

int n, x, b, c, t;

int solve(mat o){
	mat a(n, vector<int>(n));
	a[0][0] = b;
	a[0][1] = c;
	range(i,1,n - 1){
		a[i][i - 1] = x;
		a[i][i] = b;
		a[i][i + 1] = c;
	}
	a[n - 1][n - 2] = x;
	a[n - 1][n - 1] = b;

	//for(auto i : a){ for(auto j : i){ cout << j << ' '; } cout << endl; } cout << endl;

	a = pow(a,t); //行列Aのn乗。
	//for(auto i : a){ for(auto j : i){ cout << j << ' '; } cout << endl; } cout << endl;
	o = mul(a,o);
	rep(i,n){
		if(i) cout << ' ';
		cout << o[i][0];
	}
	cout << endl;
	//return a[1][0];
	return 1;
}

int main(){
	while(cin >> n >> M >> x >> b >> c >> t, n){
		mat o(n, vector<int>(1));
		rep(i,n){
			cin >> o[i][0];
		}
		solve(o);
	}
}
