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

bool check(vector<int>& dp){
	rep(i,dp.size()){
		if(i == 0) continue;
		if((i bitand dp[i]) == dp[i]) return false;
	}
	return true;
}

int main(){
	int n;
	while(cin >> n,n){
		string s;
		cin >> s;

		set<pair<int,int>> st;

		int bit = 0;
		rep(i,s.size() - 1){
			if(s[i] == 'u') bit = 0;
			else bit |= 1 << (s[i] - '0');

			//show(bitset<10>(bit))
			if(s[i + 1] != 'u' and bit != 0) st.emplace(bit, s[i + 1] - '0');
		}

		//for(auto i : st){
		//	cout << bitset<10>(i.first) << ' ' << i.second << endl;
		//}

		vector<int> dp(1 << 10, -1);
		dp[0] = 0;
		rep(s,1 << 10){
			if(dp[s] == -1) continue;
			for(auto p : st){
				bit = p.first;
				int nxt = p.second;

				if((bit bitand s) != 0) continue;

				int nbit = bit bitor s;
				if(dp[nbit] == -1) dp[nbit] = 1 << nxt;
				else dp[nbit] |= 1 << nxt;
			}
		}

		//rep(i,dp.size()){
		//	if(dp[i] != -1) cout << bitset<10>(i) << ' ' << bitset<10>(dp[i]) << endl;
		//}

		cout << (check(dp) ? "SAFE" : "UNSAFE") << endl;
	}
}
