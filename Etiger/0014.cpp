#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin >> n;
    if (n >= 100)
        cout << n * 7 << endl;
    else if (n >= 50)
        cout << n * 8 << endl;
    else
        cout << n * 10 << endl;
    return 0;
}