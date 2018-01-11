#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

typedef string::const_iterator State;
int number(State&);
int factor(State&);
int term(State&);
int expression(State&);

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
    if (*begin == '(') {
        begin++; // '('を飛ばす。
        int ret = expression(begin);
        begin++; // ')'を飛ばす。
        return ret;
    } else {
        return number(begin);
    }
    return -1;
}

// 乗算除算の式をパースして、その評価結果を返す。
int term(State &begin) {
    int ret = factor(begin);

    for (;;) {
        if (*begin == '*') {
            begin++;
            ret *= factor(begin);
        } else if (*begin == '/') {
            begin++;
            ret /= factor(begin);
        } else {
            break;
        }
    }

    return ret;
}

// 四則演算の式をパースして、その評価結果を返す。
int expression(State &begin) {
    int ret = term(begin);

    for (;;) {
        if (*begin == '+') {
            begin++;
            ret += term(begin);
        } else if (*begin == '-') {
            begin++;
            ret -= term(begin);
        } else {
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
        //throw ParseError();
    }
}


int main(){
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        State tmp = s.begin();
        int ans = expression(tmp);
        consume(tmp, '=');
        cout << ans << endl;
    }
}
