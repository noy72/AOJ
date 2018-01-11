#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

bool end_parse;

typedef string::const_iterator State;
int number(State&);
int factor(State&);
int term(State&);
int expression(State&);
bool eq(State&);

// 数字の列をパースして、その数を返す。
int number(State &begin) {
    int ret = 0;

    while (isdigit(*begin)) {
        ret *= 10;
        ret += *begin - '0';
        begin++;
    }

    return ret;
}

// 括弧か数をパースして、その評価結果を返す。
int factor(State &begin) {
    if(end_parse) return -1;
    if (*begin == '(') {
        begin++; // '('を飛ばす。
        int ret = eq(begin);
        begin++; // ')'を飛ばす。
        return ret;
    } else {
        return number(begin);
    }
    return 0;
}

// 乗算除算の式をパースして、その評価結果を返す。
int term(State &begin) {
    if(end_parse) return -1;
    int ret = factor(begin);

    for (;;) {
        if (*begin == '*') {
            begin++;
            ret *= factor(begin);
        } else if (*begin == '/') {
            begin++;
            int tmp = factor(begin);
            if(tmp == 0 || ret % tmp != 0) {
                end_parse = 1;
                return 1e7;
            }
            else ret /= tmp;
        } else {
            break;
        }
    }

    return ret;
}

// 四則演算の式をパースして、その評価結果を返す。
int expression(State &begin) {
    if(end_parse) return -1;
    int ret = term(begin);

    for (;;) {
        if (*begin == '+') {
            begin++;
            ret += term(begin);
        } else if (*begin == '-') {
            begin++;
            ret -= term(begin);
            if(ret < 0){
                end_parse = true;
                return 1e7;
            }
        } else {
            break;
        }
    }

    return ret;
}

bool eq(State &begin){
    int ret = expression(begin);
    if(end_parse) return 0;

    if(*begin == '='){
        begin++;
        int tmp = expression(begin);
        return (ret == tmp);
    }
    return 0;
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
        //throw ParseError();
    }
}

int h, w;
bool sintaxCheck(string s){
    rep(i,s.size() - 1){
        if(not isdigit(s[i]) && not isdigit(s[i + 1])) return false;
        if(s[i] == '0' && isdigit(s[i + 1])) return false;
    }
    if(not isdigit(s.front()) || not isdigit(s.back())) return false;

    end_parse = 0;
    State tmp = s.begin();
    bool ans = eq(tmp);
    assert(tmp == s.end() || end_parse);
    return ans;
}

bool requireString(char m[15][15]){
    string str;
    range(i,1,h){ //ver
        range(j,1,w + 1){
            if(m[i - 1][j] == '#' && m[i][j] != '#' && m[i + 1][j] != '#'){
                str = "";
                for(int k = i; m[k][j] != '#'; k++) str.push_back(m[k][j]);
                if(not sintaxCheck(str)) return false;
            }
        }
    }
    range(i,1,h + 1){ //hor
        range(j,1,w){
            if(m[i][j - 1] == '#' && m[i][j] != '#' && m[i][j + 1] != '#'){
                str = "";
                for(int k = j; m[i][k] != '#'; k++) str.push_back(m[i][k]);
                if(not sintaxCheck(str)) return false;
            }
        }
    }
    return true;
}

bool check(char m[15][15]){
    bool f;
    string str;
    range(i,1,h){ //ver
        range(j,1,w + 1){
            if(m[i - 1][j] == '#' && m[i][j] != '#' && m[i + 1][j] != '#'){
                f = true;
                str = "";
                for(int k = i; m[k][j] != '#'; k++){
                    if(m[k][j] == '.'){
                        f = false;
                        break;
                    }
                    str+=m[k][j];
                }
                if(not f) continue;
                if(not sintaxCheck(str)) return false;
            }
        }
    }
    range(i,1,h + 1){ //hor
        range(j,1,w){
            if(m[i][j - 1] == '#' && m[i][j] != '#' && m[i][j + 1] != '#'){
                f = true;
                str = "";
                for(int k = j; m[i][k] != '#'; k++){
                    if(m[i][k] == '.'){
                        f = false;
                        break;
                    }
                    str+=m[i][k];
                }
                if(not f) continue;
                if(not sintaxCheck(str)) return false;
            }
        }
    }
    return true;
}

int main(){
    while(scanf("%d%d%*c",&h,&w),h){
        char m[15][15];
        rep(i,h + 2) rep(j, w + 2) m[i][j] = '#';

        int y[15], x[15];
        int k = 0;
        rep(i,h){
            rep(j,w){
                scanf("%c",&m[i + 1][j + 1]);
                if(m[i + 1][j + 1] == '.'){
                    y[k] = i + 1;
                    x[k++] = j + 1;
                }
            }
            scanf("%*c");
        }

        int n;
        scanf("%d%*c",&n);
        vector<char> v;
        rep(i,n){
            char x;
            scanf("%c%*c",&x);
            v.emplace_back(x);
        }
        if(not check(m)){
            cout << "No" << endl;
            continue;
        }

        bool f = false;
        do{
            rep(i,n) m[y[i]][x[i]] = v[i];
            f |= requireString(m);
        }while(next_permutation(all(v)));
        cout << (f ? "Yes" : "No" ) << endl;
    }
}
