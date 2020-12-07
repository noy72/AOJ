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

void putMedal(int& limit , map<int,int>& m, int x){
	m[x]++;

	auto it = m.find(x);
	cout << it->first << ' ' << it->second << endl;
	if(it == m.begin()) return;

	for(; it != m.begin(); it--){
		//show(distance(m.begin(), it))
		if(it->second == 2){
			it->second = 0;
			m[ it->first - 1]++;
		}else{
			break;
		}
	}

	while(m.count(limit + 1)) limit++;
}

bool containOther(map<int,int>& m){
	for(auto i : m){
		if(i.first != 0 and i.second != 0) return true;
	}
	return false;
}

int main(){
	int n;
	cin >> n;

	map<int,int> m;
	m[0] = 0;

	int limit = 0;
	rep(i,n){
		int x;
		cin >> x;

		if(limit < x){
			putMedal(limit, m, x);
			cout << "Yes" << endl;
		}else{
			cout << "No" << endl;
		}
	}

}
