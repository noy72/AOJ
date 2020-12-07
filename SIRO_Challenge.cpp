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

const int INF = 1e8 + 5;
const int MAX_V = 500;

void init(int m[MAX_V][MAX_V]){
	rep(i,MAX_V) rep(j,MAX_V) m[i][j] = INF;
	rep(i,MAX_V) m[i][i] = 0;
}

void warshallFloyd(int m[MAX_V][MAX_V], int n){
	rep(k,n){
		rep(i,n){
			rep(j,n){
				m[i][j] = min(m[i][j], m[i][k] + m[k][j]);
			}
		}
	}
}

//i番目のビットを返す
bool getBit(int num, int i){
	return ((num & (1 << i)) != 0);
}

//i番目を1にする
int setBit(int num, int i){
	return num | (1 << i);
}

//i番目を0にする
int clearBit(int num, int i){
	int mask = ~(1 << i);
	return num & mask;
}

//i番目をvで置き換える
int updateBit(int num, int i, int v){
	int mask = ~(1 << i);
	return (num & mask) | (v << i);
}

int main(){
	int n, m, l, s, t;
	while(cin >> n >> m >> l >> s >> t, n){
		s--;

		int g[MAX_V][MAX_V];
		init(g);
		rep(i,m){
			int a, b, c;
			cin >> a >> b >> c;
			a--; b--;
			g[a][b] = g[b][a] = c;
		}
		warshallFloyd(g, n);

		vector<pair<int, int>> r(l + 1);
		rep(i,l){
			cin >> r[i].first >> r[i].second;
			r[i].first--;
		}
		r[l] = make_pair(s, 0);

		//rep(i,n){ rep(j,n){ cout << g[i][j] << ' '; } cout << endl; }

		l++;
		vector<vector<int>> dp(1 << l, vector<int>(l, INF));
		rep(i,l){
			dp[1 << i][i] = g[s][r[i].first] + r[i].second;
			//dp[1 << i][i] = g[s][r[i].first] + r[i].second;
		}

		//rep(b, 1 << l){ rep(i,l){ cout << dp[b][i] << ' '; } cout << endl; }
		//cout << endl;
		rep(b, 1 << l){
			rep(i,l){
				if(not getBit(b, i)) continue;
				//dp[setBit(b, i)][i] = min(dp[setBit(b, i)][i], dp[b][i] + r[i].second);
				rep(j,l){
					if(getBit(b, j)) continue;
					dp[setBit(b, j)][j] = min(dp[setBit(b, j)][j], dp[b][i] + g[r[i].first][r[j].first] + r[j].second);
				}
			}
		}

		//rep(b, 1 << l){ rep(i,l){ cout << dp[b][i] << ' '; } cout << endl; }

		int ans = 0;
		rep(b, 1 << l){
			if(dp[b][l - 1] <= t) ans = max<int>(ans, bitset<20>(b).count());
			//rep(i,l){
			//	if(dp[b][i] + g[r[i].first][s] <= t) ans = max<int>(ans, bitset<20>(b).count());
			//}
		}
		cout << ans - 1 << endl;
	}
}
