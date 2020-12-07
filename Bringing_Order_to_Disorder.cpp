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

int length;
long long sum;

void init(long long n){
	while(n != 0){
		sum += n % 10;
		n/=10;
		length++;
	}
}

pair<long long, long long> solve1(long long n){
	vector<vector<long long>> dp(length + 1, vector<long long>(sum + 1, 0));
	dp[0][sum] = 1;
	rep(i,length){
		rep(j,sum + 1){
			rep(k,10){
				if(j - k < 0) break;
				dp[i + 1][j - k] += dp[i][j];
			}
		}
	}

	long long res = 0;
	range(i,1,sum + 1) res += dp[length][i];
	return make_pair(res, dp[length].front());
}

long long solve2(long long n){
	string s = to_string(n);
	
	long long res = 1;
	rep(i,s.size()){
		res *= (i + 1);
	}

	map<char,int> m;
	for(auto c : s) m[c]++;
	
	vector<long long> fact(10, 1);
	range(i,1,10) fact[i] = fact[i - 1] * i;
	for(auto p : m){
		res /= fact[p.second];
	}
	return res;
}

long long solve3(long long n){
	vector<vector<long long>> dp(length, vector<long long>(2));
	string s = to_string(n);

}

int main(){
	long long n;
	cin >> n;

	init(n);

	pair<long long,long long> s1 = solve1(n); // first : 1を満たす
	cout << s1.first << ' ' << s1.second << endl;
	long long s2 = solve2(n);
	cout << s2 << endl;


}
