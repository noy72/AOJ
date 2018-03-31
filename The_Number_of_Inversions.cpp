#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

const int MAX_N = 200000;

template <typename T>
class BIT{
	private:
		vector<T> bit; //[1, n]
	public:
		BIT(){
			bit = vector<T>(MAX_N + 1, 0);
		}
		T sum(int i){
			assert(1 <= i and i <= MAX_N and "invalid argument");
			T s = 0;
			while(i > 0){
				s += bit[i];
				i -= i & -i;
			}
			return s;
		}

		void add(int i, int x){
			assert(1 <= i and i <= MAX_N and "invalid argument");
			while(i <= MAX_N){
				bit[i] += x;
				//bit[i] = max(bit[i], x);
				i += i & - i;
			}
		}
};

template <typename T>
class compressCoordinate{
	public:
		vector<T> a, c; // 圧縮した数列、ソートした数列
		compressCoordinate(const vector<int>& arg){
			a = vector<T>(arg.size());
			c = arg;
			compress(c);
			rep(i,arg.size()){
				a[i] = lb(c, arg[i]);
			}
		}
		void compress(vector<T> &v) {
			sort(v.begin(), v.end());
			v.erase(unique(v.begin(),v.end()),v.end());
		}
		int lb(const vector<T>& v, T num){
			return lower_bound(all(v), num) - v.begin();
		}
		int map(T a){
			return lb(c, a);
		}
};

int main(){
	BIT<int> bit;
	int n;
	cin >> n;

	vector<int> a(n);
	rep(i,n){
		cin >> a[i];
	}
	compressCoordinate<int> com(a);

	long long cnt = 0;
	rep(i,n){
		int t = com.map(a[i]) + 1;

		cnt += bit.sum(MAX_N) - bit.sum(t);
		bit.add(t,1);
	}
	cout << cnt << endl;
}
