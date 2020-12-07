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



vector<int> getSeq(int N, int S, int W){
	int g = S;
	vector<int> a(N);
	map<int,int> m;
	for(int i=0; i<N; i++) {
		if(m.count(g)) {
			cout << m[g] << ' ' << i << endl;
			return a;
		}else{
			m[g] = i;
		}
		a[i] = (g/7) % 10;
		if( g%2 == 0 ) { g = (g/2); }
		else           { g = (g/2) ^ W; }
	}
	return a;
}

int main(){
	int n, s, w, q;
	while(cin >> n >> s >> w >> q, n){
		vector<int> a = getSeq(n, s, w);
		show("JI")
	}
}
