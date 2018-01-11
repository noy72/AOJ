#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

int weight[30] = {0}, zero[30] = {0};

void solve(string num, int &len, int &used, map<int,map<int,int>> &m, set<char> &s){
    int sum = 0;
    int i = 0;
    for(auto it:s){
        if(zero[it - 'A'] && num[i] == '0') return;
        sum+=weight[it - 'A'] * (num[i] - '0');
        i++;
    }
    m[sum][used]++;
}

void dfs(int used, string s, int &len, map<int,map<int,int>> &m, set<char> &st){
    range(i,0,10){
        if(used & (1 << i)) continue;
        used ^= (1 << i);
        s+=('0' + i);
        if(s.size() == len) solve(s,len,used,m,st);
        else dfs(used,s,len,m,st);
        used ^= (1 << i);
        s.pop_back();
    }
}

void makeConvertTable(int up[30], int low[30], set<char> s){
    auto it = s.begin();
    int j = 0, k = 0;
    rep(i,s.size()){
        if(i < s.size() / 2){
            up[*it - 'A'] = j++;
        }else{
            low[*it - 'A'] = k++;
        }
        it++;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    int n;
    while(cin >> n,n){
        map<int,map<int,int>> up, low; //sum -> map<used,count>
        set<char> s, s_up, s_low;
        memset(weight, 0, sizeof(weight));
        memset(zero, 0, sizeof(zero));


        rep(i,n){
            string a;
            cin >> a;
            int k = 1;
            for(int j = a.size() - 1; j >= 0; j--){
                if(i == n - 1) weight[a[j] - 'A'] -= k;
                else weight[a[j] - 'A'] += k;
                s.insert(a[j]);
                k*=10;
            }
            if(a.size() >= 2)  zero[a[0] - 'A'] = 1;
        }
        //rep(i,27) show(zero[i])

        {
            auto it = s.begin();
            rep(i,s.size()){
                if(i < s.size() / 2) s_up.insert(*it);
                else s_low.insert(*it);
                it++;
            }
        }

        int len = s.size() / 2;
        dfs(0,"",len,up,s_up);
        len = s.size() - len;
        dfs(0,"",len,low,s_low);

        int cnt = 0;
        for(auto i:up){
            for(auto k:i.second){
                for(auto j:low[-i.first]){
                    if((j.first & k.first) == 0){
                        cnt+=j.second*k.second;
                    }
                }
            }
        }
        cout << cnt << endl;
    }
}
