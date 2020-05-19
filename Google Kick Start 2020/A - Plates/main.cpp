#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
//#include <bits/stdc++.h>

using namespace std;

int N, K, P;
int cache[50][50*30];

int rec(int i, int taken, auto &plates) {
    if (i >= N || taken >= P)
        return 0;
    if (cache[i][taken] != -1) return cache[i][taken];
    int ans = rec(i+1, taken, plates);
    int cur = 0;
    for (int j = 0; j < K && taken+j+1 <= P; j++) {
        cur += plates[i][j];
        ans = max(ans, cur + rec(i+1, taken+j+1, plates));
    }
    cache[i][taken] = ans;
    return ans;
}

int main() {
    int numtc;
    cin >> numtc;
    for (int tc = 1; tc <= numtc; tc++) {
        cin >> N >> K >> P;
        vector<vector<int>> plates(N, vector<int> (K, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < K; j++) {
                int p;
                cin >> p;
                plates[i][j] = p;
            }
        }
        memset(cache, -1, 50*50*30*4);
        cout << "Case #" << tc << ": " << rec(0, 0, plates) << endl;
    }
}
