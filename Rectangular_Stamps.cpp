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

typedef vector<char> vc;
typedef vector<vc> Pic;

class Bit{
	int bit;
	public:
	Bit() : bit(0) { }
	bool at(int i, int j){
		return ( bit >> (i * 4 + j) ) & 1;
	}
	void set(int i, int j){
		bit |= 1 << (i * 4 + j);
	}
	int get(){
		return bit;
	}
};

const char color[] = {'R', 'G', 'B'};

bool canDelete(Pic& pic, Bit& b, pair<int, int> s, int y, int x, char c){
	bool f = false;
	range(i,y,y + s.first){
		range(j,x,x + s.second){
			if(i < 0 or j < 0 or i >= 4 or j >= 4) continue;
			if(not b.at(i,j)) f = true;
			if(pic[i][j] != c and not b.at(i,j)) return false;
		}
	}
	return f;
}
void output(Bit b){
}

Bit getUpdatedBit(Bit& b, pair<int, int> s, int y, int x){
	Bit res = b;
	range(i,y,y + s.first){
		range(j,x,x + s.second){
			if(i < 0 or j < 0 or i >= 4 or j >= 4) continue;
			res.set(i,j);
		}
	}
	return res;
}

struct P{
	int cnt;
	Bit bit;
	P(int cnt, Bit bit) : cnt(cnt), bit(bit) {}
	bool operator < ( const P &right ) const {
		return cnt < right.cnt;
	}
	bool operator > ( const P &right ) const {
		return cnt > right.cnt;
	}
};

void bfs(vector<pair<int, int>>& stamps, Pic& pic){
	priority_queue<P, vector<P>, greater<P>> q;
	//queue<P> q;
	q.emplace(0, Bit());

	vector<int> dis(1 << 16, 1e9);
	dis[0] = 0;

	while(not q.empty()){
		P tmp = q.top(); q.pop();

		Bit b = tmp.bit;
		int cnt = tmp.cnt;


		//if(dis.at(b.get()) <= cnt) continue;
		//dis[b.get()] = cnt;

		if((1 << 16) - 1 == b.get()){
			cout << cnt << endl;
			return;
		}

		rep(c,3){
			rep(i,stamps.size()){
				range(y, 1 - stamps[i].first, 4){
					range(x, 1 - stamps[i].second, 4){
						if(canDelete(pic, b, stamps[i], y, x, color[c])){
							Bit tmp = getUpdatedBit(b, stamps[i], y, x);
							if(dis.at(tmp.get()) > cnt + 1){
								dis[tmp.get()] = cnt + 1;
								q.emplace(cnt + 1, getUpdatedBit(b, stamps[i], y, x));
							}
						}
					}
				}
			}
		}
	}
}

int main(){
	int n;
	cin >> n;

	vector<pair<int, int>> stamps(n);
	rep(i,n){
		cin >> stamps[i].first >> stamps[i].second;
	}

	Pic pic(4, vc(4));
	rep(i,4) rep(j,4) cin >> pic[i][j];

	bfs(stamps, pic);
}
