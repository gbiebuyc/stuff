#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

int N, K;
int sessions[(int)10e5];

bool check(int d) {
    int reqAdditional = 0;
    for(int i=0; i+1<N; i++)
        reqAdditional += (sessions[i+1] - sessions[i] - 1)/d;
    if (reqAdditional<=K)
        return 1;
    return 0;
}

int binsearch(int lo, int hi) {
    while (lo<hi) {
        int mid = (lo+hi)/2;
        if (check(mid))
            hi=mid;
        else
            lo=mid+1;
    }
    return lo;
}

int32_t main() {
    int tc, t;
    cin >> tc;
    for (t = 0; t<tc; t++) {
        cin >> N >> K;
        //cout << N << K;
        //vector<int> sessions(N);
        for (int i=0; i<N; i++)
            cin >> sessions[i];
        int ans = binsearch(1, 10e9);
        cout << "Case #" << t+1 << ": " << ans << endl;
    }
}
