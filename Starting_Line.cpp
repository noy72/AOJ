#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const double EPS = 1e-9;

int main(){
    int n;
    double k, t, u, v, l;
    cin >> n >> k >> t >> u >> v >> l;

    double c[205];
    rep(i,n) cin >> c[i];
    c[n] = l;

    double m, h, s; //現在位置、所持人参数、加速の残り時間
    double time = 0;
    int i = 0;
    while(m < l){
        double next = c[i] - m;
        if((h > 0 && s < EPS) || h > k){
            h--;
            s = t;
        }else if(h == 0 && s < EPS){
            time += next / u;
            m += next;
            i++;
            h++;
        }else if(s > EPS){
            if(next / v <= s){
                s -= next / v;
                time += next / v;
                m += next;
                i++;
                h++;
            }else{
                m += s * v;
                time += s;
                s = 0;
            }
        }
    }
    cout <<fixed << setprecision(8) <<  time << endl;
}
