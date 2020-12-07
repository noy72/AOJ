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

int main(){
	set<char> st = {'a', 'i', 'u', 'e', 'o'};

	int n;
	while(cin >> n,n){
		vector<string> v(n);
		rep(i,n){
			cin >> v[i];
		}

		vector<string> t(n);
		rep(i,n){
			string tmp;
			tmp = v[i].front();
			range(j,1,v[i].size()){
				if(st.count(v[i][j - 1])){
					tmp += v[i][j];
				}
			}
			t[i] = tmp;
		}

		bool f = true;
		range(k,1,55){
			set<string> c;
			rep(i,n){
				c.emplace(t[i].substr(0,min<int>(k, t[i].size())));
			}
			if(c.size() == n){
				cout << k << endl;
				f = false;
				break;
			}
		}
		if(f) cout << -1 << endl;
	}
}
