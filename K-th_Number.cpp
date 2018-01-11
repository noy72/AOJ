
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
const int INF = 2000000000;
using namespace std;

const int MAX = (1 << 18) - 1;

int n;
int a[100005], as[100005]; //入力配列、入力をソートした配列
vector<int> dat[MAX];

void init(int k, int l, int r){
    if(r - l == 1) dat[k].push_back(a[l]); //現在見ている場所が葉
    else{
        int lch = k * 2 + 1, rch = k * 2 + 2; //子の添字
        init(lch, l, (l + r) / 2);
        init(rch, (l + r) / 2, r);
        dat[k].resize(r - l); //場所を確保する
        merge(all(dat[lch]), all(dat[rch]), dat[k].begin()); //子をマージして親に入れる
    }
}

//[a, b)の最小値を求める
//query(a, b, 0, 0, n)
int query(int a, int b, int k, int l, int r, int mid){
    if(r <= a || b <= l) return 0;

    if(a <= l && r <= b) return upper_bound(all(dat[k]), mid) - dat[k].begin();
    else{
        int lc = query(a, b, k * 2 + 1, l, ( l + r) / 2, mid);
        int rc = query(a, b, k * 2 + 2, (l + r) / 2, r, mid);
        return lc + rc;
    }
}

int main(){
    int q;
    scanf("%d%d", &n, &q);

    rep(i,n) scanf("%d", &a[i]);
    rep(i,n) as[i] = a[i];
    sort(as, as + n);
    init(0,0,n);

    int x, y, k;
    rep(i,q){
        scanf("%d%d%d", &x, &y, &k);

        int right = n - 1, left = -1;
        rep(i,100){
            int  mid = (right + left) / 2;
            if(query(x - 1, y,0,0,n,as[mid]) >= k) right = mid;
            else left = mid;
        }
        printf("%d\n", as[right]);
    }
}
