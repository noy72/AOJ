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

const int MAX_N = 100005;
int n;

class BIT{
    long long bit0[MAX_N], bit1[MAX_N];
    long long bit_sum(long long *b, int i){
        long long s = 0;
        while(i > 0){
            s += b[i];
            i -= i & -i;
        }
        return s;
    }
    long long sum(int a){
        return bit_sum(bit1, a) * a + bit_sum(bit0, a);
    }

    public:
    BIT(){
        memset(bit0, 0, sizeof(bit0));
        memset(bit1, 0, sizeof(bit1));
    }
    void add(bool f, int i, int v){
        while(i <= n){
            if(f) bit1[i] += v;
            else bit0[i] += v;
            i += i & -i;
        }
    }
    void range_add(int l, int r, int x){
        add(0, l, -x * (l - 1));
        add(1, l, x);
        add(0, r + 1, x * r);
        add(1, r + 1, -x);
    }
    long long range_sum(int l, int r){
        return sum(r) - sum(l);
    }
};

void compress(vector<int> &v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
}

int lb(vector<int> v, int num){
    return lower_bound(all(v), num) - v.begin();
}

void compressCoordinate(vector<int> g[MAX_N], vector<int> x, vector<int> y, int p[MAX_N][2]){
    rep(i,n){
        int fx = lb(x, p[i][0]);
        int fy = lb(y, p[i][1]);
        g[fy].emplace_back(fx);
    }
}

int main(){
    scanf("%d",&n);

    vector<int> x(n), y(n), g[MAX_N];
    int p[MAX_N][2];
    rep(i,n){
        scanf("%d%d", &p[i][0], &p[i][1]);
        x[i] = p[i][0];
        y[i] = p[i][1];
    }

    compress(x);
    compress(y);
    compressCoordinate(g,x,y,p);

    int covered[MAX_N] = {0};
    long long ans = n;

    BIT bit;
    rep(i,y.size()){
        sort(all(g[i]));
        int size = static_cast<int>(g[i].size());

        rep(j,size){
            int x = g[i][j];
            long long s = bit.range_sum(x - 1, x);

            if(covered[x]) ans += s;
            covered[x] = true;
            bit.add(0, x, -s);
            if(j + 1 < size){
                if(x + 1 < g[i][j + 1] - 1){
                    bit.range_add(x + 1, g[i][j + 1] - 1, 1);
                }else if(x + 1 == g[i][j + 1] - 1){
                    bit.add(0, x + 1, 1);
                }
            }
        }
    }
    cout << ans << endl;
}
