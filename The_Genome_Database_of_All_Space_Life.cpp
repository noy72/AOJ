#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int k;
string s, ans;

typedef string::const_iterator State;
int number(State&);
string factor(State&);
string expression(State&);

int number(State& begin){
	int res = 0;
	while(isdigit(*begin)){
		res *= 10;
		res += *begin - '0';
		begin++;
	}
	return res;
}

string factor(State &begin){
	begin++;
	string ret = expression(begin);
	begin++;
	return ret;
}

string expression(State& begin){
	string res;
	while(begin != s.end() or res.size() > k){
		if(isdigit(*begin)){
			int loop = number(begin);

			string tmp;
			if(*begin == '('){
				tmp = factor(begin);
			}else{
				tmp = *begin;
				begin++;
			}

			rep(i,loop){
				if(res.size() > k) break;
				res += tmp;
			}
		}else if(isupper(*begin)){
			res += *begin;
			begin++;
		}else{
			break;
		}
	}
	return res;
}

int main(){
	while(cin >> s >> k, s != "0"){
		State tmp = s.begin();
		string t = expression(tmp);
		if(t.size() - 1 < k) cout << 0 << endl;
		else cout << t[k] << endl;
	}
}
