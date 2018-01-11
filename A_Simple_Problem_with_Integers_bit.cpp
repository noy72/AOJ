
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

long long bit0[MAX_N], bit1[MAX_N];
int n;

long long sum(long long *b, int i){
    long long s = 0;
    while(i > 0){
        s += b[i];
        i -= i & -i;
    }
    return s;
}

void add(long long *b, int i, int v){
    while(i <= n){
        b[i] += v;
        i += i & -i;
    }
}

int main(){
    int q;
    scanf("%d%d",&n,&q);
    rep(i,n){
        int x;
        scanf("%d", &x);
        add(bit0, i + 1, x);
    }

    rep(i,q){
        char a;
        int l, r, x;
        cin >> a;
        if(a == 'C'){
            scanf("%d%d%d",&l,&r,&x);
            add(bit0, l, -x * (l - 1));
            add(bit1, l, x);
            add(bit0, r + 1, x * r);
            add(bit1, r + 1, -x);
        }else{
            long long res = 0;
            scanf("%d%d", &l, &r);
            res += sum(bit0, r) + sum(bit1, r) * r;
            res -= sum(bit0, l - 1) + sum(bit1, l - 1) * (l - 1);
            printf("%lld\n",res);
        }
    }
}
