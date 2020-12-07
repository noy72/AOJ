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
	int n = 16;
	int k = 8;
		//0 ~ n - 1 に含まれる、サイズkの部分集合を列挙する
	int comb = (1 << k) - 1;
	int cnt = 0;
	while(comb < (1 << n)){
		int x = comb & -comb, y = comb + x;
		comb = ((comb & ~y) / x >> 1) | y;
		cnt++;
	}
	show(cnt)
}
