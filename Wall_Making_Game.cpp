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

typedef tuple<int,int,int,int> T;
map<T, int> memo;
int grundy(vector<vector<char>>& m, T t){
	if(memo.count(t)) return memo[t];

	int lx, ly, rx, ry;
	tie(lx, ly, rx, ry) = t;

	set<int> s;
	range(i,ly,ry){
		range(j,lx,rx){
			if(m[i][j] == 'X') continue;
			vector<T> a(4);
			a[0] = T(lx, ly, j, i);
			a[1] = T(j + 1, ly, rx, i);
			a[2] = T(lx, i + 1, j, ry);
			a[3] = T(j + 1, i + 1, rx, ry);

			int x = 0;
			//rep(k,4){
			//		int q,w,e,r;
			//		tie(q,w,e,r) = a[k];
			//		cout << q << w << e << r << endl;
			//}
			//		cout << endl;
			rep(k,4){
				if(get<2>(a[k]) > get<0>(a[k]) and get<3>(a[k]) > get<1>(a[k])){
					x ^= grundy(m, a[k]);
				}
			}
			s.emplace(x);
		}
	}

	int k = 0;
	while(s.count(k)) k++;
	return memo[t] = k;
}

int main(){
	int h, w;
	cin >> h >> w;

	vector<vector<char>> m(h, vector<char>(w));
	rep(i,h){
		rep(j,w){
			cin >> m[i][j];
		}
	}

	cout << (grundy(m, T(0, 0, w, h)) != 0 ? "First" : "Second") << endl;
}
