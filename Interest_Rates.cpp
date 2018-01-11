#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int main(){
    int n;
    while(cin >> n,n){
        double y;
        cin >> y;

        pair<int, double> p;
        auto f1 = [](double y, double r){ return 1 + y * r / 100; };
        auto f2 = [](double y, double r){ return pow(1 + r / 100,y); };
        rep(i,n){
            int b,t;
            double r;
            cin >> b >> r >> t;
            if(p.second < (t == 1 ? f1(y,r) : f2(y,r))){
                p.first = b;
                p.second = (t == 1 ? f1(y,r) : f2(y,r));
            }
        }
        cout << p.first << endl;
    }
}
