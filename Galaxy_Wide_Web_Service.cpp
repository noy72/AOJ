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


int gcd(int x, int y) {
	int r;
	if(x < y) swap(x, y);

	while(y > 0){
		r = x % y;
		x = y;
		y = r;
	}
	return x;
}

int lcm( int m, int n ) {
	// 引数に０がある場合は０を返す
	if ( ( 0 == m ) || ( 0 == n ) ) return 0;
	return ((m / gcd(m, n)) * n); // lcm = m * n / gcd(m,n)
}

int main(){
	int n;
	cin >> n;

	int t = 1;
	for(int i = 24; i >= 1; i--){
		cout << i << ' ' << t << ' ' << lcm(t, i) << endl;
		t = lcm(t,i);
	}
	show(t)

	rep(i,n){

	}
}
