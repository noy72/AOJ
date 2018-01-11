#include<bits/stdc++.h>
#define range(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,b) for(int i = 0; i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define show(x)  cerr << #x << " = " << (x) << endl;
using namespace std;

const int b = 120;

class Dice{
    public:
        int top, south, east, west, north, bottom;
        void setRabel(int a[6]){ //top, south, east, west, north, bottom
            top = a[0];
            south = a[1];
            east = a[2];
            west = a[3];
            north = a[4];
            bottom = a[5];
        }
        void role(int south, int top){
            int c[6][5] = {
                {south,west,north,east,south},
                {top,south,bottom,north,top},
                {top,east,bottom,west,top},
                {top,west,bottom,east,top},
                {top,north,bottom,south,top},
                {south,west,north,east,south},
            };
            this->south = south;
            north = 7 - south;
            this->top = top;
            bottom = 7 - top;
            rep(i,6){
                rep(j,4){
                    if(c[i][j] == south && c[i][j + 1] == top){
                        east = i + 1;
                        west = 7 - (i + 1);
                        return;
                    }
                }
            }
            assert(0);
        }
        void role(char com){
            int temp;
            switch (com) {
                case 'E':
                    temp = top;
                    top = west;
                    west = bottom;
                    bottom = east;
                    east = temp;
                    break;
                case 'N':
                    temp = top;
                    top = south;
                    south = bottom;
                    bottom = north;
                    north = temp;
                    break;
                case 'W':
                    temp = east;
                    east = bottom;
                    bottom = west;
                    west = top;
                    top = temp;
                    break;
                case 'S':
                    temp = north;
                    north = bottom;
                    bottom = south;
                    south = top;
                    top = temp;
                    break;
                default:
                    assert(0);
            }
        }
};

pair<char, char> direc(Dice d){
    pair<int, char> p[4];
    p[0] = make_pair(d.north, 'N');
    p[1] = make_pair(d.east, 'E');
    p[2] = make_pair(d.south, 'S');
    p[3] = make_pair(d.west, 'W');
    sort(p,p + 1,greater<pair<int,char>>());
    return make_pair(p[0].second, p[1].second);
}

void roling(int t[250][250], int h[250][250], pair<char,char> a, Dice d){
    int dy = 0,dx = 0;
    int x = b, y = b;
    auto dydx = [](char a, int &dy, int &dx){
        if(a == 'N') dy--;
        else if(a == 'W') dx++;
        else if(a == 'S') dy++;
        else dx--;
    };
    auto moving = [](int h[250][250], int &x, int &y, int dx, int dy, Dice &d, char com){
        while(h[y][x] > h[y + dy][x + dx]){
            d.role(com);
            y+=dy;
            x+=dx;
        }
    };

    dydx(a.first, dy, dx);
    moving(h,x,y,dx,dy,d,a.first);
    dydx(a.second, dy, dx);
    moving(h,x,y,dx,dy,d,a.second);

    h[y][x]++;
    t[y][x] = d.top;
}

int main(){
    int n;
    while(cin >> n,n){
        int t[250][250] = {0};
        int h[250][250] = {0};
        rep(i,n){
            Dice d;
            int a[6] = {1,3,2,5,4,6};
            d.setRabel(a);

            int x, y;
            cin >> x >> y;
            d.role(x,y);
            pair<char, char> m = direc(d);
            roling(t,h,m,d);
        }

        int ans[7] = {0};
        rep(i,250) rep(j,250){
            ans[ t[i][j] ]++;
        }
        rep(i,6){
            if(i) cout << ' ';
            cout << ans[i + 1];
        }
        cout << endl;
    }
}
