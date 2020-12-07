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

template <typename X, typename T>
auto vectors(X x, T a) {
	return vector<T>(x, a);
}

template <typename X, typename Y, typename Z, typename... Zs>
auto vectors(X x, Y y, Z z, Zs... zs) {
	auto cont = vectors(y, z, zs...);
	return vector<decltype(cont)>(x, cont);
}

pair<int, int> max(pair<int, int> a, pair<int, int> b){
	if(a.first > b.first) return a;
	else if(a.first == b.first){
		if(a.second > b.second) return a;
		else return b;
	}else{
		return b;
	}
}

pair<int, int> min(pair<int, int> a, pair<int, int> b){
	if(a.first > b.first) return b;
	else if(a.first == b.first){
		if(a.second > b.second) return b;
		else return a;
	}else{
		return a;
	}
}

int f(int a, int b){
	return (a + b) % 60;
}

vector<vector<int>> ord;
void init(){
	vector<int> tmp = {0,1,2};
	do {
		ord.emplace_back(tmp);
	} while ( next_permutation(all(tmp)) );
}

int main(){
	init();

	int n;
	while(cin >> n,n){
		vector<vector<int>> a(n, vector<int>(3));
		rep(i,n){
			rep(j,3) cin >> a[i][j];
		}

		rep(i,n){
			rep(j,6){
				rep(k,60){

				}
			}
		}
	}
}
