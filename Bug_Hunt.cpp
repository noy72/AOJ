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
int factor(State&);
int term(State&);
int expression(State&);

map<char, int> length;
map<char, map<int, int>> array_;
bool invalid;
bool right__;
char name;
int p;

// 数字の列をパースして、その数を返す。
int number(State &begin) {
	long long ret = 0;

	while (isdigit(*begin)) {
		ret *= 10;
		ret += *begin - '0';
		begin++;
	}

	if(ret > 2147483647) {
		invalid = true;
		return 0;
	}
	return ret;
}

// 括弧か数をパースして、その評価結果を返す。
int factor(State &begin) {
	if(invalid) return 0;

	if (*begin == '[') {
		begin++; // '('を飛ばす。
		int ret = expression(begin);
		begin++; // ')'を飛ばす。
		return ret;
	} else {
		return number(begin);
	}
	return 0;
}

// 四則演算の式をパースして、その評価結果を返す。
int expression(State &begin) {
	if(invalid) return 0;

	int ret = factor(begin);
	char t = -1;
	for (;;) {
		if (isalpha(*begin)) {
			t = *begin;
			begin++;
			ret = factor(begin);

			//cout << t << ' ' << ret << endl;
			if(length[t] <= ret){
				invalid = true;
				return 0;
			}
			//cout << right__ << endl;
			//cout << inited[t].count(ret) << endl;
			if(right__ and not array_[t].count(ret)){
				invalid = true;
				return 0;
			}
		} else {
			break;
		}
	}

	name = t;
	p = ret;
	return t == -1 ? p : array_[name][p];
}

//beginがexpectedを指していたらbeginを一つ進める。
void consume(State &begin, char expected) {
	if (*begin == expected) {
		begin++;
	} else {
		cerr << "Expected '" << expected << "' but got '" << *begin << "'" << endl;
		cerr << "Rest string is '";
		while (*begin) {
			cerr << *begin++;
		}
		cerr << "'" << endl;
		//throw ParseError();
	}
}

bool containEqual(string& s){
	for(auto i : s){
		if(i == '=') return true;
	}
	return false;
}

int main(){
	while(true){
		string s;
		vector<string> vs;
		while(cin >> s, s != "."){
			vs.emplace_back(s);
		}
		if(vs.empty()) break;

		length.clear();
		array_.clear();
		invalid = false;
		rep(i,vs.size()){
			if(not containEqual(vs[i])){
				State tmp = vs[i].begin();
				tmp++;
				tmp++;
				length[vs[i][0]] = number(tmp);
			}else{
				State tmp = vs[i].begin();
				while(*tmp != '=') tmp++;
				tmp++;
				right__ = true;
				int res = expression(tmp);
				//show(res)

				tmp = vs[i].begin();
				right__ = false;
				expression(tmp);
				array_[name][p] = res;
				//show(*tmp)
			}
			if(invalid){
				cout << i + 1 << endl;
				break;
			}
		}
		if(not invalid) cout << 0 << endl;
	}
}
