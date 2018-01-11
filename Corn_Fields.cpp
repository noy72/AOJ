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
const int INF = 100000000;
using namespace std;

const int M = 1000000000;
int dp[2][1 << 13];
int a[13][13];
int n,m;

bool check(int x, int y, int i){
    if(y & y << 1) return 1;
    if(x & y) return 1;
    rep(j,n){ if(y >> j & 1 && a[i][n - j - 1] == 0) return 1; }
    return 0;
}

int main(){
    scanf("%d%d",&m,&n);

    rep(i,m) rep(j,n) scanf("%d",&a[i][j]);

    int *cur = dp[0], *next = dp[1];
    cur[0] = 1;
    rep(i,m){
        rep(k,1 << n){
            rep(j,1 << n){
                if(check(j,k,i)) continue;
                //cout << k << ' ' << j << endl;
                next[k] = (next[k] + cur[j] % M) % M;
            }
        }
        rep(j,1 << n) cur[j] = 0;
        swap(cur, next);
    }

    long long sum = 0;
    rep(i,1 << n){
        sum += cur[i];
        sum %= M;
    }
    cout << sum << endl;
}
