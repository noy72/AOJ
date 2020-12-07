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


class RollingHash {
public:
	typedef pair<long long,long long> hash_type;
	long long base1, base2;
	long long mod1, mod2;
	vector<long long> hash1, hash2;
	vector<long long> pow1, pow2;

	RollingHash() {}
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

RollingHash::hash_type getHash(string& s, int type){
	RollingHash hash(s);
	if(type == 0) return hash.get(1,s.size());
	if(type == 1) return hash.get(0,s.size() - 1);
	return hash.get(0,s.size());
}

int containQuest(const string& s){
	rep(i,s.size()){
		if(s[i] == '?') return i;
	}
	return -1;
}


void serarch(vector<int>& ans, map<RollingHash::hash_type, int >& h, string& s, int type, int idx){
	int p = containQuest(s);
	if(p == -1){
		ans[idx] += h[getHash(s, type)];
	}else{
		for (char i = 'a'; i <= 'z'; i++) {
			s[p] = i;
			ans[idx] += h[getHash(s, type)];
		}
		s[p] = '?';
	}
}

int main(){
	int n, m;
	cin >> n >> m;

	vector<RollingHash> hash(n);
	vector<int> size(n), ans(m,0);
	rep(i,n){
		string s;
		cin >> s;
		hash[i] = RollingHash(s);
		size[i] = s.size();
	}

	vector<string> query(m);
	rep(i,m){
		cin >> query[i];
	}

	range(len,1,201){
		map<RollingHash::hash_type, int> h, rh, kh;
		rep(i,n){
			if(size[i] < len) continue;
			if(len == size[i]) kh[ hash[i].get(0,len) ]++;
			h[ hash[i].get(0,len) ]++;
			rh[ hash[i].get(size[i] - len, size[i]) ]++;
		}

		rep(i,m){
			string& s = query[i];
			if(s.front() == '*'){
				if(s.size() - 1 != len) continue;
				serarch(ans, rh, s, 0, i);
			}else if(s.back() == '*'){
				if(s.size() - 1 != len) continue;
				serarch(ans, h, s, 1, i);
			}else{
				if(s.size() != len) continue;
				serarch(ans, kh, s, 2, i);
			}
		}
	}

	for(auto i : ans) cout << i << endl;
	return 0;
}
