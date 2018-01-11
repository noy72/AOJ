
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

const int MAX_N = 1 << 17;
const int DAT_SIZE = (1 << 18) - 1;

//セグメントツリーを持つ配列
long long dat_a[DAT_SIZE], dat_b[DAT_SIZE];

void add(int a, int b, int x, int k, int l, int r){
    if(a <= l && r <= b) dat_a[k] += x;
    else if(l < b && a < r){
        dat_b[k] += (min(b,r) - max(a, l)) * x;
        add(a, b, x, k * 2 + 1, l, (l + r) / 2);
        add(a, b, x, k * 2 + 2, (l + r) / 2, r);
    }
}

long long sum(int a, int b, int k, int l, int r){
    if(b <= l || r <= a){
        return 0;
    }else if(a <= l && r <= b){
        return dat_a[k] * (r - l) + dat_b[k];
    }else{
        long long res = (min(b, r) - max(a, l)) * dat_a[k];
        res += sum(a, b, k * 2 + 1, l, (l + r) / 2);
        res += sum(a, b, k * 2 + 2, (l + r) / 2, r);
        return res;
    }
}

int main(){
    int n, q;
    scanf("%d%d",&n,&q);
    rep(i,n){
        int x;
        scanf("%d", &x);
        add(i, i + 1, x, 0, 0, n);
    }

    rep(i,q){
        char a;
        int b, c, d;
        cin >> a;
        if(a == 'C'){
            scanf("%d%d%d",&b,&c,&d);
            add(b - 1, c, d, 0, 0, n);
        }else{
            scanf("%d%d", &b, &c);
            printf("%lld\n",sum(b - 1, c, 0, 0, n));
        }
    }
}
