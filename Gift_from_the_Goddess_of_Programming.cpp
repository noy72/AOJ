#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

struct Data{
    int m;
    char io;
    string id;
};

void requireTime(map<string,int> &time, map<string, vector<pair<int, int>>> s){
    auto it = s.begin();
    vector<pair<int, int>> god = s["000"];
    it++;

    for(; it != s.end(); it++){
        rep(i,god.size()){
            vector<pair<int, int>> tmp = it->second;
            rep(j,tmp.size()){
                int left = max(god[i].first, tmp[j].first);
                int right = min(god[i].second, tmp[j].second);
                time[ it->first ] += max(0, right - left);
            }
        }
    }
}

int main(){
    int n;
    while(cin >> n,n){
        int maxi = 0;
        map<string,int> time;//id->一緒にいた時間
        map<string, vector<pair<int, int>>> seg; //idごとの区間
        rep(i,n){
            string id;
            int th,tm,m,d;
            char io,g;

            cin >> m >> g >> d >> th >> g >> tm >> io >> id;
            int time = m * 30 * 24 * 60 + d * 24 * 60 + th * 60 + tm;
            if(io == 'I'){
                seg[id].emplace_back(make_pair(time,-1));
            }else{
                seg[id].back().second = time;
            }
        }
        requireTime(time,seg);
        //show(maxi)
        for(auto it : time){
            maxi = max(maxi,it.second);
        }
        cout << maxi << endl;
    }
}
