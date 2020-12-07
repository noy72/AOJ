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

struct Data{
	int t, c, sum;
	Data(int t, int c, int sum = 0) : t(t), c(c), sum(sum) { }
	bool operator < ( const Data &right ) const {
		return t < right.t;
	}
};

void returnLane(int time, queue<Data>& a, queue<Data>& b){
	vector<Data> nextLane;
	while(not a.empty() and time >= a.front().t + a.front().sum){
		auto p = a.front(); a.pop();
		p.c--;
		p.sum = time;
		if(p.c == 0) continue;
		nextLane.emplace_back(p);
	}
	sort(all(nextLane));
	for(auto i : nextLane) b.emplace(i);
}

int main(){
	int n;
	while(cin >> n,n){
		vector<pair<int, int>> a(n);
		rep(i,n){
			cin >> a[i].first >> a[i].second;
			a[i].second *= 2;
		}

		queue<Data> lane1, lane2;

		vector<pair<int, int>> tmp(all(a));
		sort(all(tmp));
		for(auto i : tmp) lane1.emplace(i.first, i.second, 0);

		int ans = 0;
		while(not lane1.empty() or not lane2.empty()){
			ans++;
			returnLane(ans, lane1, lane2);
			returnLane(ans, lane2, lane1);
		}
		cout << ans << endl;
	}
}
