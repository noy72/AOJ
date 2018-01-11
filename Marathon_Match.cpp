#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cmath>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

const int N = 105;

//n個を選ぶ組み合わせの中、k個を選ぶ組み合わせの割合。
void Pascals(double m[N][N]){
	m[0][0] = 1;
	range(i,1,N){
		rep(j,i + 1){
			if(j == 0) m[i][j] = m[i - 1][j];
			else if(j == i) m[i][j] = m[i - 1][j - 1];
			else m[i][j] = (m[i - 1][j] + m[i - 1][j - 1]);
		}
	}
}

int main(){
	int n, m, l;
	cin >> n >> m >> l;

	vector<double> p(n), t(n), v(n);
	rep(i,n){
		cin >> p[i] >> t[i] >> v[i];
		p[i] /= 100;
	}

	double pas[N][N];
	Pascals(pas);

	double c[N][N] = {{0}};
	rep(i,n){
		rep(j,m + 1){
			double rest_p = 1;
			double run_p = 1;
			for(int k = 0; k < j; k++){
				rest_p *= p[i];
			}
			for(int k = j; k < m; k++){
				run_p *= (1 - p[i]);
			}
			c[i][j] = rest_p * run_p * pas[m][j];
		}
	}


	vector<double> base_time(n);
	rep(i,n) {
		if(v[i] == 0) base_time[i] = INF;
		else base_time[i] = l / v[i];
	}

	rep(i,n){
		double ans = 0;

		rep(j,m + 1){
			double cul = c[i][j];
			if(isnan(cul)) continue;
			double time = base_time[i] + j * t[i];
			rep(k,n){
				if(i == k) continue;

				if(t[k] < 1e-10){
					if(time >= base_time[k]) cul *= 0;
					continue;
				}

				int rest = 0;
				if(time >= base_time[k]){
					rest = (time - base_time[k]) / t[k];
					while(rest * t[k] + base_time[k] <= time) rest++;
				}
				if(rest > m){
					cul *= 0;
					continue;
				}

				double sum = 0;
				range(l,rest,m + 1) sum += c[k][l];
				cul *= sum;
			}
			if(isnan(cul)) continue;
			ans += cul;
		}
		cout << fixed << setprecision(8)<<ans << endl;
	}
}
