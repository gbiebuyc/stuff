#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

ll t, R, C;
string grid[250];

int manhattan(int i, int j, int k, int l) {
    return abs(k-i)+abs(l-j);
}

int find(int i, int j) {
    char old = grid[i][j];
    grid[i][j] = '1';
    int maxDist = 0;
    for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
            if (grid[i][j]=='1')
                continue;
            int minDist = 9999;
            for (int k=0; k<R; k++) {
                for (int l=0; l<C; l++) {
                    if (grid[k][l]=='1') {
                        int dist = manhattan(i,j,k,l);
                        if (dist<minDist)
                            minDist=dist;
                    }
                }
            }
            if (minDist>maxDist)
                maxDist=minDist;
        }
    }
    grid[i][j] = old;
    return maxDist;
}

int main() {
    cin>>t;
    for (int i=1; i<=t; i++) {
        cin>>R>>C; cin.ignore();
        for (int i=0; i<R; i++)
            getline(cin, grid[i]);
        int minDist = 9999;
        //int best_i, best_j;
        for (int i=0; i<R; i++) {
            for (int j=0; j<C; j++) {
                int dist = find(i,j);
                if (dist<minDist) {
                    minDist=dist;
                    //best_i = i;
                    //best_j = j;
                }
            }
        }
        //grid[best_i][best_j] = '1';
        //for (int i=0; i<R; i++)
            //cout<<grid[i]<<endl;
        cout<<"Case #"<<i<<": "<<minDist<<endl;
    }
}
