#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

#define int long long

vector<long long> bit(50);
vector<int> sum(50);
int n;
int maximum;
int b[50];

bool getBit(int num, int i){
	return ((num & (1 << i)) != 0);
}

int setBit(int num, int i){
	return num | (1 << i);
}

void dfs(int p, long long used , int score){
	maximum = max(maximum, score);
	if(p == n) return;
	if(score + sum[p] <= maximum) return;
	if(not getBit(used,p)) dfs(p + 1, used bitor bit[p], score + b[p]);
	dfs(p + 1, used, score);
}

signed main(){
	while(cin >> n,n){
		string a[50], d[50][50];
		int c[50];
		map<string,int> id;

		bit.clear();
		sum.clear();
		maximum = 0;

		rep(i,n){
			cin >> a[i] >> b[i] >> c[i];
			id[a[i]] = i;
			rep(j,c[i]){
				string s;
				cin >> d[i][j];
			}
		}
		for(int i = n - 1; i >= 0; i--){
			sum[i] = sum[i + 1] + b[i];
		}
		rep(i,n){
			long long near = 0;
			rep(j,c[i]){
				near = setBit(near, id[d[i][j]]);
			}
			bit[i] = near;
		}

		dfs(1, bit[0], b[0]);
		cout << maximum << endl;
	}
}
