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


typedef string::const_iterator State;
int number(State&);
pair<int,bool> factor(State&);
pair<int,bool> term(State&);
pair<int,bool> expression(State&);

bool invalid;

// 数字の列をパースして、その数を返す。
int number(State &begin) {
	if(not isdigit(*begin)){
		invalid = true;
		return 0;
	}

	int ret = 0;

	while (isdigit(*begin)) {
		ret *= 2;
		ret += *begin - '0';
		begin++;
	}

	if(ret >= 1024){
		invalid = true;
		return 0;
	}
	return ret;
}

// 括弧か数をパースして、その評価結果を返す。
pair<int,bool> factor(State &begin) {
	if(invalid) return make_pair(0,0);
	if (*begin == '(') {
		begin++; // '('を飛ばす。
		pair<int,bool> ret = expression(begin);
		if(not ret.second) {
			invalid = true;
		}
		begin++; // ')'を飛ばす。
		ret.second = 0;
		return ret;
	} else {
		return make_pair(number(begin), 0);
	}
	return make_pair(0, 0);
}

// 乗算除算の式をパースして、その評価結果を返す。
pair<int,bool> term(State &begin) {
	if(invalid) return make_pair(0,0);
	pair<int,bool> ret = factor(begin);

	for (;;) {
		if (*begin == '*') {
			begin++;
			ret.second = true;
			ret.first *= factor(begin).first;
			if(ret.first >= 1024) {
				invalid = true;
				return make_pair(0,0);
			}
		} else {
			break;
		}
	}

	return ret;
}

// 四則演算の式をパースして、その評価結果を返す。
pair<int,bool> expression(State &begin) {
	if(invalid) return make_pair(0,0);
	pair<int,bool> ret = term(begin);

	for (;;) {
		if (*begin == '+') {
			begin++;
			ret.second = true;
			ret.first += term(begin).first;
			if(ret.first >= 1024) {
				invalid = true;
				return make_pair(0,0);
			}
		} else if (*begin == '-') {
			begin++;
			ret.second = true;
			ret.first -= term(begin).first;
			if(ret.first < 0) {
				invalid = true;
				return make_pair(0,0);
			}
		} else {
			break;
		}
	}

	return ret;
}


const string c = "01+-*()";

int dfs(string& s, int i){
	if(i == s.size()){
		invalid = false;
		State tmp = s.begin();

		pair<int,bool> ans = expression(tmp);
		if(ans.first >= 1024 or ans.first < 0 or tmp != s.end()) return -1e5;
		return invalid ? -1e5 : ans.first;
	}

	while(s[i] != '.' and i < s.size()){
		i++;
	}

	if(s[i] == '.'){
		int res = -1e5;
		rep(j,c.size()){
			s[i] = c[j];
			res = max(res, dfs(s, i));
			s[i] = '.';
		}
		return res;
	}else{
		return dfs(s, i);
	}
}

int main(){
	string s;
	cin >> s;

	int ans = dfs(s, 0);
	cout << (ans == -1e5 ? -1 : ans) << endl;
}
