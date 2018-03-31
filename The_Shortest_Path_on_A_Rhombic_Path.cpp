#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

vector<string> split(string in, char sp = ','){
	vector<string> ret;
	stringstream ss(in);
	string s;
	while(getline(ss, s, sp)){
		ret.emplace_back(s);
	}
	return ret;
}

int main(){
	vector<string> s;
	string in;
	while(cin >> in){
		s.emplace_back(in);
	}

	vector<vector<int>> v(s.size());
	rep(i,s.size()){
		vector<string> sp = split(s[i]);
		for(auto j : sp){
			v[i].emplace_back(stoi(j));
		}
	}

	vector<vector<int>> dp(all(v));
	rep(i,s.size() / 2){
		rep(j,v[i].size()){
			dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + v[i + 1][j]);
			dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + v[i + 1][j + 1]);
		}
	}
	range(i,s.size() / 2, s.size()){
		rep(j,v[i].size() - 1){
			dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + v[i + 1][j]);
			dp[i + 1][j] = max(dp[i + 1][j], dp[i][j + 1] + v[i + 1][j]);
		}
	}
	cout << dp.back().front() << endl;
}
