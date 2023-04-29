#include <bits/stdc++.h>
using namespace std;
int n;
void m(int n)
{
    if (n == 0)
        return;
    char c;
    cin >> c;
    m(n - 1);
    cout << c << " ";
}
int main()
{
    cin >> n;
    m(n);
    return 0;
}
