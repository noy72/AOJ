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


const int INF = 1e8;
int levenshteinDistance(string& s, string& t){
	vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, INF));
	rep(i, s.size() + 1) dp[i][0] = i;
	rep(i, t.size() + 1) dp[0][i] = i;

	range(i,1,s.size() + 1){
		range(j,1,t.size() + 1){
			int cost = s[i - 1] == t[j - 1] ? 0 : 1;
			dp[i][j] = min({
					dp[i - 1][j] + 1,			// Insertion
					dp[i][j - 1] + 1,			// Deletion
					dp[i - 1][j - 1] + cost});	// Replace
		}
	}
	return dp[s.size()][t.size()];
}

void check(set<pair<int,int>>& ans, vector<string>& s, int d, string& t, int i, int j, int cnt){
	if(levenshteinDistance(t, s[j]) + cnt <= d){
		if(t < s[j]) ans.emplace(i, j);
		else ans.emplace(j,i);
	}
}

void ansEmplace(set<pair<int, int>>& ans, vector<string>& s, int i, int j){
	if(s[i] < s[j]) ans.emplace(i,j);
	else ans.emplace(j,i);
}

int main(){
	int n;
	while(cin >> n, n){
		int d;
		cin >> d;

		vector<string> s(n);
		rep(i,n){
			cin >> s[i];
		}

		set<pair<int,int>> ans;

		// swap回数が0のとき
		rep(i,n){
			range(j,i + 1,n){
				if(levenshteinDistance(s[i], s[j]) <= d){
					ansEmplace(ans, s, i, j);
				}
			}
		}

		// swap回数が1のとき
		if(d >= 1){
			rep(i,n){
				vector<string> ss;
				rep(j, s[i].size() - 1){
					string t = s[i];
					swap(t[j], t[j + 1]);
					ss.emplace_back(t);
				}

				rep(j,ss.size()){
					range(k,i + 1,n){
						if(levenshteinDistance(ss[j], s[k]) <= d - 1){
							ansEmplace(ans, s, i, k);
						}
					}
				}
			}
		}

		// swap回数が2のとき
		if(d >= 2){
			rep(i,n){
				rep(j,s[i].size()){
					rep(k,s[i].size()){
						string t = s[i];
						swap(t[j], t[j + 1]);
						swap(t[k], t[k + 1]);

						range(l,i + 1,n){
							if(t == s[l]){
								ansEmplace(ans, s, i, l);
							}
						}
					}
				}
			}
		}

		// 削除を一回行ってからswapしたとき
		if(d >= 2){
			rep(i,n){
				vector<string> ss;
				rep(j, s[i].size()){
					string t = s[i];
					t.erase(next(t.begin(),j));

					rep(k,t.size() - 1){
						string tt = t;
						swap(tt[j], tt[j + 1]);
						ss.emplace_back(tt);
					}
				}

				rep(j,ss.size()){
					range(k,i + 1,n){
						if(ss[j] == s[k]){
							ansEmplace(ans, s, i, k);
						}
					}
				}
			}
		}

		vector<pair<string,string>> v;

		for(auto p : ans){
			v.emplace_back(s[p.first],s[p.second]);
		}
		sort(all(v));
		for(auto p : v){
			cout << p.first << ',' << p.second << endl;
		}
		cout << v.size() << endl;
	}
}
