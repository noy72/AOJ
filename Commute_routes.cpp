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

int main(){
	int h, w;
	cin >> h >> w;

	const int m = 100000;
	int dp[101][101][2] = {{{0}}};
	dp[0][0][0] = 1;
	rep(i,h){
		rep(j,w){
			dp[i + 1][j][1] += dp[i][j][0];
			dp[i][j + 1][1] += dp[i][j][0];
		}
	}
}
