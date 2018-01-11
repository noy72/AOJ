#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int main(){
	long long n, p, q;
	cin >> n >> p >> q;

	vector<long long> c(n);
	long long sum = 0;
	rep(i,n){
		cin >> c[i];
		sum += c[i];
	}

	vector<long long> minus(n);
	rep(i,n){
		minus[i] = p * i + c[i];
	}
	sort(all(minus));

	long long ans = sum;
	long long m = 0;
	range(i,1,n + 1){
		m += minus[i - 1];
		//cout << i * p * q << ' ' << p * i * (i - 1) << ' ' << m << endl;
		ans = max(ans, sum + i * p * q + p * i * (i - 1) - m);
	}
	cout << ans << endl;
}
