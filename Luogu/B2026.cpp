#include <bits/stdc++.h>
using namespace std;
double a, b;
int main()
{
    cin >> a >> b;
    cout << a - (int)(a / b) * b << endl;
    return 0;
}