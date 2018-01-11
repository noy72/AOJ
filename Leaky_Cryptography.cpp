#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const long long M = (1LL << 32);

long long encode(string s){
    long long res = 0;
    rep(i,s.size()){
        res *= 16;
        if(s[i] >= 'a' && s[i] <= 'z'){
            res += 10 + s[i] - 'a';
        }else{
            res += s[i] - '0';
        }
    }
    return res;
}

int log16(long long n){
    int res = 0;
    while(n > 0){
        n /= 16;
        res++;
    }
    return res - 1;
}

string encode(long long n){
    if(n == 0) return "0";
    string str;
    int len = static_cast<int>(log16(n));
    long long K = 1;
    rep(i,len) K*=16;
    rep(i,len + 1){
        if(n / K == 0) str+= '0';
        else{
            if(n / K > 9) str += 'a' + (n / K - 10);
            else str+= ('0' + n / K);
        }
        n%=K; K/=16;
    }
    return str;
}

bool getBit(long long num, int i){
    return ((num & (1 << i)) != 0);
}

int main(){
    long long t;
    cin >> t;

    while(t--){
        vector<long long> a;
        long long s;
        rep(i,9){
            string x;
            cin >> x;
            if(i == 8) s = encode(x);
            else a.emplace_back(encode(x));
        }

        long long k = 1;
        long long ans = 0;
        rep(i,32){
            long long sum = accumulate(all(a), 0LL) % M;
            if(getBit(sum,i) ^ getBit(s,i)){
                ans += 1LL << i;
                rep(j,8)  a[j] ^= 1LL << i;
            }
            //show(ans)
        }
        cout << encode(ans % M) << endl;
    }
}
