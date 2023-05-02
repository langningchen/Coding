#include <bits/stdc++.h>
using namespace std;
int main()
{
    srand(time(NULL));
    freopen("cover.in", "w", stdout);
    cout << 100 << endl;
    for (int i = 0; i < 100; i++)
    {
        int a = rand() % 1001;
        int b = rand() % 1001;
        if (a > b)
            swap(a, b);
        cout << a << " " << b << endl;
    }
    return 0;
}
