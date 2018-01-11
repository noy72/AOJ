#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;


int main(){
	int h, w;
	char m[605][605];
	cin >> h >> w;

	rep(i,h) cin >> m[h - i - 1];
	Grid grid(h,w);
	grid.zoom(m);
	grid.white();
	grid.output();
	vector<Grid::Segment> edges = grid.toEdges();

	int ans = 0;
	set<double> s;
	Vector hol = Vector(1,0);
	rep(i,h){
		rep(j,w){
			Vector vec = Vector(j,i);
			if(s.count(angleOf
		}
	}
}
