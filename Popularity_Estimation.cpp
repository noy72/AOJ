#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int main(){
    int n;
    while(cin >> n,n){
        map<int,int> m;
        map<string,vector<int>> d;
        string name;
        map<string,int> vote;
        rep(i,n){
            int k;
            cin >> name >> k;
            if(k == 0) vote[name] = 0;
            rep(j,k){
                int a;
                cin >> a;
                m[a]++;
                d[name].emplace_back(a);
            }
        }

        for(auto itd : d){
            //show(itd.first)
            for(auto itv : itd.second){
                vote[itd.first] += n - m[ itv ] + 1;
                //show(n - m[ itv ])
            }
        }

        int mini = 1e8;
        for(auto it : vote){
            if(mini > it.second){
                mini = it.second;
                name = it.first;
            }
        }
        cout << mini << ' ' << name << endl;
    }
}
