#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

typedef string::const_iterator State;
int countMinus(State&);
int negative(int,int);
int number(State&);
int factor(State&);
int expression(State&);

int p, q, r;

int inverted(int ret){
    if(ret == 0) return 2;
    else if(ret == 2) return 0;
    else return 1;
}

// 数字の列をパースして、その数を返す。
int number(State &begin) {
    int ret = 0;
    if(*begin == 'P') ret = p;
    else if(*begin == 'Q') ret = q;
    else if(*begin == 'R') ret = r;
    else if(isdigit(*begin)) ret = *begin - '0';
    else return 0;

    begin++;
    return ret;
}

// 括弧か数をパースして、その評価結果を返す。
int factor(State &begin) {
    int ret;
    if (*begin == '(') {
        begin++; // '('を飛ばす。
        ret = expression(begin);
        begin++; // ')'を飛ばす。
        return ret;
    }else {
        return number(begin);
    }
}

int term(State &begin){
    if (*begin == '-') {
        begin++;
        return inverted(term(begin));
    } else {
        return factor(begin);
    }
}

// 四則演算の式をパースして、その評価結果を返す。
int expression(State &begin) {
    int ret = term(begin);

    for (;;) {
        if (*begin == '+') {
            begin++;
            ret = max(ret, term(begin));
        } else if (*begin == '*') {
            begin++;
            ret = min(ret, term(begin));
        } else {
            break;
        }
    }

    return ret;
}

int main(){
    string s;
    while(cin >> s, s[0] != '.'){
        int cnt = 0;
        for(p = 0; p < 3; p++){
            for(q = 0; q < 3; q++){
                for(r = 0; r < 3; r++){
                    State tmp = s.begin();
                    if(expression(tmp) == 2){
                        //cout << p << ' ' << q << ' ' << r << endl;
                        cnt++;
                    }
                }
            }
        }
        cout << cnt << endl;
    }
}
