#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

typedef pair<pair<int,int>,int> P;

const int gmax_n = 40005;

int par[gmax_n]; //親
int depth[gmax_n];//木の深さ

void init(int n){
	rep(i,n){
		par[i] = i;
		depth[i] = 0;
	}
}

int find(int x){
	if(par[x] == x){
		return x;
	}else {
		return par[x] = find(par[x]);
	}
}

void unite(int x, int y){
	x = find(x);
	y = find(y);
	if(x == y) return;

	if(depth[x] < depth[y]){
		par[x] = y;
	}else{
		par[y] = x;
		if(depth[x] == depth[y]) depth[x]++;
	}
}

bool same(int x, int y){
	return find(x) == find(y);
}

int main(){
	int n, h, w;
	cin >> n >> w >> h;

	vector<pair<int, int>> in(n);
	//vector<P> x(n), y(n);
	rep(i,n){
		int a, b;
		cin >> a >> b;
		in[i] = make_pair(a,b);
		//x[i] = make_pair(make_pair(a,b),i);
		//y[i] = make_pair(make_pair(b,a),i);
	}
	//sort(all(x));
	//sort(all(y));

	init(n);
	rep(i,n){
		//auto xs = lower_bound(all(x), make_pair(make_pair(in[i].first, - 1),-1));
		//for(; xs != x.end() && xs->first.first == in[i].first; xs++){
		//	unite(i, xs->second);
		//}
		//auto ys = lower_bound(all(y), make_pair(make_pair(in[i].second, - 1),-1));
		//for(; ys != y.end() && ys->first.second == in[i].second; ys++){
		//	unite(i, ys->second);
		//}
		rep(j,n){
			if(in[i].first == in[j].first || in[i].second == in[j].second){
				unite(i,j);
			}
		}
	}

	int ans = 0;
	map<int,int> m;
	vector<bool> isEdge(n,0);
	rep(i,n){
		if(in[i].first == 1 || in[i].first == w || in[i].second == 1 || in[i].second == h){
			isEdge[find(i)] = true;
		}
		m[find(i)]++;
	}
	auto f = [&](){
		if(m.size() == 1) return 0;
		rep(i,n){
			if(isEdge[find(i)]) return 0;
		}
		return 1;
	};

	for(auto i : m){
		ans += i.second - 1;
	}
	ans += (m.size() - 1) * 2;
	cout << ans + f() << endl;
}
