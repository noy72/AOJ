#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;
const long long M = 67280421310721LL;

vector<string> split(string in, char sp = ' '){
	vector<string> ret;
	stringstream ss(in);
	string s;
	while(getline(ss, s, sp)){
		ret.emplace_back(s);
	}
	return ret;
}

void modmod(vector<string> sp, int start){
	range(i,start,10){
		vector<long long> a(3,0);
		rep(j,3){
			for(auto c : sp[j]){
				(a[j] *= 10) %= M;
				if(c == 'X') a[j] += i;
				else a[j] += c - '0';
			}
		}
		if((a[0] + a[1]) % M == a[2] % M){
			cout << i << endl;
			return;
		}
	}
	cout << "NA" << endl;
	return;
}

int main(){
	string s;
	while(cin >> s){
		rep(i,s.size()) if(s[i] == '+') s[i] = '=';
		vector<string> sp = split(s, '=');

		int start = 0;
		for(auto& i : sp) if(i.front() == 'X' and i.size() > 1) start = 1;
		modmod(sp, start);
	}
}
