#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
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


double d[22][3];

//要素vからr個取り出す組み合わせ
double func(vector<int> v, int r){
    double ret = 0;
    do{
        double sum = 0;
        rep(i,r){
            rep(j,r){
                rep(k,3) sum += (d[v[i]][k] - d[v[j]][k]) * (d[v[i]][k] - d[v[j]][k]);
            }
        }
        ret = max(ret, sum / 2);
    }while(next_combination(v.begin(), v.begin() + r, v.end()));
    return ret;
}

int main(){
    int n, m;
    cin >> n >> m;
    rep(i,n) rep(j,3) cin >> d[i][j];

    vector<int> v;
    rep(i,n) v.emplace_back(i);
    cout <<fixed << setprecision(6)<< func(v,m) << endl;

}
