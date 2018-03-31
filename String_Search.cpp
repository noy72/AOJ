#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

class KnuthMorrisPratt{
	public:
		vector<int> fail;
		string t; // 探す文字列
		KnuthMorrisPratt(string& t) {
			this->t = t;
			int m = t.size();
			fail = vector<int>(m + 1);
			int j = fail[0] = -1;
			for (int i = 1; i <= m; ++i) {
				while (j >= 0 && t[j] != t[i - 1]) j = fail[j];
				fail[i] = ++j;
			}
		}
		vector<int> match(string& s){ // s に含まれる連続する部分文字列 t のインデックスを返す
			int n = s.size(), m = t.size();
			vector<int> res;
			for (int i = 0, k = 0; i < n; ++i) {
				while (k >= 0 && t[k] != s[i]) k = fail[k];
				if (++k >= m) {
					res.emplace_back(i - m + 1); // match at s[i-m+1 .. i]
					k = fail[k];
				}
			}
			return res;
		}
};

int main(){
	string s, t;
	cin >> s >> t;
	KnuthMorrisPratt kmp(t);
	for(auto i : kmp.match(s)){
		cout << i << endl;
	}
}
