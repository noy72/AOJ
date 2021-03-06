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

map<char,int> m;

string toString(int a){
	string s;
	while(a != 0){
		s += '0' + a % 2;
		a/=2;
	}
	while(s.size() < 6) s+=('0');
	reverse(all(s));
	return s;
}

vector<string> getPicture(int h, int w){
	vector<string> res(h);
	rep(i,h){
		rep(j,(w + 5) / 6){
			char c;
			cin >> c;

			string s = toString(m[c]);
			rep(k,s.size()){
				if(res[i].size() == w) break;
				res[i]+=s[k];
			}
		}
	}
	return res;
}

const int MAX = 5;

int encode(char c){
	if(isdigit(c)){
		return  c - '0';
	}

	assert(false && "invalid string");
}

struct Node{
	int nxt[MAX+1];			// 次のalphabeteのノード番号
	int exist;				// 子ども以下に存在する文字列の数の合計
	vector<int> accept;		// その文字列id
	Node() : exist(0){memset(nxt, -1, sizeof(nxt));}
};

class Trie{
	private:
		void updateDirect(int node,int id){
			ac.emplace_back(node);
			nodes[node].accept.emplace_back(id);
		}
		void updateChild(int node,int child,int id){
			++nodes[node].exist;
		}
		void add(const string &str,int str_index,int node_index,int id){
			if(str_index == str.size())
				updateDirect(node_index, id);
			else{
				const int c = encode(str[str_index]);
				if(nodes[node_index].nxt[c] == -1) {
					nodes[node_index].nxt[c] = (int) nodes.size();
					nodes.emplace_back(Node());
				}
				add(str, str_index + 1, nodes[node_index].nxt[c], id);
				updateChild(node_index, nodes[node_index].nxt[c], id);
			}
		}
		void add(const string &str,int id){add(str, 0, 0, id);}
	public:
		vector<Node>nodes;
		vector<int> ac; // ac[i] := i番目のパターンを受理する状態番号
		int root;
		Trie() : root(0){nodes.emplace_back(Node());}
		void add(const string &str){add(str, nodes[0].exist);}
		int size(){return (nodes[0].exist);}
		int nodesize(){return ((int) nodes.size());}
};

class AhoCorasick : public Trie{
	public: 
		static const int FAIL = MAX;
		vector<int> correct;
		AhoCorasick() : Trie() {}

		void build(){
			correct.resize(nodes.size());
			rep(i,nodes.size())correct[i]=(int)nodes[i].accept.size();

			queue<int> que;
			rep(i,MAX+1){
				if(~nodes[0].nxt[i]) {
					nodes[nodes[0].nxt[i]].nxt[FAIL] = 0;
					que.emplace(nodes[0].nxt[i]);
				}else nodes[0].nxt[i] = 0;
			}
			while(!que.empty()) {
				Node now = nodes[que.front()];
				correct[que.front()] += correct[now.nxt[FAIL]];
				que.pop();
				rep(i,MAX){
					if(now.nxt[i] == -1) continue;
					int fail = now.nxt[FAIL];
					while(nodes[fail].nxt[i] == -1) {
						fail = nodes[fail].nxt[FAIL];
					}
					nodes[now.nxt[i]].nxt[FAIL] = nodes[fail].nxt[i];

					auto &u = nodes[now.nxt[i]].accept;
					auto &v = nodes[nodes[fail].nxt[i]].accept;
					vector<int> accept;
					set_union(all(u),all(v),back_inserter(accept));
					u=accept;
					que.emplace(now.nxt[i]);
				}
			}
		}
		// result := 各パターンがそれぞれ何度マッチしたか
		int match(const string &str,vector<int> &result,int now=0){
			result.assign(size(),0);
			int count=0;
			for(auto &c:str) {
				while(nodes[now].nxt[encode(c)]==-1)now=nodes[now].nxt[FAIL];
				now = nodes[now].nxt[encode(c)];
				count += correct[now];
				for(auto &v:nodes[now].accept)result[v]++;
			}
			return count;
		}
		int next(int now,char c){
			while(nodes[now].nxt[encode(c)]==-1)now=nodes[now].nxt[FAIL];
			return nodes[now].nxt[encode(c)];
		}
};

class KnuthMorrisPratt{
	public:
		vector<int> fail;
		string t; // 探す文字列
		KnuthMorrisPratt(string& t) {
			this->t = t;
			int m = t.size();
			fail = vector<int>(m + 1);
			int j = fail[0] = -1;
			for (int i = 1; i <= m; ++i) {
				while (j >= 0 && t[j] != t[i - 1]) j = fail[j];
				fail[i] = ++j;
			}
		}
		vector<int> match(string& s){ // s に含まれる連続する部分文字列 t のインデックスを返す
			int n = s.size(), m = t.size();
			vector<int> res;
			for (int i = 0, k = 0; i < n; ++i) {
				while (k >= 0 && t[k] != s[i]) k = fail[k];
				if (++k >= m) {
					res.emplace_back(i - m + 1); // match at s[i-m+1 .. i]
					k = fail[k];
				}
			}
			return res;
		}
};

// tに一致するsの部分集合の左上の座標を返す
// O(N + |A|M) N:=総文字数 M:=パターンの文字数 |A|:=アルファベット+数字集合のサイズ
vector<pair<int, int>> BakerBird(vector<string>& s, vector<string>& t){
	AhoCorasick aho;
	for(auto str : t) aho.add(str);
	aho.build();

	vector<vector<int>> status(s.size(), vector<int>(s[0].size()));
	rep(i,s.size()){
		int now = 0;
		rep(j,s[0].size()){
			now = aho.next(now, s[i][j]);
			status[i][j] = now;
		}
	}

	string patern;
	rep(i,aho.ac.size()){
		patern += aho.ac[i] + '0';
	}

	vector<pair<int, int>> res;
	KnuthMorrisPratt kmp(patern);
	range(i,t[0].size() - 1, s[0].size()){
		string sstr; // statusを縦に見た文字列
		rep(j,s.size()){
			sstr += status[j][i] + '0';
		}
		for(auto y : kmp.match(sstr)){
			res.emplace_back(y, i - t[0].size() + 1);
		}
	}
	sort(all(res));
	return res;
}

vector<string> rotate(vector<string>& s){
	vector<string> res(s.size());
	rep(j,s.size()){
		for(int i = s.size() - 1; i >= 0; i--){
			res[j]+=s[i][j];
		}
	}
	return res;
}

vector<string> rev(vector<string> s){
	rep(i,s.size()){
		reverse(all(s[i]));
	}
	return s;
}

int main(){
	for(char i = 'A'; i <= 'Z'; i++){
		m[i] = m.size();
	}
	for(char i = 'a'; i <= 'z'; i++){
		m[i] = m.size();
	}
	for(char i = '0'; i <= '9'; i++){
		m[i] = m.size();
	}
	m['+'] = m.size();
	m['-'] = m.size();

	int h, w, p;
	while(cin >> w >> h >> p, w){

		vector<string> image = getPicture(h, w);
		vector<string> pattern = getPicture(p, p);

		//for(auto i : image){ cout << i << endl; } cout << endl;
		//for(auto i : pattern){ cout << i << endl; }

		set<vector<string>> st;
		rep(i,4){
			vector<string> t = rotate(pattern);
			st.emplace(t);
			pattern = t;

			vector<string> rt = rev(t);
			st.emplace(rt);
		}

		int ans = 0;
		for(auto i : st){
			for(auto j : i){ cout << j << endl; }
			ans += BakerBird(image, i).size();
		}
		cout << ans << endl;
	}
}
