#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

class Circle{
    public : double x, r;
};

double dist(Circle a, Circle b){
    double z = a.r + b.r;
    double x = abs(a.r - b.r);
    return sqrt(z * z - x * x);
}

int main(){
    int n;
    cin >> n;

    Circle v[505] = {Circle{0,0}};
    rep(i,n){
        cin >> v[i].r;
    }

    rep(i,n){
        double max_dist = v[i].r;
        int p = 0;
        rep(j,i){
            //if(max_dist < dist(v[i],v[j]) + (limit - v[j].x)){
            //    min_dist = dist(v[i],v[j]) + (limit - v[j].x);
            //    p = j;
            //}
            max_dist = max(max_dist, dist(v[i],v[j]) + v[j].x);
        }
        if(i == p) v[i].x = v[i].r;
        else v[i].x = max_dist;
    }

    double ans = 0;
    rep(i,n){
        ans = max(ans, v[i].x + v[i].r);
    }
    cout <<fixed << setprecision(5) <<  ans << endl;
}
