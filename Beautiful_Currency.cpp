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

double getRatio(double a, double b){
	return abs(a - b) / a;
}

int main(){
	int n;
	cin >> n;

	vector<int> a(n);
	cin >> a;

	vector<vector<double>> dp(n, vector<double>(200000, numeric_limits<double>::max()));
	rep(i,n){
		range(j,1,200000){
			if(i == 0){
				dp[i][j] = getRatio(a[i], j);
			}else{
				for(int k = j; k < 200000; k+=j){
					dp[i][k] = min(dp[i][k], max(dp[i - 1][j], getRatio(a[i], k)));
				}
			}
		}
	}

	cout << fixed << setprecision(10) << *min_element(all(dp[n - 1])) << endl;
}
