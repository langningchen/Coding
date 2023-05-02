#include <bits/stdc++.h>
using namespace std;
int main()
{
    srand(time(NULL));
    freopen("missing.in", "w", stdout);
    cout << 100 << " " << rand() % 100 + 1 << endl;
    for (int i = 0; i < 100; i++)
        cout << rand() % 100 + 1 << " ";
    cout << endl;
    return 0;
}
