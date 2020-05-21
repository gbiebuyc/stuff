#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

int main() {
    int t, N;
    cin>>t;
    for (int i=1; i<=t; i++) {
        cin>>N;
        vector<int> v(N);
        for (int i=0; i<N; i++) {
            char c;
            cin>>c;
            v[i] = c - '0';
        }
        int len = ceil(N/2.0);
        int ans = 0;
        for (int i=0; i<len; i++)
            ans+=v[i];
        int cur = ans;
        for (int i=0; i<N-len; i++) {
            cur = cur - v[i] + v[i+len];
            if (cur>ans)
                ans = cur;
        }
        cout<<"Case #"<<i<<": "<<ans<<endl;
    }
}
