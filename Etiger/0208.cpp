#include <iostream>
using namespace std;
double s, k;
int n = 1;
int main() {
    cin >> k;
    while (s <= k)
    {
        s += 1.0 / n;
        n++;
    }
    n--;
    cout << n;
    return 0;
}
