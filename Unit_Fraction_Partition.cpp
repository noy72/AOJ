#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

double p, q, a, n;
const double base = 100;

int dfs(int k, int n, int start, double sum){
	int res = 0;
	if(n != 0){
		range(i,start,a){
			if(k * i > a) break;
			if(p * i - q < sum * i * q) continue;

			res += dfs(k * i, n - 1, i, sum + base / i);
		}
	}

	if(abs(p / q - sum) < 1e-10) res++;
	return res;
}

int main(){
	while(cin >> p >> q >> a >> n, n) {
		p *= base;
		cout << dfs(1, n, 1, 0) << endl;
	}
}
