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

bool getBit(long long num, int i){
	return ((num & (1LL << i)) != 0);
}

vector<int> atk, sum;
vector<long long> bit;
int maxi;

void input(int n){
	vector<string> name(n);
	vector<vector<string>> near(n);

	map<string, int> id;
	rep(i,n){
		int d;
		cin >> name[i] >> atk[i] >> d;
		id[name[i]] = i;
		while(d--){
			string s;
			cin >> s;
			near[i].emplace_back(s);
		}
	}

	rep(i,n){
		sum[i + 1] = sum[i] + atk[i];
	}

	rep(i,n){
		bit[i] |= 1LL << i;
		for(auto s : near[i]){
			bit[i] |= 1LL << id[s];
		}
		//cout << bitset<10>(bit[i]) << endl;
	}
}

void dfs(int& n, int i, long long enemy, int total){
	maxi = max(maxi, total);
	if(i == n) return;
	if(total + sum[n] - sum[i] < maxi) return;
	
	if(not getBit(enemy,i)){
		dfs(n, i + 1, enemy bitor bit[i], total + atk[i]);
	}
	dfs(n, i + 1, enemy, total);
}

//map<pair<long long, long long>, int> memo1, memo2;
vector<int> dp; // dp[s] := 集合sから任意の数, 仲間を選べるときの最大値

int main(){
	int n;
	while(cin >> n,n){
		atk = vector<int>(n);
		sum = vector<int>(n + 1, 0);
		bit = vector<long long>(n,0);
		input(n);

		maxi = 0;
		dfs(n, 0, bit[0], atk[0]);
		cout << maxi << endl;
	}
}
