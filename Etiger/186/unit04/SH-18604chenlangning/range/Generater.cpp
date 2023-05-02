#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("range.in", "w", stdout);
    srand(time(NULL));
    cout << 10000 << endl;
    for (int i = 0; i < 10000; i++)
        cout << (rand() % 1000 + 1) << " ";
    cout << endl;
    return 0;
}
