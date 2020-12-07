#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
const int INF = 1e8;
using namespace std;

typedef complex<double> Point;
typedef Point Vector;
//線分を表す構造体
struct Segment{ Point p1, p2; };
//直線を表す構造体

namespace std{
	bool operator < (const Point &a, const Point &b){
		return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
	}
	bool operator == (const Point &a, const Point &b){
		return a.real() == b.real() && a.imag() == b.imag();
	}
}

// 許容する誤差
#define EPS (1e-10)

int ccw(Point, Point, Point);

// 内積 (dot product) : a・b = |a||b|cosΘ
double dot(Point a, Point b) {
	return (a.real() * b.real() + a.imag() * b.imag());
}

// 外積 (cross product) : a×b = |a||b|sinΘ
double cross(Point a, Point b) {
	return (a.real() * b.imag() - a.imag() * b.real());
}

// a1,a2を端点とする線分とb1,b2を端点とする線分の交差判定
bool isIntersectedLs(Point a1, Point a2, Point b1, Point b2) {
	return ( ccw(a1, a2, b1) * ccw(a1, a2, b2) <= 0 &&
			ccw(b1, b2, a1) * ccw(b1, b2, a2) <= 0 );
}
bool isIntersectedLs(Segment s1, Segment s2) {
	return isIntersectedLs(s1.p1, s1.p2, s2.p1, s2.p2);
}

//ベクトルの位置検出
static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;

int ccw(Point p0, Point p1, Point p2){
	Vector a = p1 - p0;
	Vector b = p2 - p0;
	if( cross(a, b) > EPS ) return COUNTER_CLOCKWISE;
	if( cross(a, b) < -EPS ) return CLOCKWISE;
	if( dot(a, b) < -EPS ) return ONLINE_BACK;
	if( abs(a) < abs(b) ) return ONLINE_FRONT;

	return ON_SEGMENT;
}


double ga[1000][1000], gb[1000][1000];

const int MAX_V = 1000;
double dijkstra(int n, int s, double g[MAX_V][MAX_V]){
	vector<double> dis(n,INF);
	priority_queue<double, vector<pair<double, int>>, greater<pair<double, int>>> q;

	q.emplace(0,s);
	dis[s] = 0;

	while(not q.empty()){
		int pos;
		double cost;
		tie(cost, pos) = q.top(); q.pop();
		if(pos == 1) break;

		rep(to,n){
			if(dis[to] > cost + g[pos][to]){
				dis[to] = cost + g[pos][to];
				q.emplace(dis[to], to);
			}
		}
	}
	return dis[1];
}

double solve(double g[MAX_V][MAX_V], Segment s, vector<Point>& a){
	int n = a.size();
	rep(i,n){
		rep(j,n){
			if(i == j) continue;
			if(isIntersectedLs(s, Segment{a[i], a[j]})){
				g[i][j] = INF;
			}
		}
	}
	return dijkstra(n, 0, g);
}

void input(vector<Point>& a, int n){
	rep(i,n){
		double x, y;
		cin >> x >> y;
		a[i] = Point(x,y);
	}
}

void culDist(double g[MAX_V][MAX_V], vector<Point>& a, int n){
	rep(i,n) rep(j,n) g[i][j] = abs(a[i] - a[j]);
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);

	int na, nb;
	cin >> na >> nb;

	vector<Point> a(na), b(nb);
	input(a, na);
	input(b, nb);

	culDist(ga, a, na);
	culDist(gb, b, nb);

	double adis = ga[0][1];
	double bdis = gb[0][1];

	double ans = min<double>(
			solve(gb, Segment{a[0], a[1]}, b) + adis,
			solve(ga, Segment{b[0], b[1]}, a) + bdis
			);
	cout << fixed << setprecision(10) << (ans >= INF ? -1 : ans) << endl;
}
