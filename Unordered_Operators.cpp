#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

typedef string::const_iterator State;
long long number(State&);
long long factor(State&,vector<long long>);
long long expr3(State&,long long,vector<long long>);
long long expr2(State&,long long,vector<long long>);
long long expr1(State&,long long,vector<long long>);

vector<vector<long long>> v;

// 数字の列をパースして、その数を返す。
long long number(State &begin) {
    long long ret = 0;

    while (isdigit(*begin)) {
        ret *= 10;
        ret += *begin - '0';
        begin++;
    }

    return ret;
}

// 括弧か数をパースして、その評価結果を返す。
long long factor(State &begin, vector<long long> v) {
    if (*begin == '(') {
        begin++; // '('を飛ばす。
        long long ret = expr1(begin,0,v);
        begin++; // ')'を飛ばす。
        return ret;
    } else {
        return number(begin);
    }
    return 0;
}

long long expr3(State &begin, long long i, vector<long long> v) {
    long long ret = factor(begin,v);

    for (;;) {
        if (*begin == '+' && v[i] & 1) {
            begin++;
            ret += factor(begin,v);
        } else if (*begin == '-' && v[i] & 2) {
            begin++;
            ret -= factor(begin,v);
        } else if (*begin == '*' && v[i] & 4){
            begin++;
            ret *= factor(begin,v);
        } else {
            break;
        }
    }

    return ret;
}

long long expr2(State &begin, long long i, vector<long long> v) {
    long long ret = expr3(begin, 2, v);

    for (;;) {
        if (*begin == '+' && v[i] & 1) {
            begin++;
            ret += expr3(begin, 2, v);
        } else if (*begin == '-' && v[i] & 2) {
            begin++;
            ret -= expr3(begin, 2, v);
        } else if (*begin == '*' && v[i] & 4){
            begin++;
            ret *= expr3(begin, 2, v);
        } else {
            break;
        }

    }

    return ret;
}

long long expr1(State &begin, long long i, vector<long long> v) {
    long long ret = expr2(begin, 1, v);

    for (;;) {
        if (*begin == '+' && v[i] & 1) {
            begin++;
            ret += expr2(begin, 1, v);
        } else if (*begin == '-' && v[i] & 2) {
            begin++;
            ret -= expr2(begin, 1, v);
        } else if (*begin == '*' && v[i] & 4){
            begin++;
            ret *= expr2(begin, 1, v);
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
    vector<long long> num = {1,2,4};
    do{ v.emplace_back(num); }while(next_permutation(all(num))); 
    num = {0,3,4};
    do{ v.emplace_back(num); }while(next_permutation(all(num))); 
    num = {0,5,2};
    do{ v.emplace_back(num); }while(next_permutation(all(num))); 
    num = {0,6,1};
    do{ v.emplace_back(num); }while(next_permutation(all(num))); 
    num = {0,0,7};
    do{ v.emplace_back(num); }while(next_permutation(all(num))); 

    string s;
    cin >> s;

    long long ans = -LONG_MAX;
    rep(i,v.size()){
        State tmp = s.begin();
        ans = max(ans, expr1(tmp, 0, v[i]));
        assert(tmp == s.end());
    }
    cout << ans << endl;
}
