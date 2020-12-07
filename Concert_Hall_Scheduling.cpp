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

struct D{
	int l, r, d;
	bool operator < ( const D &right ) const {
		return r < right.r;
	}
};

int main(){
	int n;
	while(cin >> n,n){
		vector<D> d(n);
		rep(i,n){
			auto& p = d[i];
			cin >> p.l >> p.r >> p.d;
			p.l--; p.r--;
		}
		sort(all(d));

		vector<vector<int>> cur(400, vector<int>(400,0));
		rep(i,n){
			const auto& p = d[i];
			for (int j = 365; j >= 0; j--) {
				for (int k = 365; k >= 0; k--) {
					if(j <= p.l){
						cur[p.r + 1][k] = max(cur[p.r + 1][k], cur[j][k] + p.d);
					}
					if(k <= p.l){
						cur[j][p.r + 1] = max(cur[j][p.r + 1], cur[j][k] + p.d);
					}
				}
			}
		}

		int ans = 0;
		rep(i,400){
			rep(j,400){
				ans = max(ans, cur[i][j]);
			}
		}
		cout << ans << endl;
	}
}
