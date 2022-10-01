#include <bits/stdc++.h>
using namespace std;
int x, y;
int main()
{
    cin >> x >> y;
    if (x > -2 && x < 2 && y > -2 && y < 2)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
    return 0;
}