#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int main(){
	int n;
	while(cin >> n,n){
		vector<int> r(n), w(n);
		rep(i,n){
			cin >> r[i] >> w[i];
		}
		auto it = max_element(all(r));
		int maxi = distance(r.begin(), it);

		int sum = accumulate(all(r),0);
		int cnt = 0;

		if(sum - *it < *it){
			int s = *it * 2 - sum;
			vector<bool> dp(s + 1,0);
			dp[0] = 1;
			rep(i,n){
				if(maxi == i) continue;
				for(int j = s; j >= w[i]; j--){
					if(dp[j - w[i]]) dp[j] = true;
				}
			}

			for(int i = s; i >= 0; i--) {
				if(dp[i]) {
					cnt = s - i;
					break;
				}
			}
			//rep(i,it->first + 1){ cout << dp[i] << ' '; } cout << endl;
		}
		cout << accumulate(all(r),0) + accumulate(all(w),0) + cnt << endl;
	}
}
