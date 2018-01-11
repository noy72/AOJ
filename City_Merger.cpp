#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

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


int connect(string a, string b){
	rep(i,a.size()){
		string a_sub = a.substr(i,min(a.size() - i, b.size()));
		string b_sub = b.substr(0,a_sub.size());
		if(a_sub == b_sub){
			return b.size() - b_sub.size();
		}
	}
	return b.size();
}

int main(){
	int n;
	while(cin >> n,n){
		vector<string> in(n);
		rep(i,n){ cin >> in[i]; }

		vector<string> str;
		rep(i,n){
			bool f = false;
			rep(j,n){
				if(i == j) continue;
				if(string::npos != in[j].find(in[i])){
					f = true;
				}
			}
			if(not f) str.emplace_back(in[i]);
		}


		int c[20][20];
		n = str.size();
		rep(i,n){
			rep(j,n){
				if(i == j) continue;
				c[i][j] = connect(str[i], str[j]);
			}
		}

		int dp[1 << 14][20];
		rep(i,1 << 14) rep(j,20) dp[i][j] = INF;
		rep(i,n) dp[setBit(0,i)][i] = str[i].size();
		//rep(i,1 << n){ rep(j,n){ cout << dp[i][j] << endl; } cout << endl; }

		rep(s, 1 << n){
			rep(i,n){
				if(not getBit(s,i)) continue;
				rep(j,n){
					if(getBit(s,j)) continue;
					//cout << i << ' ' << j << endl;
					//show(c[i][j])
					dp[setBit(s,j)][j] = min(dp[setBit(s,j)][j], dp[s][i] + c[i][j]);
				}
			}
		}
		//rep(i,1 << n){ rep(j,n){ cout << dp[i][j] << endl; } cout << endl; }

		int ans = INF;
		rep(i,n){
			ans = min(ans, dp[(1 << n) - 1][i]);
		}
		cout << ans << endl;
	}
}
