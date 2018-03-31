#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

struct Node{
	int l, r;
	int num;
	Node(){
		l = r = -1;
	}
};

int number(string& s, int& i){
	int res = 0;
	while(isdigit(s[i])){
		res *= 10;
		res += s[i] - '0';
		i++;
	}
	return res;
}

int dfs(vector<Node>& node, string& s, int l, int r, int& idx){
	if(r - l == 0) return -1;

	int cur = idx;

	int cnt = 0, i = l;
	while(true){
		if(s[i] == '(') cnt++;
		else if(s[i] == ')') cnt--;
		else if(cnt == 0){
			idx++;
			node[cur].l = dfs(node, s, l + 1, i - 1, idx);
			i++;
			node[cur].num = number(s, i);
			i++;
			idx++;
			node[cur].r = dfs(node, s, i + 1, r - 1, idx);
			break;
		}
		i++;
	}
	return cur;
}

string merge(vector<Node>& x, int xi, vector<Node>& y, int yi){
	if(xi == -1 or yi == -1) return "";

	string left = merge(x, x[xi].l, y, y[yi].l);
	string num = to_string(x[xi].num + y[yi].num);
	string right = merge(x, x[xi].r, y, y[yi].r);

	return  "(" + left + ")" + "[" + num + "]" + "(" + right + ")";
}

int main(){
    string a,b;
    cin >> a >> b;

	vector<Node> x(10000), y(10000);
	int idx = 0;
	dfs(x, a, 0, a.size(), idx);
	idx = 0;
	dfs(y, b, 0, b.size(), idx);


	string ans = merge(x,0,y,0);
	cout << merge(x, 0, y, 0) << endl;
}
