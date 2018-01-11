#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int main(){
    int n;
    string s;
    cin >> n >> s;

    int right = -1, left = -1; //１内側, ２外側
    int rp, lp;
    rep(i,s.size() - 2){
        string sub = s.substr(i,2);
        if(sub == "><"){
            left = 1;
            lp = i;
            break;
        }else if(sub == "<>"){
            left = 2;
            lp = i;
            break;
        }
    }
    for(int i = s.size() - 1; i >= 0; i--){
        string sub = s.substr(i,2);
        if(sub == "><"){
            right = 1;
            rp = i;
            break;
        }else if(sub == "<>"){
            right = 2;
            rp = i;
            break;
        }
    }
    lp++;
    rp = n - rp - 1;
    //show(lp) show(rp)

    if(right == 2 && left == 2){
        cout << max(n - lp, n - rp) << endl;
    }else{
        cout << n << endl;
    }
}
