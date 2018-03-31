#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

const int dy[16] = { 0, 1, 0,-1, 1,-1, 1,-1, 0,-2, 0, 2};
const int dx[16] = { 1, 0,-1, 0, 1, 1,-1,-1, 2, 0,-2, 0};
int dir, y, x;
vector<vector<char>> m;
map<int,int> loop;

bool f = false;
int ans;

bool cond(int&, string&);
void expr(int&, string&);

void comm(int& p, string& com){
	if(com[p] == '^'){
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if(m[ny][nx] != '#'){
			x = nx;
			y = ny;
		}
	}else if(com[p] == '>'){
		(dir+=1) %= 4;
	}else if(com[p] == 'v'){
		int d = (dir + 2) % 4;
		int ny = y + dy[d];
		int nx = x + dx[d];
		if(m[ny][nx] != '#'){
			x = nx;
			y = ny;
		}
	}else if(com[p] == '<'){
		dir = (dir - 1 + 4) % 4;
	}else{
		assert(false);
	}

	ans++;
	p++;

	if(m[y][x] == 'g'){
		f = true;
	}
}

bool cond(int& p, string& com){
	bool rev = false;
	if(com[p] == '~'){
		rev = true;
		p++;
	}

	bool res;
	switch (com[p]) {
		case 'N':
			res = dir == 3;
			break;
		case 'E':
			res = dir == 0;
			break;
		case 'S':
			res = dir == 1;
			break;
		case 'W':
			res = dir == 2;
			break;
		case 'C':
			res = m[y + dy[dir]][x + dx[dir]] == '#';
			break;
		case 'T':
			res = true;
			break;
	}
	p++;
	return rev ^ res;
}

void nextEnd(int& p, string& com){
	int cnt = 1;
	while(cnt != 0){
		if(com[p] == '{' or com[p] == '[') cnt++;
		else if(com[p] == '}' or com[p] == ']') cnt--;
		p++;
	}
}

set<tuple<int,int,int,int>> s;
void expr(int& p, string& com){

	while(true){
	//cout << dir << endl;
	//cout << p << ' ' << com[p] << endl;
	//cout << y << ' ' << x << endl;
	////char a;
	//cin >> a;
		tuple<int,int,int,int> tup = tuple<int,int,int,int>(dir, y, x, p);
		if(s.count(tup)){
			f = true;
			return;
		}else{
			s.emplace(tup);
		}

		if(f) return;

		if(com[p] == '}'){
			p = loop[p];
		}else if(com[p] == ']'){
			p++;
		}else if(com[p] == '{' or com[p] == '['){
			p++;
			if(not cond(p, com)){
				nextEnd(p, com);
			}
		}else if(com[p] == '@'){
			break;
		}else if(m[y][x] == 'g'){
			f = true;
			return;
		}else{
			comm(p, com);
		}
	}
}

int main(){
	int h, w;
	cin >> h >> w;

	m = vector<vector<char>>(h, vector<char>(w));
	pair<int, int> s;
	rep(i,h){
		rep(j,w){
			cin >> m[i][j];
			if(m[i][j] == 's'){
				y = i;
				x = j;
			}
		}
	}
	dir = 3;

	string com;
	cin >> com;
	com += '@';

	stack<int> st;
	rep(i,com.size()){
		if(com[i] == '{'){
			st.emplace(i);
		}else if(com[i] == '}'){
			loop[i] = st.top(); st.pop();
		}
	}

	int p = 0;
	expr(p, com);
	if(m[y][x] == 'g') cout << ans << endl;
	else cout << -1 << endl;
}
