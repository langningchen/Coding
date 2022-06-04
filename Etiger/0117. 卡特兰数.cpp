#include <iostream>
using namespace std;
long long h(long long k)
{
    return k < 2 ? 1 : h(k - 1) * (4 * k - 2) / (k + 1);
}
int main() {
    int n;
    cin >> n;
    cout << h(n);
    return 0;
}
