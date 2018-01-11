#include <assert.h>
#include <algorithm>
#include <complex>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <list>
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
using namespace std;
const int INF = 11000000;

int x[16], y[16];

bool isCovered(int k, int i, int j){
    int rx = max(x[i], x[j]);
    int lx = min(x[i], x[j]);
    int ry = max(y[i], y[j]);
    int ly = min(y[i], y[j]);
    if(lx <= x[k] && x[k] <= rx && ly <= y[k] && y[k] <= ry) return 1;
    else return 0;
}

int main(){
    int n;
    while(scanf("%d",&n), n){
        rep(i,n){
            scanf("%d%d",&x[i],&y[i]); //ビット演算と配列の添字を一致させる
        }

        int k = 0;
        int s[400], cost[400];
        rep(i,n){
            range(j,i + 1,n){
                cost[k] = max(1,abs(x[i] - x[j])) * max(1,abs(y[i] - y[j]));
                int tmp = (1 << i) | (1 << j);
                rep(k,n){
                    if(isCovered(k,i,j)) tmp |= (1 << k);
                }
                s[k++] = tmp;
            }
        }
        int dp[1 << 16];
        rep(i,1 << n) dp[i] = INF;
        dp[0] = 0;
        rep(i,1 << n){
            rep(j,k){
                dp[i | s[j]] = min(dp[i | s[j]], dp[i] + cost[j]);
            }
        }
        cout << dp[(1 << n) - 1] << endl;
    }
}
