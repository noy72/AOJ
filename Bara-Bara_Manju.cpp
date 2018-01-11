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
		vector<int> a;

		map<int, int> m;
		rep(i,n){
			int x;
			cin >> x;
			m[x]++;
		}

		int ans = 0;
		range(i,1,5){
			int tmp = min(m[i], m[10 - i]);
			ans += tmp;
			m[i]-=tmp;
			m[10 - i]-=tmp;
		}
		ans += m[5] / 2;
		m[5] %= 2;

		for(auto i : m){
			rep(j,i.second){
				a.emplace_back(i.first);
			}
		}

		sort(all(a),greater<int>());

		vector<bool> used(a.size(),0); //すでに袋詰めしたまんじゅう
	}
}
