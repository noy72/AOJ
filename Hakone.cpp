#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;


template <typename X, typename T>
auto vectors(X x, T a) {
return vector<T>(x, a);
}

template <typename X, typename Y, typename Z, typename... Zs>
auto vectors(X x, Y y, Z z, Zs... zs) {
auto cont = vectors(y, z, zs...);
return vector<decltype(cont)>(x, cont);
}

int main(){
	int n;
	cin >> n;

	vector<char> v;
	rep(i,n){
		char a;
		cin >> a;
		if(a == '-') continue;
		v.emplace_back(a);
	}

	auto dp = vectors(n,n,0);
	dp[0][0] = 1;
	rep(i,n){

	}
}
