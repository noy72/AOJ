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
	string s, t;
	cin >> s >> t;

	for(int len = min(s.size(), t.size()); len >= 0; len--){
		set<vector<int>> st;

		vector<int> cnt(26,0);
		int i = 0;
		while(i < len){
			cnt[ s[i++] - 'a' ]++;
		}
		st.emplace(cnt);
		while(i < s.size()){
			cnt[ s[i] - 'a' ]++;
			cnt[ s[i - len] - 'a' ]--;
			st.emplace(cnt);
			i++;
		}

		cnt = vector<int>(26,0);
		i = 0;
		while(i < len){
			cnt[ t[i++] - 'a' ]++;
		}
		if(st.count(cnt)){
			cout << len << endl;
			return 0;
		}

		while(i < t.size()){
			cnt[ t[i] - 'a' ]++;
			cnt[ t[i - len] - 'a' ]--;
			if(st.count(cnt)){
				cout << len << endl;
				return 0;
			}
			i++;
		}
	}
	cout << 0 << endl;
}
