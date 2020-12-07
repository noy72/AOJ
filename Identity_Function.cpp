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

long long power(long long x, long long n, long long M){ //べき乗 x^n mod M
	long long res = 1;
	if(n > 0){
		res = power(x, n / 2, M);
		if(n % 2 == 0) res = (res * res) % M;
		else res = (((res * res) % M) * x ) % M;
	}
	return res;
}

int main(){
	map<long long, vector<long long>> meo;
	rep(n,400){
		long long a[1000][1000];
		range(i,1,n){
			long long t = i;
			rep(j,100){
				t = power(t, n, n);
				a[i][j] = t;
				//cout << t << ' ';
			}
			//cout << endl;
		}

		rep(j,100){
			bool f = true;
			range(i,1,n){
				if(a[i][j] != i){
					f = false;
					break;
				}
			}
			if(f) {
				meo[j + 1].emplace_back(n);
				//cout << n << ' ' << j + 1 << endl;
				break;;
			}
		}
	}
	for(auto i : meo){
		cout << i.first <<  "   ";
		cout << i.second << endl;
	}
}
