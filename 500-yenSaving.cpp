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

const vector<int> coin = {1, 5, 10, 50, 100, 500, 1000};
const vector<int> exchange_ = {5, 2, 5, 2, 5};

vector<int> getCharge(int price){
	int charge = 5000 - price;
	vector<int> res(coin.size(),0);
	res[6] = -5;

	for(int i = coin.size() - 1; i >= 0; i--){
		res[i] += charge / coin[i];
		charge %= coin[i];
	}
	return res;
}

void mergeCharge(vector<int>& charge, vector<int>& wallet){
	rep(i,coin.size()){
		wallet[i] += charge[i];
	}

	rep(i,4){
		wallet[i + 1] += wallet[i] / exchange_[i];
		wallet[i] %= exchange_[i];
	}
	if(charge[5] == 0 and wallet[4] >= 5){
		wallet[4] -= 5;
		wallet[5]++;
	}
}

int getTotalPrice(int y1, int y5, int y10, int y50, int y100, int y1000){
	int res = (500 - y1000) * 1000;
	res -= y1 + y5 * 5 + y10 * 10 + y50 * 50 + y100 * 100;
	return res;
}

int dp[5][2][5][2][501][501];
int nxt[5][2][5][2][501][501];

int main(){
	int n;
	while(cin >> n, n){
		vector<int> p(n);
		rep(i,n){
			cin >> p[i];
		}

		vector<vector<int>> charge(n);
		rep(i,n){
			charge[i] = getCharge(p[i]);
			//cout << charge[i] << endl;
		}

		memset(dp, -1, sizeof(dp));
		memset(nxt, -1, sizeof(nxt));

		dp[0][0][0][0][0][500] = 0;
		rep(i,n){
			rep(y1,5) rep(y5,2) rep(y10,5) rep(y50,2) rep(y100,501) for(int y1000 = 500; y1000 >= 5; y1000--) {
				if(dp[y1][y5][y10][y50][y100][y1000] == -1) continue;

				nxt[y1][y5][y10][y50][y100][y1000] = max(
						nxt[y1][y5][y10][y50][y100][y1000],
						dp[y1][y5][y10][y50][y100][y1000]);

				vector<int> w = {y1, y5, y10, y50, y100, dp[y1][y5][y10][y50][y100][y1000], y1000};
				mergeCharge(charge[i], w);
				nxt[w[0]][w[1]][w[2]][w[3]][w[4]][w[6]] = max(nxt[w[0]][w[1]][w[2]][w[3]][w[4]][w[6]], w[5]);
				//cout << w << endl;
			}
			memcpy(dp, nxt, sizeof(nxt));
			memset(nxt, -1, sizeof(nxt));
		}

		int y500 = 0, pay = 1e9;
		rep(y1,5) rep(y5,2) rep(y10,5) rep(y50,2) rep(y100,5) for(int y1000 = 500; y1000 >= 5; y1000--) {
			int c = dp[y1][y5][y10][y50][y100][y1000];
			int t = getTotalPrice(y1, y5, y10, y50, y100, y1000);
			if(y500 < c){ 
				y500 = c;
				pay = t;
			}else if(y500 == c and pay > t){
				pay = t;
			}
		}
		cout << y500 << ' ' << pay - y500 * 500 << endl;
	}
}
