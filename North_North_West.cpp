#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int main(){
    string s;
    while(cin >> s,s[0] != '#'){
        int i = 0;
        vector<bool> v;
        while(i < s.size()){
            if(s.substr(i,5) == "north"){
                v.emplace_back(1);
                i+=5;
            } else {
                v.emplace_back(0);
                i+=4;
            }
        }

        int a = -1;
        int cnt = -1;
        for(int i = v.size() - 1; i >= 0; i--){
            cnt++;
            if(v[i]){
                if(cnt == 0) a = 0;
                else a = a * 2.0 - 90.0;
            }else{
                if(cnt == 0) a = 90;
                else a = a * 2.0 + 90.0;
            }
        }

        int b = pow(2, cnt);
        //cout << a << ' ' << b << endl;
        while(a % 2 == 0 && b % 2 == 0){
            a /= 2;
            b /= 2;
        }
        if(b > 1) cout << a << '/' << b << endl;
        else cout << a << endl;
    }
}
