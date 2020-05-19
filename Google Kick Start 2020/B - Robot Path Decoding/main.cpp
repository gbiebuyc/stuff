#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int i;
string line;

pair<int, int> parse() {
    int x, y;
    x = y = 0;
    for (;; i++) {
        char c = line[i];
        if (i>=line.size() || c==')') {
            return make_pair(x, y);
        }
        else if (c>='2'&&c<='9') {
            int n = c-'0';
            pair<int, int> p;
            i+=2;
            p = parse();
            while (n--) {
                x += p.first;
                y += p.second;
                if (x>=1000000000) x-=1000000000;
                else if (x<0) x+=1000000000;
                if (y>=1000000000) y-=1000000000;
                else if (y<0) y+=1000000000;
            }
        }
        else if (c=='N') y--;
        else if (c=='S') y++;
        else if (c=='E') x++;
        else if (c=='W') x--;
        if (x>=1000000000) x-=1000000000;
        else if (x<0) x+=1000000000;
        if (y>=1000000000) y-=1000000000;
        else if (y<0) y+=1000000000;
    }
}

int main() {
    int t, tc;
    cin >> tc;
    cin.ignore();
    for (t=0; t<tc; t++) {
        getline(cin, line);
        i = 0;
        pair<int, int> p;
        p = parse();
        int x, y;
        x = p.first+1;
        y = p.second+1;
        cout << "Case #" << t+1 << ": " << x<<" "<<y << endl;
    }
}
