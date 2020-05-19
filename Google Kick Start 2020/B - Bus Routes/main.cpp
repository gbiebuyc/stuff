#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int N;
ll D;

int main() {
    int t, tc;
    cin >> tc;
    for (t=0; t<tc; t++) {
        cin >> N >> D;
        ll b[1000];
        for (int i=0; i<N; i++) {
            cin >> b[i];
        }
        for (int i=N-1; i>=0; i--) {
            D = D/b[i]*b[i];
        }
        cout << "Case #" << t+1 << ": " << D << endl;
    }
}
