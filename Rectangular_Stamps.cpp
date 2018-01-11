#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

typedef vector<vector<char>> vvc;

int n;
vvc isEnd(4,vector<char>(4));
char c[3] = {'R', 'G', 'B'};
vector<pair<int, int>> stump(20);
void out(vvc v){
	show("out")
	rep(i,4){
		rep(j,4){
			cout << v[i][j];
		}
		cout << endl;
	}
}

vvc pushStump(vvc s, pair<int, int> p, int y, int x){
	char m[16][16];
	char color = '#';
	rep(i,16) rep(j,16) m[i][j] = '.';
	rep(i,4) rep(j,4) m[i + 4][j + 4] = s[i][j];

	range(i,y,y + p.first){
		range(j,x,x + p.second){
			if(m[i][j] != '.' && color == '#') color = m[i][j];
			if(m[i][j] == color || m[i][j] == '.'){
				m[i][j] = '.';
			}else{
				//show("eend")
				//cout << i << ' ' << j << endl;
				return vvc();
			}
		}
	}
	rep(i,4) rep(j,4) s[i][j] = m[i + 4][j + 4];

	return s;
}

set<vvc> pushStumpAll(vvc s, pair<int, int> p){
	set<vvc> res;
	rep(i,16 - p.first){
		rep(j,16 - p.second){
			res.emplace(pushStump(s, p, i, j));
		}
	}
	res.erase(s);
	res.erase(vvc());
	return res;
}


//map<pair<int,int>, int> memo;
map<pair<vvc,int>, int> memo;
int dfs(vvc s, int cnt){
	if(memo.count(make_pair(s,cnt))) return memo[make_pair(s,cnt)];
	if(s == isEnd){
		return 0;
	}
	//out(s);

	int res = INF;
	rep(i,n){
		set<vvc> st = pushStumpAll(s, stump[i]);
		for(auto j : st){
			res = min(res, dfs(j, cnt + 1));
		}
	}

	return memo[make_pair(s,cnt)] = res;
}

int main(){
	cin >> n;
	rep(i,n) cin >> stump[i].first >> stump[i].second;

	vvc in(4,vector<char>(4));
	rep(i,4){
		rep(j,4){
			cin >> in[i][j];
		}
	}

	rep(i,4) rep(j,4) isEnd[i][j] = '.';
	cout << dfs(in, 0) << endl;
}
