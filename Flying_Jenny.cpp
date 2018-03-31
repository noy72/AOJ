#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int main(){
	vector<int> a = {1,4,1,4,1,2,1,2};
	vector<int> p(8);

	while(cin >> p[0]){
		rep(i,7) cin >> p[i + 1];

		vector<pair<int,pair<int, int>>> v;
		rep(i,8){
			int V = 0, sum = 0;
			rep(j,8){
				V += a[(i + j) % 8];
				V *= 10;
				sum += min(a[(i + j) % 8], p[j]);
			}
			v.emplace_back(make_pair(-sum, make_pair(V,i)));
		}
		sort(all(v));

		rep(i,8){
			if(i) cout << ' ';
			cout << a[(i + v.front().second.second) % 8];
		}
		cout << endl;
	}
}
