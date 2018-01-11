#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
//const int INF = 1e8;
using namespace std;

long long C(long long mid, long long len, long long r, long long a, long long b, long long c){
	//cout << n << ' ' << mid << ' ' << len << ' ' << r << endl;
	long long _3, _5, _15;
	_3 = mid / 3;
	_5 = mid / 5;
	_15 = mid / 15;
	_3 -= _15;
	_5 -= _15;
	_3 -= a;
	_5 -= b;
	_15 -= c;
	//cout << _3 << ' ' << _5 << ' ' << _15 << endl;
	//show(mid)
	//	show((_3 + _5 + _15 * 2) * 4 + ((mid - r + 1) - _3 - _5 - _15) * len)

	return (_3 + _5 + _15 * 2) * 4 + ((mid - r + 1) - _3 - _5 - _15) * len;
}

int main(){
	long long n;
	cin >> n;

	long long _3[20], _5[20], _15[20];
	_3[0] = _5[0] = _15[0] = 0;
	long long sum = 0;
	for(long long r = 1, i = 1; true; r*=10, i++){
		_3[i] = (r * 10 - 1) / 3;
		_5[i] = (r * 10 - 1) / 5;
		_15[i] = (r * 10 - 1) / 15;
		_3[i] -= _15[i];
		_5[i] -= _15[i];

		_3[i] -= _3[i - 1];
		_5[i] -= _5[i - 1];
		_15[i] -= _15[i - 1];

		long long result = (_3[i] + _5[i] + _15[i] * 2) * 4 + ((r * 10 - r) - _3[i] - _5[i] - _15[i]) * i;
		//show(sum)
		if(sum + result > n){
			long long right = r * 10 - 1, left = r;
			rep(_,100){
				long long mid = (right + left ) / 2;
				if(C(mid, i, r, _3[i - 1], _5[i - 1], _15[i - 1]) < n - sum) left = mid;
				else right = mid;
			}
			show(left)
				show(sum + C(left, i, r, _3[i - 1], _5[i - 1], _15[i - 1]))
				return 0;
		}
		sum += result;
	}

}
