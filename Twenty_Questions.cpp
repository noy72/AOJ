#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

typedef bitset<15> bit;

int main(){
	int m, n;
	while(cin >> m >> n, n){
		vector<bit> b(n);
		rep(i,n){
			string s;
			cin >> s;
			b[i] = bit(s);
		}

		size_t ans = 100;
		for(auto i = 0uL; i < 1uL << m; i++){
			set<unsigned long> s;
			bit mask(i);
			rep(j,n){
				bit tmp = mask & b[j];
				s.emplace(tmp.to_ulong());
			}
			if(s.size() == n){
				show(mask.count())
				ans = min(ans, mask.count());
			}
		}
		cout << ans << endl;
	}
}
