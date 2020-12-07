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
	int n;
	while(cin >> n, n){
		double ww; // weight water
		cin >> ww;

		vector<double> vw(n), wf(n), vf(n), th(n);
		rep(i,n){
			cin >> vw[i] >> wf[i] >> vf[i] >> th[i];
		}

		auto C = [&](double w){
			double res = 0;
			rep(i,n){
				double a = (th[i] - w * vw[i]) / vf[i];
				if(a < 0) res += 0;
				else res += a * wf[i];
			}
			//cout << fixed << setprecision(8)<< w << ' ' << res + w * ww << endl;
			return res + w * ww;
		};


		double right = 1e15, left = 0;
		rep(i,200){
			double llr = (left * 2 + right) / 3;
			double rll = (left + right * 2) / 3;
			if(C(llr) > C(rll)){
				left = llr;
			}else{
				right = rll;
			}
		}

		cout << fixed << setprecision(8)  << C(left) << endl;

	}
}
