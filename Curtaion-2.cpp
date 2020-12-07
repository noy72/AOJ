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

template <typename T>
class CompressCoordinate{
public:
	vector<T> a, c; // 圧縮した数列、ソートした数列
	CompressCoordinate(const vector<T>& arg){
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


const int dy[16] = { 0,-1, 0, 1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};
const int dy_[16] = { 0, 1, 0, 1};
const int dx_[16] = { 0, 0, 1, 1};

void dfs(int y, int x, vector<vector<int>>& m){
	m[y][x] = -1;
	rep(i,4){
		int ny = y + dy[i];
		int nx = x + dx[i];
		if(ny < 0 || ny >= 200 || nx < 0 || nx >= 200) continue;
		if(m[ny][nx] != 0) continue;
		dfs(ny, nx, m);
	}
}

vector<vector<int>> getGrid(CompressCoordinate<long long>& cx, CompressCoordinate<long long>& cy, vector<long long>& x, vector<long long>& y){
	vector<vector<int>> m(200, vector<int>(200, 0));
	int n = x.size();
	rep(i,n){
		pair<int, int> a = make_pair(cx.map(x[i]), cy.map(y[i]));
		pair<int, int> b = make_pair(cx.map(x[(i + 1) % n]), cy.map(y[(i + 1) % n]));
		if(a > b) swap(a,b);
		assert(a < b);

		//cout << a.first << ' ' << a.second << endl;
		//cout << b.first << ' ' << b.second << endl;
		//cout << endl;
		while(a != b){
			m[a.second + 1][a.first + 1] = 1;
			if(a.first == b.first) a.second++;
			else a.first++;
		}
		m[a.second + 1][a.first + 1] = 1;
	}

	dfs(0,0,m);

	vector<pair<int, int>> d;
	rep(i,200 - 1){
		rep(j,200 - 1){
			if(m[i + 1][j + 1] == 0) m[i + 1][j + 1] = 1;
		}
	}

	vector<vector<int>> res(200, vector<int>(200, 0));
	rep(i,190){
		rep(j,190){
			bool f = true;
			rep(k,4){
				if(m[i + dy_[k]][j + dx_[k]] != 1) f = false;
			}
			if(f) res[i - 1][j - 1] = 1;
		}
	}
	return res;
}

int main(){
	int n;
	while(cin >> n,n){
		//vector<pair<int, int>> win(n);
		vector<long long> comx(n + 4), comy(n + 4);
		vector<long long> x(n), y(n);
		rep(i,n){
			cin >> x[i] >> y[i];
			comx[i] = x[i];
			comy[i] = y[i];
			//win[i] = make_pair(x[i], y[i]);
		}

		vector<long long> X(4), Y(4);
		rep(i,4){
			cin >> comx[i + n] >> comy[i + n];
			X[i] = comx[i + n];
			Y[i] = comy[i + n];
		}

		CompressCoordinate<long long> cx(comx), cy(comy);

		vector<vector<int>> window = getGrid(cx, cy, x, y), curtain = getGrid(cx, cy, X, Y);
		//cout << endl; rep(i,10){ rep(j,10){ cout << curtain[i][j] << ' '; } cout << endl; }
		//cout << endl; rep(i,10){ rep(j,10){ cout << window[i][j] << ' '; } cout << endl; }
		rep(i,200){
			rep(j,200){
				if(curtain[i][j] == 1) window[i][j]--;
			}
		}

		//cout << endl; rep(i,10){ rep(j,10){ cout << window[i][j] << ' '; } cout << endl; }


		long long ans = 0;
		rep(i,200){
			rep(j,200){
				if(window[i][j] >= 1){
					//cout << (cy.c[i + 1] - cy.c[i]) << ' ' << (cx.c[j  + 1] - cx.c[j]) << endl;
					ans += (cy.c[i + 1] - cy.c[i]) * (cx.c[j + 1] - cx.c[j]);
				}
			}
		}
		cout << ans << endl;
	}
}
