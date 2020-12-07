#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

bool canUseVer(int v, int ver, vector<long long>& c, bool u[20][20]){
	rep(i,c.size()){
		if(u[c[i]][ver]) return false;
	}
	return true;
}

bool f;
int st;
vector<long long> dfs(vector<long long> c, int v, int n, bool u[20][20]){
	if(n == c.size()){
		return c;
	}

	vector<long long> res;
	int s = c.empty() ? 0 : c.back() + 1;
	s = f and s == 0 ? st : s;
	range(i,s,v){
		if(canUseVer(v, i, c, u)){
			c.emplace_back(i);
			res = dfs(c, v, n, u);
			if(res.size() == n) return res;
			c.pop_back();
		}
	}
	return vector<long long>();
}

bool search(bool u[20][20], int v, int n){
	vector<long long> tmp;
	vector<long long> c = dfs(tmp, v, n, u);
	if(c.size() == n){
		for(auto i : c){
			//cout << i << ' ' ;
			for(auto j : c){
				u[i][j] = u[j][i] = true;
			}
		}
		//cout << endl;
		return true;
	}
	return false;
}

bool C(int v, vector<long long>& a){
	bool u[20][20] = {{0}};
	rep(i,a.size()){
		f = true;
		st = i / 2;
		if(not search(u, v, a[i])){
			return false;
		}
	}
	return true;
}

int main(){
	int n;
	cin >> n;

	long long ans = 0;
	vector<long long> a(n);
	rep(i,n){
		cin >> a[i];
		ans += max<long long>(a[i] - 4L, 0L);
		a[i] -= max<long long>(a[i] - 4L, 0L);
	}
	sort(all(a),greater<long long>());

	int right = 20, left = 1;
	rep(i,10){
		int mid = (right + left) / 2;
		if(C(mid, a)) right = mid;
		else left = mid;
	}
	C(10,a);
	cout << ans + right << endl;
}
