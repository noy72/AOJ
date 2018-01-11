#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

char alp[200];
    string s;

typedef string::const_iterator State;
string cipher(State&);
string String(State&);
string letter(State&);


string letter(State &begin){
    string ret;
    if(*begin == '+'){
        begin++;
        ret = letter(begin);
        ret[0] = alp[ret[0] + 1];
    }else if(*begin == '-'){
        begin++;
        ret = letter(begin);
        ret[0] = alp[ret[0] - 1];
    }else{
        ret += *begin;
        begin++;
    }
    return ret;
}

// 括弧か数をパースして、その評価結果を返す。
string String(State &begin) {
    if (*begin == '[') {
        begin++; // '('を飛ばす。
        string ret = cipher(begin);
        begin++; // ')'を飛ばす。
        reverse(all(ret));
        return ret;
    }else{
        return letter(begin);
    }
    return 0;
}

// 四則演算の式をパースして、その評価結果を返す。
string cipher(State &begin) {
    string ret = String(begin);

    while(begin != s.end()){
        if(*begin == ']') break;
        ret += cipher(begin);
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
    for(char i = 'A'; i <= 'Z'; i++){
        alp[static_cast<int>(i)] = i;
    }
    alp[static_cast<int>('A') - 1] = 'Z';
    alp[static_cast<int>('Z') + 1] = 'A';

    while(cin >> s,s[0] != '.'){
        string ans = "";
        rep(i,100) ans += 'Z';
        vector<int> v;
        rep(i,s.size()){
            if(s[i] == '?') v.emplace_back(i);
        }
        char i[3];
        for(i[0] = 'A'; i[0] <= 'Z'; i[0]++){
            for(i[1] = 'A'; i[1] <= 'Z'; i[1]++){
                for(i[2] = 'A'; i[2] <= 'Z'; i[2]++){
                    rep(l,v.size()) s[ v[l] ] = i[l];

                    State  tmp = s.begin();
                    ans = min(ans,cipher(tmp));
                    if(v.size() == 0) goto end;
                }
            }
        }
end:
        cout << ans << endl;
    }
}
