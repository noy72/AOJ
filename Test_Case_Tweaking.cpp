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

const int INF = 1e8;
const int MAX_V = 105;

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

void changeCost(int m[MAX_V][MAX_V], int n, int a, int b){
	m[a][b] = m[b][a] = 0;
	rep(i,n){
		rep(j,n){
			m[i][j] = min(m[i][j], m[i][a] + m[b][j]);
		}
	}
}

int ans;
bool C(int n, int C, int mid, int m[MAX_V][MAX_V], vector<pair<int,pair<int, int>>>& p){
	int c[MAX_V][MAX_V];
	memcpy(c, m, sizeof(m[0]) * MAX_V);

	rep(i,mid + 1){
		auto e = p[i].second;
		c[e.first][e.second] = c[e.second][e.first] = 0;
	}

	warshallFloyd(c, n);
	int minCost = c[0][n - 1];
	cout << mid << endl;
	show(minCost)
	if(minCost > C) return false;

	int cnt = 0;
	rep(i,mid){
		auto e = p[i].second;
		if(c[0][e.first] + c[e.second][n - 1] == minCost){
			cnt++;
		}
	}
	ans = cnt;

	return true;
}

int main(){
	int n, m, c;
	while(cin >> n >> m >> c, n){
		int m[MAX_V][MAX_V];
		init(m);

		vector<pair<int,pair<int, int>>> p(n);
		rep(i,n){
			int a, b, cost;
			cin >> a >> b >> cost;
			a--; b--;
			m[a][b] = m[b][a] = cost;
			p[i] = make_pair(cost, make_pair(a,b));
		}
		sort(all(p), greater<pair<int,pair<int, int>>>());

		int ans = 1e9;
		warshallFloyd(m,n);

		rep(i,n){
			changeCost(m, n, p[i].second.first, p[i].second.second);
			show(m[0][n - 1])
			if(m[0][n - 1] <= c){
				int cnt = 0;
				rep(j,i + 1){
					auto e = p[j].second;
					if(m[0][e.first] + m[e.second][n - 1] == m[0][n - 1]){
						cnt++;
					}
				}
				ans = min(ans, cnt);
			}
		}
		cout << ans << endl;
	}

}
