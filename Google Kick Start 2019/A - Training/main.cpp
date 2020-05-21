#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

int main() {
    ll t, N, P;
    cin>>t;
    for (int i=1; i<=t; i++) {
        cin>>N>>P;
        vector<ll> v(N);
        for (int i=0; i<N; i++)
            cin>>v[i];
        sort(v.begin(), v.end());
        vector<ll> prefixSum(N);
        prefixSum[0] = v[0];
        for (int i=1; i<N; i++)
            prefixSum[i] = prefixSum[i-1]+v[i];
        ll minDiff = 1000000000000000000;
        for (int i=0; i<N-P+1; i++) {
            ll diff = P*v[i+P-1] - (prefixSum[i+P-1]-(i?prefixSum[i-1]:0));
            if (diff<minDiff) {
                minDiff = diff;
            }
        }
        cout<<"Case #"<<i<<": "<<minDiff<<endl;
    }
}
