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

vector<vector<int>> surface = {
	{1, 2, 4},
	{0, 3, 5},
	{0, 3, 6},
	{1, 2, 7},
	{5, 6, 0},
	{4, 7, 1},
	{4, 7, 2},
	{5, 6, 3},
};

int main(){
	vector<string> s(8);
	while(cin >> s){
		map<string, int> m;
		int k = 0;
		for(auto i : s){
			if(not m.count(i)) m[i] = k++;
		}

		vector<int> v;
		for(auto i : s){
			v.emplace_back(m[i]);
		}

		set<vector<vector<int>>> ans;
		//do{
		rep(i,3){
			if(i == 0) v = vector<int>{0,1,0,1,1,1,1,1};
			if(i == 1) v = vector<int>{0,1,1,0,1,1,1,1};
			if(i == 2) v = vector<int>{0,1,1,1,1,1,1,0};
			vector<vector<int>> tmp(8);
			rep(i,surface.size()){
				vector<int> st;
				for(auto j : surface[i]){
					st.emplace_back(v[j]);
				}
				tmp[i] = st;
			}
			sort(all(tmp));
			for(auto j : tmp){
				for(auto k : j.second){
					cout << k<< ' ';
				}
				cout << endl;
			}
			cout << endl;
			ans.emplace(tmp);
		}
		//}while(next_permutation(all(v)));
		cout << ans.size() << endl;
	}
}
