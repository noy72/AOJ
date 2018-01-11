#include <assert.h>
#include <algorithm>
#include <complex>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <list>
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
const int INF = 100000000;
using namespace std;

int findOverlappingPair(string str1, string str2, string &str){
    int maxi = INT_MIN;
    int len1 = str1.size();
    int len2 = str2.size();

    for (int i = 1; i <= min(len1, len2); i++){
        if (str1.compare(len1 - i, i, str2, 0, i) == 0) {
            if (maxi < i) {
                maxi = i;
                str = str1 + str2.substr(i);
            }
        }
    }

    for (int i = 1; i <= min(len1, len2); i++) {
        if (str1.compare(0, i, str2, len2 - i, i) == 0) {
            if (maxi < i) {
                maxi = i;
                str = str2 + str1.substr(i);
            }
        }
    }

    return maxi;
}

string findShortestSuperstring(string arr[], int len){
    while(len != 1){
        int maxi = INT_MIN;  // to store  maxiimum overlap
        int l, r;   // to store array index of strings
        string resStr;  // to store resultant string after

        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                string str;
                int res = findOverlappingPair(arr[i], arr[j], str);

                if (maxi < res) {
                    maxi = res;
                    resStr.assign(str);
                    l = i, r = j;
                }
            }
        }
        len--;  //ignore last element in next cycle
        if (maxi == INT_MIN){
            arr[0] += arr[len];
        }else {
            arr[l] = resStr;   // copy resultant string to index l
            arr[r] = arr[len];  // copy string at last index to index r
        }
    }
    return arr[0];
}

int main(){
    int t;
    scanf("%d",&t);
    rep(_,t){
        int n;
        scanf("%d",&n);
        string arr[20];
        rep(i,n){
            cin >> arr[i];
        }
        sort(arr, arr + n);
        printf("Scenario #%d:\n",_ + 1);
        cout << findShortestSuperstring(arr, n) << endl;
    }
}
