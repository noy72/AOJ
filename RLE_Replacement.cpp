#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

struct Data{
	list<char> c;
	list<char>::iterator it_c;
	list<int> n;
	list<int>::iterator it_n;
	Data(){
		it_c = c.begin();
		it_n = n.begin();
	}
	void next(){
		it_c++;
		it_n++;
	}
	void reset(){
		it_c = c.begin();
		it_n = n.begin();
	}
};

void parser(Data& a){
	char chr;
	int num;
	while(cin >> chr, chr != '$'){
		cin >> num;
		a.c.emplace_back(chr);
		a.n.emplace_back(num);
	}
}

int main(){
	Data a, b, c;
	parser(a);
	parser(b);
	parser(c);

	while(true){
		bool f = true;
		auto cpa = a;
		while(b.it_c != b.c.end()){
			if(cpa.it_c == cpa.c.end() or *cpa.it_c != *b.it_c or *cpa.it_n < *b.it_n){
				f = false;
				break;
			}
			cpa.next();
			b.next();
		}

		if(f){
			cpa = a;
			b.reset();
			while(b.it_c != b.c.end()){
			}
		}
	}
}
