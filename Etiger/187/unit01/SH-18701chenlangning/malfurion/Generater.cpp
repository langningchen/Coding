#include <bits/stdc++.h>
using namespace std;
int main()
{
    srand(time(NULL));
    freopen("malfurion.in", "w", stdout);
    cout << 100000 << endl;
    for (int i = 0; i < 100000; i++)
        cout << rand() % 1000000000 + 1 << " ";
    cout << endl;
    return 0;
}
