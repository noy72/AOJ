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

int main(){
	int d;
	double e;
	while(cin >> d >> e, d||e){
		double mini = 1e9;
		rep(i,d + 1){
			int j = d - i;
			mini = min(mini, abs(hypot(i,j) - e));
		}
		cout << fixed << setprecision(10) << mini << endl;
	}
}
