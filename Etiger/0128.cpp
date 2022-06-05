#include <iostream>
using namespace std;
long long f(long long x)
{
    return x == 1 ? 1 : x * x + f(x - 1);
}
int main() {
    int n;
    cin >> n;
    cout << f(n);
    return 0;
}
