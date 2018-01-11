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

const int MAX_N = 100005;
class node{
    public:
        int right, left;
        int right_len, left_len, length;
        node(){
            right = left = INF;
            right_len = left_len = length = 0;
        }
};


class segTree{
    private:
        //セグメントツリーを持つ配列
        int n;
        node dat[4 * MAX_N];

        node connect(node a, node b){
            node ret;
            ret.left = a.left;
            ret.left_len = a.left_len;

            ret.right = b.right;
            ret.right_len = b.right_len;

            int mid = 0;
            if(a.right == b.left && a.right != INF){
                mid = a.right_len + b.left_len;
                if(a.right == a.left) ret.left_len= mid;
                if(b.right == b.left) ret.right_len= mid;
            }
            ret.length = max(mid, max(a.length, b.length));

            //cout << a.left << ' ' << a.right << "  ";
            //cout << b.left << ' ' << b.right << endl;
            //cout << a.left_len << ' ' << a.right_len << "  ";
            //cout << b.left_len << ' ' << b.right_len << endl;
            //show(ret.length)
            return ret;
        }
        node query(int a, int b, int k, int l, int r){
            if(r <= a || b <= l) {
                node res;
                return res;
            }

            //[a,b)が[l,r)を完全に含んでいれば、この節点の値
            if(a <= l && r <= b) return dat[k];
            else{
                //そうでなければ、２つのこの最小値
                node x = query(a, b, k * 2, l, ( l + r) / 2);
                node y = query(a, b, k * 2 + 1, (l + r) / 2, r);
                return connect(x,y);
            }
        }
    public:
        void printSEG(){
            rep(i,n){
                show(i)
            cout << dat[i].left << ' ' << dat[i].right << endl;
            cout << dat[i].left_len << ' ' << dat[i].right_len <<  endl;
            cout << dat[i].length << endl;
            }
        }
        segTree(int n_){
            n = 1;
            while(n < n_) n *= 2;
        }
        void update(int i, int x){
            i += n; //葉の節点
            dat[i].right = dat[i].left = x;
            dat[i].right_len = dat[i].left_len = dat[i].length = 1;

            while(i > 1){ //登りながら更新
                int a = i, b = i^1;
                if(a > b) swap(a,b);
                dat[i / 2] = connect(dat[a], dat[b]);
                i = i / 2;
            }
        }
        //[a, b)の最小値を求める
        node query(int a, int b){
            return query(a,b,1,0,n);
        }
};

void excep(int m){
    rep(i,m){
        scanf("%*d%*d");
        printf("1\n");
    }
}

int main(){
    int n,m;
    while(scanf("%d",&n),n){
        scanf("%d",&m);
        if(n == 1){
            scanf("%*d");
            excep(m);
            continue;
        }
        segTree s(n);
        rep(i,n){
            int x;
            scanf("%d",&x);
            s.update(i,x);
        }
        //s.printSEG();
        rep(i,m){
            int a, b;
            scanf("%d%d",&a,&b);
            node ans = s.query(a - 1,b);
            assert(ans.right_len <= ans.length);
            assert(ans.left_len <= ans.length);
            printf("%d\n",ans.length);
        }
    }
}
