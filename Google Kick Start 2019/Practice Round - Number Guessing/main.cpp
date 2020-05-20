#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

int main() {
    //ofstream f("errors.txt");
    int t, A, B, N;
    cin>>t;
    while (t--) {
        cin>>A>>B>>N;
        //f<<A<<" "<<B<<" "<<N<<endl;
        for (;;) {
            int guess = ceil((A+B)/2.0);
            //f<<"my guess: "<<guess<<endl;
            cout<<guess<<endl<<flush;
            string s;
            cin>>s;
            //f<<s<<endl;
            if (s=="TOO_BIG")
                B=guess-1;
            else if (s=="TOO_SMALL")
                A=guess;
            else
                break;
        }
    }
}
