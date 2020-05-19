#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N;

int main() {
    int t, tc;
    cin >> tc;
    for (t=0; t<tc; t++) {
        cin >> N;
        int ans = 0;
        int h[100];
        for (int i=0; i<N; i++) {
            cin >> h[i];
            if (i<2)
                continue;
            if (h[i-1]>h[i-2] && h[i-1]>h[i])
                ans++;
        }
        cout << "Case #" << t+1 << ": " << ans << endl;
    }
}
