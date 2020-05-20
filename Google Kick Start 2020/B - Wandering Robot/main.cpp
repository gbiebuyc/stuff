#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;
typedef long long ll;

int W, H, L, U, R, D;
double memo[300][300];

double solve(int x, int y) {
    if (memo[x][y] != -1)
        return memo[x][y];
    double result;
    if (x>=L&&x<=R&&y>=U&&y<=D)
        result = 0;
    else if (x==W&&y==H)
        result = 1;
    else if (x==W)
        result = solve(x, y+1);
    else if (y==H)
        result = solve(x+1, y);
    else
        result = 0.5*solve(x+1, y) + 0.5*solve(x, y+1);
    return memo[x][y] = result;
}

int main() {
    int t, tc;
    string line;
    getline(cin, line);
    stringstream(line) >> tc;
    //cout << fixed << setprecision(9);
    for (t=0; t<tc; t++) {
        getline(cin, line);
        stringstream(line)>>W>>H>>L>>U>>R>>D;
        for (int i=0; i<300; i++)
            for (int j=0; j<300; j++)
                memo[i][j] = -1.0;
        double ans = solve(1, 1);
        cout << "Case #" << t+1 << ": " << ans << endl;
    }
}
