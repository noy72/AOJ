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

//i番目のビットを返す
bool getBit(int num, int i){
	return ((num & (1 << i)) != 0);
}

//i番目を1にする
int setBit(int num, int i){
	return num | (1 << i);
}

//i番目を0にする
int clearBit(int num, int i){
	int mask = ~(1 << i);
	return num & mask;
}

//i番目をvで置き換える
int updateBit(int num, int i, int v){
	int mask = ~(1 << i);
	return (num & mask) | (v << i);
}

int main(){
	int m, n;
	cin >> m >> n;

	vector<vector<double>> p(m, vector<double>(n));
	rep(i,m){
		rep(j,n){
			cin >> p[i][j];
		}
		p[i].emplace_back(0);
	}

	// dp[s][i] := remain s cat, last cat is defeated by i-th enemy
	vector<vector<double>> dp(1 << m, vector<double>(n + 1, 0));

	// all enemy are defeated, parcentage of "defeating all enemy" is 0.
	// but set it to 1 for computational reaons
	rep(i,1 << m) dp[i][n] = 1;

	for(int s = (1 << m) - 1; s >= 0; s--){
		// i-th cat fight j-th enemy and is beated k-th enemy.
		for(int i = n; i >= 0; i--){
			rep(j,m){
				if(not (s >> j & 1)) continue;
				dp[
			}
		}
	}

	cout << fixed << setprecision(10) << dp[0][0] << endl;
}
