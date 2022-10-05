#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("snail.in", "w", stdout);
    srand(time(0));
    cout << 200000 << " " << 1000000000 << " " << 1000000000 << endl;
    for (int i = 1; i <= 200000; i++)
        cout << rand() % 1000000000 + 1 << " ";
    cout << endl;
    cout << 200000 << endl;
    for (int i = 1; i <= 200000; i++)
        cout << rand() % 1000000000 + 1 << endl;
    return 0;
}