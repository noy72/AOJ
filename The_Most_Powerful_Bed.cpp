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

const int INF = 1e8;

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
	int n, m;
	while(cin >> n >> m,n||m){
		vector<int> S(n), d(m);
		cin >> S >> d;

		sort(all(d));

		vector<int> sum(1 << n, 0);
		rep(s,1 << n){
			rep(i,n){
				if(getBit(s, i)) sum[s] += S[i];
			}
		}

		vector<vector<int>> dp(m + 1, vector<int>(1 << n, INF));
		dp[0][0] = 0;
		//rep(i, 1 << n) dp[0][i] = 0;
		rep(i,m){
			rep(s, 1 << n){
				dp[i + 1][s] = min(dp[i + 1][s], dp[i][s] + abs(d[i] - sum[s]));

				rep(j,n){
					int b = setBit(s, j);
					dp[i + 1][b] = min(dp[i + 1][b], dp[i][s] + abs(d[i] - sum[b]));
					dp[i][b] = min(dp[i][b], dp[i][s]);
				}
			}
		}
		//rep(j,m){
		//	cout << dp[2][j] << endl;
		//	cout << dp[6][j] << endl;
		//}

		cout << *min_element(all(dp[m])) << endl;
	}
}
