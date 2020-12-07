#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;
//const int INF = 1e8;

template<typename T>
ostream& operator << (ostream& os, vector<T>& v){
	rep(i,v.size()){ os << v[i] << (i == v.size() - 1 ? "" : " "); } return os;
}
template<typename T>
istream& operator >> (istream& is, vector<T>& v){
	for(T& x: v){ is >> x; } return is;
}

#define int long long

string solve(int k, int n){
	string res = "";
	rep(i,200){
		res += to_string(i);
	}
	return res.substr(k,n);
}

string solve(int s, int k, int n){
	string res = "";
	for (int i = s; res.size() < k + 200; i++) {
		res += to_string(i);
	}
	return res.substr(k, n);
}

signed main(){
	int k, n;
	while(cin >> k >> n, k||n){
		if(k <= 10){
			cout << solve(k, n) << endl;
			continue;
		}

		int i = 2;
		int t = 10, q = 100, d = 10;
		int idx = 10;
		while(k > idx + (q - d) * i){
			idx += (q - d) * i;
			t += q - d;
			q *= 10;
			d *= 10;
			i++;
		}

		int diff = k - idx;
		int times = diff / i;
		//cout << t + times << ' ' << diff % i << endl;
		cout << solve(t + times, diff % i, n) << endl;
	}
}
