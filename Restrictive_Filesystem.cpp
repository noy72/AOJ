#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int main(){
    int n;
    while(cin >> n,n){
        list<pair<int,pair<int, int>>> ls;
        ls.push_back(make_pair(-1,make_pair(-1,-1)));

        rep(i,n){
            char com;
            cin >> com;
            if(com == 'W'){
                int a, b;
                cin >> a >> b;
                auto cur = ls.begin();
                auto bef = ls.begin();
                cur++;
                while(b > 0){
                    int tmp = bef->second.second + 1;
                    if(cur == ls.end()){
                        ls.push_back(make_pair(a,make_pair(tmp, tmp + b - 1)));
                        b = 0;
                    }else if(bef->second.second + 1 != cur->second.first){
                        int dif = cur->second.first - bef->second.second - 1;
                        if(b <= dif){
                            ls.insert(cur,make_pair(a,make_pair(tmp,tmp + b - 1)));
                            b = 0;
                        }else{
                            ls.insert(cur,make_pair(a,make_pair(tmp,cur->second.first - 1)));
                            b -= dif;
                        }
                        cur--;
                        bef = cur;
                        bef--;
                    }
                    cur++;
                    bef++;
                }
            }else if(com == 'D'){
                int a;
                cin >> a;
                for(auto it = ls.begin(); it != ls.end();){
                    if(it->first == a){
                        it = ls.erase(it);
                    }else{
                        it++;
                    }
                }
            }else{
                int a;
                cin >> a;

                bool f = false;
                for(auto it:ls){
                    if(it.second.first <= a && a <= it.second.second){
                        cout << it.first << endl;
                        f = true;
                        break;
                    }
                }
                if(not f) cout << -1 << endl;
            }
            //for(auto it : ls){ cout << it.second.first << ' ' << it.second.second << endl; }
        }
        cout << endl;
    }
}
