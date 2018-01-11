#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;
const double EPS = 1e-8;

int main(){
    double d;
    cin >> d;

    double maxi = d * sqrt(2);
    rep(i,20){
        show(d * d)
        double y = sqrt(d * d - i * i);
        show(y)
        if(y <= 1.0) y++;
        maxi = max(maxi, y + i);
    }
    cout << maxi << endl;
}
