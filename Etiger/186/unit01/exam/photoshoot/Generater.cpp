#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("photoshoot.in", "w", stdout);
    srand(time(NULL));
    cout << 200000 << endl;
    for (int i = 0; i < 200000; i++)
        cout << ((rand() % 2) ? "G" : "H");
    cout << endl;
    return 0;
}