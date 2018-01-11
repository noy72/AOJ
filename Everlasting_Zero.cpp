#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

//区間A[a,b]と区間B[c,d]の関係
int intervalState(int a, int b, int c, int d){
    if(a < c && b < c) return 0;            //A < B
    else if(a > d && b > d) return 1;       //A > B
    else if(a <= c && d <= b) return 2;     //A -> B
    else if(c < a && b < d) return 3;       //B -> A
    else if(a <= c && b < d) return 4;      //A <= B
    else if(c < a && d <= b) return 5;      //A >= B
    return -1;
}

//Give input directly to vector<pair<int, int>> in
vector<pair<int, int>> JoinInterval(vector<pair<int,int>> in){
    vector<pair<int, int>> v;
    rep(i,in.size()) in[i].second *= -1;
    sort(all(in));
    rep(i,in.size()) in[i].second *= -1;

    rep(i,in.size()){
        if(v.empty()) v.emplace_back(in[i]);
        else{
            pair<int, int> &u = v.back();
            int tmp = intervalState(in[i].first,in[i].second,u.first,u.second);
            switch (tmp){
                case 0:
                case 1:
                    v.emplace_back(in[i]);
                    break;
                case 2:
                    u.first = in[i].first;
                    u.second = in[i].second;
                    break;
                case 3:
                    break;
                case 4:
                case 5:
                    u.first = max(u.first, in[i].first);
                    u.second = min(u.second, in[i].second);
                    break;
                case -1:
                    assert(0);
            }
        }
    }
    sort(all(v));
    return v;
}

int main(){
    int m,n;
    vector<pair<int,int>> v[105]; //v[i] := i番目のスキルの条件
    rep(i,105) v[i] = vector<pair<int,int>>(105);
    rep(i,105) rep(j,105) v[i][j] = make_pair(0,105);

    cin >> m >> n;
    rep(i,m){
        int k;
        cin >> k;
        map<int,vector<pair<int, int>>> m;
        rep(j,k){
            int num, point;
            string s;
            cin >> num >> s >> point;
            num--;

            pair<int, int> p;
            if(s[0] == '<') p = make_pair(0,point);
            else p = make_pair(point,105);
            m[num].emplace_back(p);
        }
        for(auto it : m){
            vector<pair<int, int>> in = JoinInterval(it.second);
            if(in.size() >= 2){
                cout << "No" << endl;
                return 0;
            }
            v[i][it.first] = in[0];
        }
    }

    auto canTake = [](vector<pair<int, int>> a, vector<pair<int, int>> b){
        rep(i,105) if(b[i].second < a[i].first) return 0;
        return 1;
    };

    bool used[105] = {0};
    rep(_,m){
        rep(i,m){
            if(used[i]) continue;
            bool f = true;
            //i番目のスキルを次にとるとする。
            rep(j,m){
                if(used[j] || i == j) continue;
                if(not canTake(v[i],v[j])){
                    f = false;
                    break;
                }
            }
            used[i] = f;
        }
    }
    //rep(i,m) show(used[i])

    auto check = [](bool used[105], int m){
        rep(i,m) if(used[i] == 0) return 0;
        return 1;
    };
    cout << (check(used,m) ? "Yes" : "No") << endl;
}
