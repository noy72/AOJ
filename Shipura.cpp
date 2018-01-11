#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).*begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int M = 1000000007;

string s;

typedef string::const_iterator State;
int number(State&);
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


// 乗算除算の式をパースして、その評価結果を返す。
int term(State &begin) {
    if (*begin == 'S') {
        begin++; begin++;
        long long ret = expression(begin);
        begin++;
        return ret * ret % M;
    } else {
        return number(begin);
    }
}

// 四則演算の式をパースして、その評価結果を返す。
int expression(State &begin) {
    int ret = term(begin);

    while(s.end() - begin >= 2){
        if (*begin ==  '>' && *(begin + 1) == '>'&& *(begin + 2) != '>'){
            begin++; begin++;
            ret = ret >> min(term(begin), 31);
        } else {
            break;
        }
    }

    return ret;
}

int main(){
    string tmp;
    while(getline(cin,tmp),tmp != "#"){
        s="";
        for(auto it:tmp) if(it != ' ') s+=it;
        State state = s.begin();
        cout << expression(state) << endl;
    }
}
