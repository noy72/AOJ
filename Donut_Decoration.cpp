#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

template<typename T>
ostream& operator << (ostream& os, vector<T>& v){
	rep(i,v.size()){ os << v[i] << (i == v.size() - 1 ? "" : " "); } return os;
}
template<typename T>
istream& operator >> (istream& is, vector<T>& v){
	for(T& x: v){ is >> x; } return is;
}

const int INF = 2000000000;
const int sqrtN = 512;

class sqdiv{
	public:
		int N, K;
		vector<int> data;
		vector<bool> lazy_flag;
		vector<pair<int, int>> lazy_update;
		sqdiv(int n){ //バケットサイズの変更
			N = n;
			K = (N + sqrtN - 1) / sqrtN;
			data.assign(K * sqrtN, 0);
			lazy_flag.assign(K, false);
			lazy_update.assign(K, make_pair(0,0));
		}
		void eval(int k){
			if(lazy_flag[k]){
				lazy_flag[k] = false;
				for(int i = k * sqrtN; i < (k + 1) * sqrtN; i++){
					data[i] = data[i] + 1 == lazy_update[k].first ? lazy_update[k].second : INF;
				}
			}
		}
		void update(int x, int y, int a){
			rep(k,K){
				int l = k * sqrtN, r = (k + 1) * sqrtN;
				if(r <= x || y <= l) continue;
				if(x <= l && r <= y){
					if(lazy_flag[k]){
						lazy_update[k].second = lazy_update[k].second + 1 == a ? a : INF;
					}else{
						lazy_flag[k] = true;
						lazy_update[k] = make_pair(a,a);
					}
				}else{
					eval(k);
					for(int i = max(x, l); i < min(y, r); i++){
						data[i] = data[i] + 1 == a ? a : INF;
					}
				}
			}
		}
		int find(int a){
			int k = a / sqrtN;
			eval(k);
			return data[a];
		}
};

int main(){
	int n, k, t;
	cin >> n >> k >> t;

	sqdiv s(n);
	rep(i,t){
		int l, r, x;
		cin >> l >> r >> x;
		l--;
		s.update(l, r, x);
		//cout << s.data << endl;
	}

	int cnt = 0;
	rep(i,n){
		//cout << s.find(i) << ' ';
		if(s.find(i) == k) cnt++;
	}
	//cout << endl;
	cout << cnt << endl;

	/*
	 * 1 -2 3 -4
	 */
}
