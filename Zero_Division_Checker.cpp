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

bool isOp(string& s){
	return s.size() == 1 and not isalpha(s[0]) and not isdigit(s[0]);
}

set<int> getNumbers(map<string, pair<int,int>>& var, string& a){
	set<int> res;
	range(i, var[a].first, var[a].second + 1){
		res.emplace(i);
	}
	return res;
}

bool f;
set<int> cul(set<int>& a, set<int>& b, string op){
	set<int> res;
	for(auto i : a){
		for(auto j : b){
			//cout << i << ' ' << j << endl;
			if(op == "+") res.emplace((i + j) % 256);
			else if(op == "-") res.emplace((i - j + 256) % 256);
			else if(op == "*") res.emplace((i * j) % 256);
			else if(op == "/"){
				if(j == 0) f = false;
				else res.emplace((i / j) % 256);
			}
		}
	}
	return res;
}

int main(){

	int m;
	cin >> m;

	map<string, pair<int, int>> var;
	rep(i,m){
		string name;
		int l, r;
		cin >> name >> l >> r;
		var[name] = make_pair(l, r);
	}

	int n;
	cin >> n;

	stack<set<int>> st;
	f = true;
	rep(i,n){
		string s;
		cin >> s;

		if(isOp(s)){
			set<int> b = st.top(); st.pop();
			set<int> a = st.top(); st.pop();
			st.emplace(cul(a, b, s));
		}else{
			if(var.count(s)){
				st.emplace(getNumbers(var, s));
			}else{
				st.emplace(set<int>{stoi(s)});
			}
		}
	}

	cout << (f ? "correct" : "error") << endl;
}
