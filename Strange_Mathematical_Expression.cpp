#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

vector<string> split(string in, char sp = ' '){
	vector<string> ret;
	stringstream ss(in);
	string s;
	while(getline(ss, s, sp)){
		ret.emplace_back(s);
	}
	return ret;
}

int main(){
	string in;
	while(getline(cin,in)){
		vector<double> st;
		vector<string> v = split(in);

		for(auto s : v){
			if(s.size() == 1 and not isdigit(s.front())){
				double b = st.back(); st.pop_back();
				double a = st.back(); st.pop_back();
				switch (s[0]) {
					case '+':
						st.emplace_back(a + b);
						break;
					case '-':
						st.emplace_back(a - b);
						break;
					case '*':
						st.emplace_back(a * b);
						break;
					case '/':
						st.emplace_back(a / b);
						break;
				}
			}else{
				st.emplace_back(stod(s));
			}
		}
		cout << fixed << setprecision(7) << st.front() << endl;
	}
}
