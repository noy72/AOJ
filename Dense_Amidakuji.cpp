#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

template<typename T>
ostream& operator << (ostream& os, vector<T>& v){
	rep(i,v.size()){ os << v[i] << (i == v.size() - 1 ? "" : " "); } return os;
}
template<typename T>
istream& operator >> (istream& is, vector<T>& v){
	for(T& x: v){ is >> x; } return is;
}

int main(){
	int H, W, n;
	cin >> H >> W >> n;

	vector<int> ans(W);
	for(int i = 0; i < W; i+= 2){
		int h = H + (i % 2);
		int l = i, r = i + 1;
		int left = i, right = W - i - 2;

		if(h > left + 1){
			h -= left + 1;
			h %= W * 2;
			if(h >= 0 and h < W){
				l = h;
			}else{
				l = W * 2 - h - 1;
			}
		}else{
			l -= h;
		}

		h = H + (i % 2);
		if(h > right + 1){
			h -= right + 1;
			h %= W * 2;
			if(h >= 0 and h < W){
				r = W - h - 1;
			}else{
				r = h - W;
			}
		}else{
			r += h;
		}

		ans[i] = l;
		ans[i + 1] = r;
	}
	for(auto& i : ans) i++;

	vector<pair<int, int>> x(n);
	rep(i,n){
		cin >> x[i].first >> x[i].second;
	}
	sort(all(x), greater<pair<int, int>>());

	rep(i,n){
		int a, b;
		tie(a, b) = x[i];
		a--;
		//cout << a << ' ' << b << endl;

		int l = b - 1, r = b;
		int left = b - 1, right = W - b - 1;
		//cout << l << ' ' << r << endl;
		//cout << left << ' ' << right << endl;

		int h = a;
		if(h > left + 1){
			h -= left + 1;
			h %= W * 2;
			if(h >= 0 and h < W){
				l = h;
			}else{
				l = W * 2 - h - 1;
			}
		}else{
			l -= h;
			if(l == -1) l = 0;
		}

		h = a;
		if(h > right + 1){
			h -= right + 1;
			h %= W * 2;
			if(h >= 0 and h < W){
				r = W - h - 1;
			}else{
				r = h - W;
			}
		}else{
			r += h;
			if(r == W) r = W - 1;
		}

		cout << a << ' ' << b << endl;
		cout << l << ' ' << r << endl;
		swap(ans[l], ans[r]);
	cout << ans << endl;
	}
}
