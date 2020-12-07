#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const long long INF = 1e10;

const int MAX_D = 1000005;

vector<long long> dp(vector<pair<long long, long long>>& a){
	vector<long long> res(MAX_D, INF);
	res[0] = 0;
	rep(i,MAX_D){
		rep(j,a.size()){
			int idx = min<int>(i + a[j].second, MAX_D - 1);
			res[idx] = min(res[idx], res[i] + a[j].first);
		}
	}

	return res;
}

int main(){
	int n;
	while(cin >> n,n){
		vector<long long> h(n);
		rep(i,n){
			cin >> h[i];
		}

		int m;
		cin >> m;
		vector<pair<long long,long long>> s, a; // first MP, second damage
		rep(i,m){
			long long MP, damage;
			string target;
			cin >> target >> MP >> target >> damage;
			(target  == "Single" ? s : a).emplace_back(MP, damage);
		}

		vector<long long> al = dp(a);
		vector<long long> si = dp(s);

		for (int i = MAX_D - 1; i > 0; i--) {
			si[i - 1] = min(si[i - 1], si[i]);
		}

		long long ans = al[*max_element(all(h))];
		rep(i,MAX_D){
			if(al[i] == INF) continue;
			long long sum = al[i];
			rep(j,n){
				sum += si[max(h[j] - i, 0LL)];
			}
			ans = min(ans, sum);
		}
		cout << ans << endl;
	}
}
