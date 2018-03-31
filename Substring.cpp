#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

class RollingHash {
	public:
		typedef pair<long long,long long> hash_type;
		long long base1, base2;
		long long mod1, mod2;
		vector<long long> hash1, hash2;
		vector<long long> pow1, pow2;

		RollingHash(const string &s) : base1(1009), base2(1007), mod1(1000000007), mod2(1000000009) {
			int n = s.size();

			hash1.assign(n + 1,0);
			hash2.assign(n + 1,0);
			pow1.assign(n + 1,1);
			pow2.assign(n + 1,1);

			rep(i,n){
				hash1[i + 1] = (hash1[i] + s[i]) * base1 % mod1;
				hash2[i + 1] = (hash2[i] + s[i]) * base2 % mod2;
				pow1[i + 1] = pow1[i] * base1 % mod1;
				pow2[i + 1] = pow2[i] * base2 % mod2;
			}
		}

		hash_type get(int l, int r) { // 区間[l,r)のハッシュ値を計算する
			long long t1 = ((hash1[r] - hash1[l] * pow1[r - l]) % mod1 + mod1) % mod1;
			long long t2 = ((hash2[r] - hash2[l] * pow2[r - l]) % mod2 + mod2) % mod2;
			return make_pair(t1, t2);
		}

		hash_type concat(hash_type h1, hash_type h2, int h2_len) {
			return make_pair((h1.first * pow1[h2_len] + h2.first) % mod1, (h1.second * pow2[h2_len] + h2.second) % mod2);
		}
};

int main(){
	int n, m;
	string s;
	cin >> n >> m >> s;

	int l = 0, r = 1;
	vector<pair<int, int>> p(m);
	rep(i,m){
		string t;
		cin >> t;
		if(t[0] == 'R'){
			if(t[1] == '+'){
				r++;
			}else{
				r--;
			}
		}else{
			if(t[1] == '+'){
				l++;
			}else{
				l--;
			}
		}
		p[i] = make_pair(l,r);
	}

	set<RollingHash::hash_type> st;
	RollingHash rh(s);
	for(auto i : p){
		tie(l,r) = i;
		st.emplace(rh.get(l, r));
	}
	cout << st.size() << endl;
}
