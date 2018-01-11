#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const double INF = 10000000;

typedef complex<double> P;

int main(){
    int n;
    double r;
    while(cin >> r >> n, r||n){
        double p[41] = {0};
        rep(i,n){
            double left, right, h;
            cin >> left >> right >> h;
            left+=20; right+=20 - 1;
            for(int j = left; j <= right; j++){
                p[j] = max(p[j],h);
            }
        }
        rep(i,40) if(p[i] == INF) p[i] = 0;

        P c = {20.0, -r};
        double mini = INF;
        auto pow = [](double a){return a * a; };
        rep(i,40){
            //if(i < 17 || 22 < i) continue;

            if(not (i > 20 - r && i < 20 + r)) continue;
            mini = min(mini, min(p[i], p[i - 1]) + r - sqrt(pow(r) - pow(i - 20)));
            //show(min(p[i],p[i - 1]))
            //show(sqrt(pow(r) - pow(i - 20)))
            //show(r)
            //show(mini)
            //if(i == 0){
            //    P tmp = {static_cast<double>(i), 0};
            //    mini = min(mini, abs((abs(c - p[i]) - r) * sin(arg(c / p[i]))));
            //}else if(i == n - 1){
            //    P tmp = {static_cast<double>(i), 0};
            //    mini = min(mini, abs((abs(c - p[i]) - r) * sin(arg(c / p[i]))));
            //}else{
            //    P tmp = {static_cast<double>(i),min(p[i - 1], p[i])};
            //    show(p[i])
            //    show(tmp)
            //    double dist = abs(c - tmp) -r;
            //    show(dist)
            //    mini = min(mini, abs((abs(c - tmp) - r) * sin(arg(c / tmp))));
            //}
        }
        cout << fixed << setprecision(4) << mini << endl;
    }
}
