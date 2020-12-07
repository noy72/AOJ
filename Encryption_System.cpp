#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

string s;
vector<string> st;
void dfs(string t, vector<bool> use){
	if(s.size() == t.size()){
		if(t.find("{") == string::npos) st.emplace_back(t);
		return;
	}

	char c = s[t.size()];
	if(c == 'a'){
		t += c;
		dfs(t, use);
		t.pop_back();
	}
	if(not use[c - 'a' + 1]){
		t += c + 1;
		use[c - 'a' + 1] = true;
		dfs(t, use);
		use[c - 'a' + 1] = false;
		t.pop_back();
	}
	if(use[c - 'a']){
		t += c;
		use[c - 'a'] = true;
		dfs(t, use);
		use[c - 'a'] = false;
		t.pop_back();
	}
}

int main(){
	while(cin >> s, s[0] != '#'){
		st.clear();
		dfs("", vector<bool>(27,0));
		sort(all(st));

		cout << st.size() << endl;

		if(st.size() <= 10){
			for(auto t : st){
				cout << t << endl;
			}
		}else{
			rep(i,5){
				cout << st[i] << endl;
			}
			rep(i,5){
				cout << st[st.size() - 5 + i] << endl;
			}
		}
	}
}
