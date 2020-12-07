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

vector<vector<int>> ROLE = {
	{2,3,5,4},
	{1,4,5,3},
	{1,2,6,5},
	{1,5,6,2},
	{1,3,6,4},
	{2,4,5,3},
};

enum FACE { TOP, BOTTOM, FRONT, BACK, LEFT, RIGHT };
template <class T>
class Dice {
	private:
		void roll(FACE a, FACE b, FACE c, FACE d) {
			T tmp = id[a];
			id[a] = id[b]; id[b] = id[c];
			id[c] = id[d]; id[d] = tmp;
		}
		T var[6];
		int id[6];
	public:
		Dice() {
			id[TOP] = 0; id[FRONT] = 1; id[LEFT] = 2;
			id[RIGHT] = 3; id[BACK] = 4; id[BOTTOM] = 5;
			rep(i,6) var[i] = id[i];
		}
		Dice(int top, int front){
			id[TOP] = top;
			id[FRONT] = front;
			id[BOTTOM] = 7 - top;
			id[BACK] = 7 - front;

			vector<int> a = {top, front, 7 - top, 7 - front};
			int mini = *min_element(all(a));
			while(a.front() != mini){
				a.emplace_back(a.front());
				a.erase(a.begin());
			}

			rep(i,6){
				if(a == ROLE[i]){
					id[RIGHT] = i + 1;
					id[LEFT] = 7 - id[RIGHT];
				}
			}
			rep(i,6) var[i] = id[i];
		}
		T& operator[] (FACE f) { return var[id[f]]; }
		const T& operator[] (FACE f) const { return var[id[f]]; }
		bool operator == (const Dice<T>& b) const {
			const Dice<T> &a = *this;
			return a[TOP] == b[TOP] && a[BOTTOM] == b[BOTTOM] &&
				a[FRONT] == b[FRONT] && a[BACK] == b[BACK] &&
				a[LEFT] == b[LEFT] && a[RIGHT] == b[RIGHT];
		}
		void roll_x() { roll(TOP, BACK, BOTTOM, FRONT); }
		void roll_y() { roll(TOP, LEFT, BOTTOM, RIGHT); }
		void roll_z() { roll(FRONT, RIGHT, BACK, LEFT); }
		vector<Dice> allRolls() {
			vector<Dice> ret;
			for (int k = 0; k < 6; (k & 1 ? roll_y() : roll_x()), ++k)
				for (int i = 0; i < 4; roll_z(), ++i)
					ret.emplace_back(*this);
			return ret;
		}
		bool equivalentTo(const Dice& di) {
			for (int k = 0; k < 6; (k & 1 ? roll_y() : roll_x()), ++k)
				for (int i = 0; i < 4; roll_z(), ++i)
					if (*this == di) return true;
			return false;
		}
};

vector<Dice<int>> ds = Dice<int>().allRolls();
set<int> ans;

void dfs(int cnt, Dice<int> d[3][3][3]){
	if(cnt == 27){
		int sum = 0;
		rep(i,3){
			rep(j,3){
				sum += d[i][j][2][RIGHT];
			}
		}
		ans.emplace(ans);
		return;
	}

	int i = cnt / 9, j = cnt % 9 / 3, k = cnt % 3;

	rep(d, ds.size()){
		if(i == 0){
			if(j == 0 and k == 0){

			}else if(j == 0){

			}else if(k == 0){

			}else{

			}
		}else{
			if(j == 0 and k == 0){

			}else if(j == 0){

			}else if(k == 0){

			}else{

			}
		}
	}
}

void search(){

}

int main(){
	int n;
	cin >> n;
	while(n--){
		rep(k,2){
			rep(i,3){
				rep(j,3){

				}
			}
		}
	}
}
