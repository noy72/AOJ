#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int M = 100000;

int main(){
    int n, m, s;
    while(cin >> n >> m >> s,n){
		vector<vector<int>> cur(n * n + 1, vector<int>(s + 1,0));
		cur[0][0] = 1;
		range(i,1,m + 1){
			for (int j = n * n; j > 0; j--) {
				range(k,i,s + 1){
					(cur[j][k] += cur[j - 1][k - i]) %= M;
				}
			}
		}

        cout << cur[n * n][s] << endl;
    }
}
