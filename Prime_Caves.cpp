#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

pair<int, int> dp[2005][2005];

class UlamSpiral{
	private:
		const static int MAX_N = 2005;
		const static int kN = 1000005;
		void primeNumber(bool prime[kN]){
			rep(i,kN) prime[i] = 1;
			prime[0] = prime[1] = 0;
			rep(i,kN){
				if(prime[i]){
					for(int j = i + i; j < kN; j+=i){
						prime[j] = 0;
					}
				}
			}
		}

	public:
		int spiral[MAX_N][MAX_N] = {{0}};
		int CENTER;
		bool p[kN] = {0};
		const int dy[4] = { 0,-1, 0, 1}; //反時計回り
		const int dx[4] = { 1, 0,-1, 0};
		UlamSpiral(int n){ //自然数の数
			CENTER = MAX_N / 2;;

			primeNumber(p);

			int x = CENTER, y = CENTER;
			int dir = 0; //右向き
			rep(i,n){
				spiral[y][x] = i + 1;
				x += dx[dir % 4];
				y += dy[dir % 4];

				int nx = x + dx[(dir + 1) % 4];
				int ny = y + dy[(dir + 1) % 4];
				if(spiral[ny][nx] == 0){
					dir++;
				}
			}
		}

		pair<int, int> getPoint(int n){ //数値nがある座標
			rep(i,MAX_N){
				rep(j,MAX_N){
					if(spiral[i][j] == n){
						return make_pair(i,j);
					}
				}
			}
			assert(false);
			return make_pair(-1,-1);
		}

		bool isPrime(int n){
			return p[n];
		}
		bool isPrime(int y, int x){
			if(spiral[y][x] == -1) return 0;
			return p[spiral[y][x]];
		}

		void out(){
			show(CENTER)
			for(int i = CENTER - 11; i < CENTER + 11; i++){
			for(int j = CENTER - 11; j < CENTER + 11; j++){
				//printf("%02d ", spiral[i][j]);
				if(p[spiral[i][j]]){
				printf("%02d ", spiral[i][j]);
				}else{
					cout << "__ ";
				}
			}
			cout << endl;

			}
		}
};

int main(){
	int m,n;
	while(cin >> m >> n, n){
		UlamSpiral ulam(m);
		//ulam.out();

		pair<int, int> s = ulam.getPoint(n);
		rep(i,2000) rep(j,2000) dp[i][j] = make_pair(-1,-1);
		dp[s.first][s.second] = make_pair(0,-1);

		range(i,s.first,2000){
			range(j,1,2000){
				if(dp[i][j].first == -1) continue;
				if(ulam.isPrime(i,j)) {
					dp[i][j] = make_pair(dp[i][j].first + 1, ulam.spiral[i][j]);
				}
				for(int k = -1; k <= 1; k++){
					if(dp[i + 1][j + k].first < dp[i][j].first){
						dp[i + 1][j + k] = dp[i][j];
					}else if(dp[i + 1][j + k].first == dp[i][j].first){
						if(dp[i + 1][j + k].second < dp[i][j].second){
							dp[i + 1][j + k] = dp[i][j];
						}
					}
				}
				
			}
		}

		vector<pair<int, int>> b;
		//cout << s.first << ' ' << s.second << endl;
		rep(i,2000){
			for(int j = 2000; j >= 0; j--){
				if(ulam.spiral[j][i] != 0){
					//show(ulam.spiral[j][i])
					//	show(dp[j][i].first)
					//	show(dp[j][i].second)
					//cout << j << ' ' << i << endl;
					b.emplace_back(j,i);
					break;
				}
			}
		}

		int p = 0;
		rep(i,b.size()){
			//cout << dp[i.first][i.second] << endl;
			if(dp[b[i].first][b[i].second].first > dp[b[p].first][b[p].second].first){
				p = i;
			}else if(dp[b[i].first][b[i].second].first == dp[b[p].first][b[p].second].first && dp[b[i].first][b[i].second].second > dp[b[p].first][b[p].second].second){
				p = i;
			}
		}

		if(dp[b[p].first][b[p].second].first == 0){
			cout << "0 0" << endl;
		}else{
			pair<int, int> pr = dp[b[p].first][b[p].second];
			cout << pr.first << ' ' << pr.second << endl;
		}
	}
}
