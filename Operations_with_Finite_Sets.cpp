#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

map<char,vector<int>> m;

void compress(vector<int> &v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
}

vector<int> U(vector<int> a, vector<int> b){
    vector<int> ret;
    set_union(all(a), all(b), back_inserter(ret));
    return ret;
}

vector<int> I(vector<int> a, vector<int> b){
    vector<int> ret;
    set_intersection(all(a), all(b), back_inserter(ret));
    return ret;
}

vector<int> D(vector<int> a, vector<int> b){
    vector<int> ret;
    set_difference(all(a), all(b), back_inserter(ret));
    return ret;
}

vector<int> S(vector<int> a, vector<int> b){
    vector<int> x,y,ret;
    set_symmetric_difference(all(a), all(b), back_inserter(ret));
    return ret;
}

vector<int> C(vector<int> a){
    vector<int> ret;
    set_difference(all(m['U']), all(a), back_inserter(ret));
    return ret;
}

typedef string::const_iterator State;
vector<int> factor(State&);
vector<int> expression(State&);
void consume(State&,char);

vector<int> factor(State &begin) {
    if (*begin == '(') {
        begin++; // '('を飛ばす。
        vector<int> ret = expression(begin);
        begin++; // ')'を飛ばす。
        return ret;
    } else {
        return m[*begin++];
    }
}

vector<int> term(State &begin){
    if (*begin == 'c') {
        begin++;
        return C(factor(begin));
    } else {
        return factor(begin);
    }
}

// 四則演算の式をパースして、その評価結果を返す。
vector<int> expression(State &begin) {
    vector<int> ret = term(begin);

    for (;;) {
        if (*begin == 'u') {
            begin++;
            ret = U(ret, term(begin));
        } else if(*begin == 'i') {
            begin++;
            ret = I(ret, term(begin));
        } else if(*begin == 'd') {
            begin++;
            ret = D(ret, term(begin));
        } else if(*begin == 's') {
            begin++;
            ret = S(ret, term(begin));
        } else{
            break;
        }
    }

    return ret;
}

//beginがexpectedを指していたらbeginを一つ進める。
void consume(State &begin, char expected) {
    if (*begin == expected) {
        begin++;
    } else {
        cerr << "Expected '" << expected << "' but got '" << *begin << "'" << endl;
        cerr << "Rest string is '";
        while (*begin) {
            cerr << *begin++;
        }
        cerr << "'" << endl;
        assert(0);
        //throw ParseError();
    }
}

int main(){
    while(true){
        m.clear();
        char c;
        int n;
        bool f = false;
        while(cin >> c >> n){
            f = true;
            if(c == 'R' && n == 0) break;
            int a;
            rep(i,n){
                cin >> a;
                m['U'].emplace_back(a);
                m[c].emplace_back(a);
            }
        }
        compress(m['U']);
        if(not f) break;
        for(auto &it:m) sort(all(it.second));

        cin.ignore();
        string s;
        getline(cin,s);
        State tmp = s.begin();
        vector<int> ans = expression(tmp);
        assert(tmp == s.end());
        if(ans.empty()) cout << "NULL" << endl;
        else rep(i,ans.size()) cout << ans[i] << (i == ans.size() - 1 ? '\n' : ' ');
    }
}
