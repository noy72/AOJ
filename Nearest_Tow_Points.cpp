#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

template <typename X, typename T>
auto vectors(X x, T a) {
	return vector<T>(x, a);
}

template <typename X, typename Y, typename Z, typename... Zs>
auto vectors(X x, Y y, Z z, Zs... zs) {
	auto cont = vectors(y, z, zs...);
	return vector<decltype(cont)>(x, cont);
}

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

const int dy[16] = { 0, 1, 1};
const int dx[16] = { 1, 0, 1};

int minimumDistance(vector<int>& a, vector<int>& b, vector<pair<int, int>>& p){
	int res = INT_MAX;
	for(auto i : a){
		for(auto j : b){
			int absx = abs(p[i].first - p[j].first);
			int absy = abs(p[i].second - p[j].second);
			res = min(res, absx * absx + absy * absy);
		}
	}
	return res;
}

int minimumDistance(vector<int>& a, vector<pair<int, int>>& p){
	int res = INT_MAX;
	for(auto i : a){
		for(auto j : a){
			if(i == j) continue;
			int absx = abs(p[i].first - p[j].first);
			int absy = abs(p[i].second - p[j].second);
			res = min(res, absx * absx + absy * absy);
		}
	}
	return res;
}

int main(){
	int n;
	cin >> n;

	vector<pair<int, int>> p(n);
	vector<int> x(n), y(n);
	rep(i,n){
		cin >> x[i] >> y[i];
		p[i] = make_pair(x[i], y[i]);
	}

	CompressCoordinate<int> cx(x), cy(y);
	int w = sqrt(cx.c.size()) + 1;
	int h = sqrt(cy.c.size()) + 1;

	auto m = vectors(h, w, vector<int>());
	rep(i,n){
		int a, b;
		tie(a,b) = p[i];
		m[cy.map(b) / h][cx.map(a) / w].emplace_back(i);
	}

	int mini = INT_MAX;
	rep(i,h - 1){
		rep(j,w - 1){
			rep(d,3){
				mini = min(mini, minimumDistance(m[i][j], m[i + dy[d]][j + dx[d]], p));
			}
		}
	}
	rep(i,h){
		rep(j,w){
			mini = min(mini, minimumDistance(m[i][j], p));
		}
	}
	cout << mini << endl;
}
