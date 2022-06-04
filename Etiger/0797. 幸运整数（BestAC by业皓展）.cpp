#include <iostream>
using namespace std;
typedef long long ll;
bool lucky(ll x) {
    do {
        ll r = x % 10;
        if(r != 5 && r != 8)
            return 0;
        x /= 10;
    } while (x);
    return 1;
}
int main() {
    ll k, n = 5, i = 1;
    cin >> k;
    while(i < k)
    {
        n++;
        if(lucky(n))
            i++;
    }
    cout << n << endl;
    return 0;
}
