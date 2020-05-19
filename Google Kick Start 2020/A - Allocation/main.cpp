#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include <bits/stdc++.h>

using namespace std;

int main() {
    int tc, numtc;
    cin >> numtc;
    for (tc = 1; tc <= numtc; tc++) {
        vector<int> houses;
        int numHouses, budget;
        cin >> numHouses >> budget;
        while (numHouses--) {
            int h;
            cin >> h;
            houses.push_back(h);
        }
        sort(houses.begin(), houses.end());
        int i;
        for (i = 0; i<houses.size() && budget-houses[i]>=0; i++)
            budget -= houses[i];
        cout << "Case #" << tc << ": " << i << endl;
    }
}
