#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

template < class BidirectionalIterator >
bool next_combination ( BidirectionalIterator first1 ,
		BidirectionalIterator last1 ,
		BidirectionalIterator first2 ,
		BidirectionalIterator last2 ){
	if (( first1 == last1 ) || ( first2 == last2 )) {
		return false ;
	}
	BidirectionalIterator m1 = last1 ;
	BidirectionalIterator m2 = last2 ; --m2;
	while (--m1 != first1 && !(* m1 < *m2 )){
	}
	bool result = (m1 == first1 ) && !(* first1 < *m2 );
	if (! result ) {
		while ( first2 != m2 && !(* m1 < * first2 )) {
			++ first2 ;
		}
		first1 = m1;
		std :: iter_swap (first1 , first2 );
		++ first1 ;
		++ first2 ;
	}
	if (( first1 != last1 ) && ( first2 != last2 )) {
		m1 = last1 ; m2 = first2 ;
		while (( m1 != first1 ) && (m2 != last2 )) {
			std :: iter_swap (--m1 , m2 );
			++ m2;
		}
		std :: reverse (first1 , m1 );
		std :: reverse (first1 , last1 );
		std :: reverse (m2 , last2 );
		std :: reverse (first2 , last2 );
	}
	return ! result ;
}

template < class BidirectionalIterator > bool next_combination ( BidirectionalIterator first , BidirectionalIterator middle , BidirectionalIterator last )
{
	return next_combination (first , middle , middle , last );
}

//要素vからr個取り出す組み合わせ
int func(vector<int> v, int r, int s){
	int res = 0;
	do{
		do{
			int sum = 0;
			rep(i,r){
				sum += v[i] * (i + 1);
			}
			if(sum == s) res++;
		}while(next_permutation(v.begin(), v.begin() + r));
	}while(next_combination(v.begin(), v.begin() + r, v.end()));
	return res;
}

int main(){
	int n, s;
	while(cin >> n >> s){

		vector<int> v(10);
		iota(all(v),0);

		cout << func(v,n,s) << endl;
	}
}
