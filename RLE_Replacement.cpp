#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

#define int long long

struct Data{
	char c;
	int n;
	Data(char c, int n) : c(c), n(n) {}
};

void parser(vector<Data>& a){
	char chr;
	int num;
	while(cin >> chr, chr != '$'){
		cin >> num;
		a.emplace_back(chr, num);
	}
}

vector<Data> a, b, c, ans;

bool canReplace(int idx){
	rep(i,b.size()){
		if(a[i + idx].c != b[i].c) return false;
		if(i == 0 or i == b.size() - 1){
			if(a[i + idx].n < b[i].n) return false;
		}else{
			if(a[i + idx].n != b[i].n) return false;
		}
	}
	return true;
}

signed main(){
	parser(a);
	parser(b);
	parser(c);

	rep(i,static_cast<int>(a.size()) - static_cast<int>(b.size()) + 1){
		if(canReplace(i)){
			rep(j,i) ans.emplace_back(a[j]);

			if(b.size() > 1){
				a[i].n -= b[0].n;
				if(a[i].n > 0) ans.emplace_back(a[i]);
			}
			rep(j,c.size()) ans.emplace_back(c[j]);

			a[i + b.size() - 1].n -= b.back().n;
			if(a[i + b.size() - 1].n > 0) ans.emplace_back(a[i + b.size() - 1]);
			range(j,i + b.size(), a.size()) ans.emplace_back(a[j]);
			break;
		}
	}

	if(ans.empty()) ans = a;

	rep(i,ans.size()){
		if(i + 1 < ans.size() and ans[i + 1].c == ans[i].c){
			ans[i + 1].n += ans[i].n;
		}else{
			cout << ans[i].c << ' ' << ans[i].n << ' ';
		}
	}
	cout << '$' << endl;
}
