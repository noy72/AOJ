#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

int main(){
	string s;
	while(cin >> s){
		int mini[205][205];
		int maxi[205][205];
		rep(i,205) rep(j,205){
			mini[i][j] = INF;
			maxi[i][j] = -INF;
		}

		rep(i,s.size()){
			if(isdigit(s[i])){
				mini[i][i + 1] = maxi[i][i + 1] = s[i] - '0';
			}
		}

		range(w,3,s.size() + 1){
			rep(i,s.size() + 1 - w){
				int j = i + w;

				if(w > 3){
					if(s[i] == '('){
						maxi[i][j] = max(maxi[i][j], maxi[i + 1][j]);
						mini[i][j] = min(mini[i][j], mini[i + 1][j]);
						continue;
					}else if(s[j - 1] == ')'){
						maxi[i][j] = max(maxi[i][j], maxi[i][j - 1]);
						mini[i][j] = min(mini[i][j], mini[i][j - 1]);
						continue;
					}
				}

				range(k,i + 1,j - 1){
					if(s[k] == '-'){
						maxi[i][j] = max(maxi[i][j], maxi[i][k] - mini[k + 1][j]);
						mini[i][j] = min(mini[i][j], mini[i][k] - maxi[k + 1][j]);
					}else if(s[k] == '+'){
						//cout << i << ' ' << k << endl;
						//cout << maxi[i][k] << ' ' << maxi[i][k + 1] << endl;
						maxi[i][j] = max(maxi[i][j], maxi[i][k] + maxi[k + 1][j]);
						mini[i][j] = min(mini[i][j], mini[i][k] + mini[k + 1][j]);

					}
				}
			}
		}
		//rep(i,s.size() + 1){ rep(j,s.size() + 1){ cout << maxi[i][j] <<  ' '; } cout << endl; }
		cout << maxi[0][s.size()] << endl;
	}
}
