#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int main(){
	int n, m, l;
	cin >> n >> m >> l;

	vector<int> k(n + 1);
	rep(i,n){
		cin >> k[i];
	}
	k[n] = k[0];

	vector<int> s(m);
	rep(i,m){
		cin >> s[i];
	}

	vector<int> sum(m + 1, 0);
	rep(i,n){
		sum[i + 1] = sum[i] + s[i];
	}

	auto f = [&](int l, int r) -> int {
		return sum[r] - sum[l];
	};


}
