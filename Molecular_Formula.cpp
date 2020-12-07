#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

typedef string::const_iterator State;
map<string, int> m;

int expr(State&);
bool f;

int number(State& p){
	int res = 0;
	while(isdigit(*p)){
		res *= 10;
		res += *p - '0';
		p++;
	}
	return res;
}

int alp(State& p){
	string s;
	s += *p;
	p++;
	if(islower(*p)){
		s+=*p;
		p++;
	}
	if(m.count(s)) return m[s];
	f = true;
	return -1;
}

int factor(State& p){
	assert(*p == '(');
	p++;
	int res = expr(p);
	p++;
	return res;
}


int expr(State& p){
	if(f) return 0;

	int res = 0;
	while(true){
		if(f) return 0;
		if(*p == '('){
			int tmp = factor(p);
			res += tmp * number(p);
		}else if(isdigit(*p)){
			int tmp;

			p--;
			if(islower(*p)){
				p--;
			}
			tmp = alp(p);

			int num = number(p);
			res += (num - 1) * tmp;
		}else if(isupper(*p) or islower(*p)){
			res += alp(p);
		}else{
			break;
		}
	}
	return res;
}

int main(){
	string s;
	while(cin >> s){
		if(s == "END_OF_FIRST_PART") break;
		int t;
		cin >> t;
		m[s] = t;
	}

	while(cin >> s, s[0] != '0'){
		s+='@';
		State tmp = s.begin();
		f = false;
		int ans = expr(tmp);

		if(f) cout << "UNKNOWN" << endl;
		else cout << ans << endl;
	}
}
