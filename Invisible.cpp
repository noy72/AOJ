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

const int MAX_N = 55;
vector<int> a, b;

pair<int, int> culStack(vector<int>& s){
	int a_score = 0, b_score = 0;
	for(int i = s.size() - 1; i >= 0; i--){
		if(i % 2 == 1 and s[i] == -1) break;
		if(i % 2 == 0 and s[i] >= 0) a_score += s[i];
	}

	for(int i = s.size() - 1; i >= 0; i--){
		if(i % 2 == 0 and s[i] == -1) break;
		if(i % 2 == 1 and s[i] >= 0) b_score += s[i];
	}

	return make_pair(a_score, b_score);
}

int get_point(int turn, int al, int ar, int bl, int br)
{
    int ap = 0, bp = 0;
    bool astop = 0, bstop = 0;
    for (int i = ar-1, j = br-1; i >= al || j >= bl; turn ^= 1) {
        if (turn == 0) {
            if (a[i] == -1) {
                bstop = 1;
            } else if (!astop) {
                ap += a[i];
            }
            i--;
        } else {
            if (b[j] == -1) {
                astop = 1;
            } else if (!bstop) {
                bp += b[j];
            }
            j--;
        }
    }
    return ap - bp;
}

int cul(int t, int as, int bs, int at, int bt){
	return get_point(t, as, at, bs, bt);
	vector<int> s;

	if(at - as > bt - bs){
		rep(i,at - as){
			s.emplace_back(a.at(as));

			if(bs >= b.size()) break;
			s.emplace_back(b.at(bs));
			as++; bs++;
		}
		//cout << s << endl;

		pair<int, int> tmp = culStack(s);
		//show(tmp.first - tmp.second)
		return tmp.first - tmp.second;
	}else{
		rep(i,bt - bs){
			s.emplace_back(b.at(bs));
			
			if(as >= a.size()) break;
			s.emplace_back(a.at(as));
			as++; bs++;
		}
		//cout << s << endl;

		pair<int, int> tmp = culStack(s);
		//show(tmp.second - tmp.first)
		return tmp.second - tmp.first;
	}
}

int memo[MAX_N][MAX_N][MAX_N][MAX_N][2][2];

int dfs(int atop, int btop, int abot, int bbot, bool turn, bool pass){
	auto& p = memo[atop][btop][abot][bbot][turn][pass];
	if(p != 1e9) return p;

	int res;
	if(turn){ // minimize
		res = 1e9;
		if(btop < b.size()){
			res = min(res, dfs(atop, btop + 1, abot, bbot, turn ^ 1, false));
		}
		if(pass){
			res = min(res, 0);
		}else{
			res = min(res, dfs(atop, btop, atop, btop, turn ^ 1, atop == abot and btop == bbot) +
					get_point(turn ^ 1, abot, atop, bbot,  btop));
		}
	}else{ // maximize
		res = -1e9;
		if(atop < a.size()){
			res = max(res, dfs(atop + 1, btop, abot, bbot, turn ^ 1, false));
		}
		if(pass){
			res = max(res, 0);
		}else{
			res = max(res, dfs(atop, btop, atop, btop, turn ^ 1, atop == abot and btop == bbot) +
					get_point(turn ^ 1, abot, atop, bbot, btop));
		}
	}
	return p = res;
}

int main(){
	int n, m;
	cin >> n >> m;

	a = vector<int>(n);
	b = vector<int>(m);
	cin >> a >> b;

	fill(memo[0][0][0][0][0], memo[MAX_N-1][MAX_N-1][MAX_N-1][MAX_N-1][2], 1e9);
	cout << dfs(0, 0, 0, 0, 0, 0) << endl;
}
