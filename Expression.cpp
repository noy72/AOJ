#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

int cul(int a, int b, int op){
	switch (op) {
		case 0:
			return a + b;
		case 1:
			return a - b;
		case 2:
			return a * b;
	}
	return -1;
}

const char op[] = {'+', '-', '*'};

int main(){
	vector<int> a(4);
	auto f = [&](){
		rep(i,3){
			rep(j,3){
				rep(k,3){
					do{
						if(cul(cul(cul(a[0],a[1],i),a[2],j),a[3],k) == 10){
							printf("(((%d %c %d) %c %d) %c %d)\n", a[0], op[i], a[1], op[j], a[2], op[k], a[3]);
							return;
						}
					}while(next_permutation(all(a)));
					do{
						if(cul(cul(a[0],a[1],i),cul(a[2],a[3],j),k) == 10){
							printf("((%d %c %d) %c (%d %c %d))\n", a[0], op[i], a[1], op[k], a[2], op[j], a[3]);
							return;
						}
					}while(next_permutation(all(a)));
				}
			}
		}
		cout << 0 << endl;
		return;
	};
	while(cin >> a[0] >> a[1] >> a[2] >> a[3], a[0]){
		f();
	}
}
