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

int dp[2][1 << 20] = {0};

int main(){
    int n, m;
    scanf("%d%d",&n,&m);

    int a[30][30];
    int p[30];
    rep(i,n){
        scanf("%d",&p[i]);
        rep(j,p[i]){
            scanf("%d",&a[i][j]);
            a[i][j]--;
        }
    }

    dp[0][0] = 1;
    rep(i,n){
        memset(dp[(i + 1) % 2], 0, sizeof(dp[(i + 1) % 2]));
        rep(j,p[i]){
            rep(k,1 << m){
                if(not getBit(k,a[i][j])){
                    dp[(i + 1) % 2][setBit(k,a[i][j])] += dp[i % 2][k];
                }
            }
        }
        rep(j,1 << m){
            cout << dp[(i + 1) % 2][j] <<' ';
        }
        cout << endl;
    }

    int sum = 0;
    rep(k, 1 << m){
        sum += dp[n % 2][k];
    }
    cout << sum << endl;
}
