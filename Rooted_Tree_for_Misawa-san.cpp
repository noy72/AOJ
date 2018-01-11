#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

typedef string::const_iterator State;

struct Node{
    Node *right, *left;
    int num;
};
Node node[1000];

int number(State &s){
    int ret = 0;
    while(isdigit(*s)){
        ret *= 10;
        ret += *s - '0';
    }
    return ret;
}


Node* dfs(State &s, int &i){
    int cur = i;
    i++;
    if(*s == '('){
        s++;
        node[i].right = dfs(s,i);
    }else if(*(s - 1) == '(' && *s == ')'){
        s++;
        node[cur].right = dfs(s,i);
    }else if(*s == '['){
        s++;
        node[cur].num = number(s);
        s++;
    }
}


int main(){
    string a,b;
    cin >> a >> b;

    State tmp = a.begin();
    //dfs(
}
