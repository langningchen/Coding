#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, f[N];
bool x[N];
int main()
{
    // freopen("photoshoot.in", "r", stdin);
    // freopen("photoshoot.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        x[i] = (c == 'G' ? 0 : 1);
    }
    int Counter = 0;
    while (1)
    {
        for (int i = 1; i <= n / 2; i++)
            if (x[i * 2 - 2] == 0 && x[i * 2 - 1] == 0)
                f[i] = f[i - 1];
            else if (x[i * 2 - 2] == 0 && x[i * 2 - 1] == 1)
                f[i] = f[i - 1] + 1;
            else if (x[i * 2 - 2] == 1 && x[i * 2 - 1] == 0)
                f[i] = max(f[i - 1] - 1, 0);
            else if (x[i * 2 - 2] == 1 && x[i * 2 - 1] == 1)
                f[i] = f[i - 1];
        // for (int i = 0; i < n; i++)
        //     cout << i << " " << f[i] << " " << x[i] << endl;
        // cout << endl;
        int ReservePlace = (max_element(f, f + n / 2 + 1) - f);
        if (f[ReservePlace] == 0)
            break;
        for (int i = 0; i < ReservePlace; i++)
            swap(x[i], x[ReservePlace * 2 - i - 1]);
        Counter++;
    }
    cout << Counter << endl;
    return 0;
}