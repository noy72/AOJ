#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

map<string, set<int>> memo;

int toNum(string str){
	int num = 0;
	rep(i,str.size()){
		num *= 10;
		num += str[i] - '0';
	}
	return num;
}

bool numCheck(string s){
	for(auto i : s){
		if(not isdigit(i)) return false;
	}
	return true;
}

auto close(string::iterator it){
	int c = 0;
	while(true){
		if(*it == '(') c++;
		else if(*it == ')') c--;

		if(c == 0) return it;
		it++;
	}
	assert(false);
	return it;
}

set<int> expr(string s){
	if(memo.count(s)) return memo[s];
	if(numCheck(s)) return memo[s] = {toNum(s)};
	if(s.front() == '(' && close(s.begin()) == --s.end()){
		return memo[s] = expr(string(++s.begin(), --s.end()));
	}

	set<int> res;
	for(auto it = s.begin(); it != s.end(); it++){
		if(*it == '(') it = close(it);

		if(not isdigit(*it) && *it != ')'){
			//cout << string(s.begin(), it) << ' ' << string(it + 1, s.end()) << endl;
			set<int> a = expr(string(s.begin(), it));
			set<int> b = expr(string(it + 1, s.end()));

			for(auto i : a){
				for(auto j : b){
					if(j == 0 && *it == '/') continue;
					switch (*it) {
						case '+':
							res.emplace(i + j);
							break;
						case '-':
							res.emplace(i - j);
							break;
						case '*':
							res.emplace(i * j);
							break;
						case '/':
							res.emplace(i / j);
							break;
					}
				}
			}
		}
	}
	return res;
}

int main(){
	string s;
	while(cin >> s, s[0] != '#'){
		cout << expr(s).size() << endl;
	}
}
