#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

template<typename T>
ostream& operator << (ostream& os, vector<T>& v){
	rep(i,v.size()){ os << v[i] << (i == v.size() - 1 ? "" : " "); } return os;
}
template<typename T>
istream& operator >> (istream& is, vector<T>& v){
	for(T& x: v){ is >> x; } return is;
}

vector<char> solve(string& s){
	vector<char> st;
	for(auto c : s){
		if(st.empty()) st.emplace_back(c);
		else{
			if(st.back() == '(' and c == ')'){
				st.pop_back();
			}else{
				st.emplace_back(c);
			}
		}
	}
	return st;
}

bool check(vector<bool>& b){
	for(auto i : b) if(not i) return false;
	return true;
}

int main(){
	int n;
	cin >> n;

	vector<string> s;
	rep(i,n){
		string t;
		cin >> t;

		vector<char> st = solve(t);
		if(st.empty()) continue;

		string tmp;
		for(auto c : st){
			tmp += c;
		}
		s.emplace_back(tmp);
	}


	vector<int> l, r;
	vector<pair<int, int>> m;
	rep(i,s.size()){
		map<char, int> ma;
		for(auto c : s[i]) ma[c]++;
		if(ma.size() == 1){
			if(ma.begin()->first == '(') l.emplace_back(ma.begin()->second);
			if(ma.begin()->first == ')') r.emplace_back(ma.begin()->second);
		}else{
			m.emplace_back(ma['('], ma[')']);
		}
	}

	//cout << l << endl;
	//cout << r << endl;
	//rep(i,m.size()){
	//	cout << m[i].first << ' ' << m[i].second << endl;
	//}

	int sum = accumulate(all(l), 0);
	vector<bool> used(m.size(), false);
	rep(i,m.size()){
		int maxi = -1e9, p = -1, mini = 1e9;;
		rep(j,m.size()){
			if(sum >= m[j].second and maxi < m[j].first - m[j].second and not used[j]){
				maxi = m[j].first - m[j].second;
				mini = m[j].second;
				p = j;
			}else if(sum >= m[j].second and maxi == m[j].first - m[j].second and not used[j] and m[j].first > m[j].second){
				mini = m[j].second;
				p = j;
			}
		}
		if(p == -1) continue;
		//cout << p << endl;
		used[p] = true;
		sum += m[p].first - m[p].second;
	}

	sum -= accumulate(all(r), 0);

	cout << (sum == 0 and check(used) ? "Yes" : "No") << endl;
}
