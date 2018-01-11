#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;


const int MAX_V = 205;
const int MAX_R = 1005;

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

int main(){
	int N, M;
	while(cin >> N >> M, N||M){
		int gl[MAX_V][MAX_V], gs[MAX_V][MAX_V];
		init(gl);
		init(gs);
		rep(i,M){
			int x, y, t;
			char sl;
			cin >> x >> y >> t >> sl;
			x--; y--;
			if(sl == 'L'){
				gl[x][y] = min(t, gl[x][y]);
				gl[y][x] = gl[x][y];
			}else{
				gs[x][y] = min(t, gs[x][y]);
				gs[y][x] = gs[x][y];
			}
		}
		warshallFloyd(gl,N);
		warshallFloyd(gs,N);

		int R;
		cin >> R;
		vector<int> z(R);
		rep(i,R){
			cin >> z[i];
			z[i]--;
		}

		int dp[MAX_R][MAX_V];
		rep(i,MAX_R) rep(j,MAX_V) dp[i][j] = INF;
		dp[0][z[0]] = 0;

		rep(i,R - 1){

			int cur = z[i];
			int next = z[i + 1];
			rep(j,N) dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + gl[cur][next]);
			rep(j,N){
				if(dp[i][j] == INF) continue;
				rep(k,N){
					dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + gl[cur][j] + gs[j][k] + gl[k][next]);
					//cout << i << ' ' << j << ' ' << k << endl;
							//show(dp[i][j] + gl[cur][j] + gs[j][k] + gl[k][next]);
				}

			}
		}

		//rep(i,R){
		//	rep(j,N){
		//		if(dp[i][j] >= INF) cout << "_";
		//		else cout << dp[i][j] << ' ';
		//	}
		//	cout << endl;
		//}

		int mini = INT_MAX;
		rep(i,N){
			mini = min(mini, dp[R - 1][i]);
		}
		cout << mini << endl;
	}
}
