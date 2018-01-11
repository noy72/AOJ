#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int MAX = 10000000;

int main(){
    int n,m;
    while(cin >> m >> n,n||m){
        static bool es[MAX] = {0};
        memset(es,0,sizeof(es));

        int i = m;
        while(true){
            if(not es[i]){
                n--;
                if(n < 0){
                    cout << i << endl;
                    break;
                }
                for(int j = i + i; j < MAX; j+=i){
                    es[j] = 1;
                }
            }
            i++;
        }
    }
}
