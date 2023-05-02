#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, ans;
bool x[N];
int main()
{
    freopen("photoshoot.in", "r", stdin);
    freopen("photoshoot.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        x[i] = (c == 'G' ? 0 : 1);
    }
    bool Temp = true;
    int Start = 0;
    for (int i = 1; i < n; i++)
    {
        if (i > 2 && Start == 0 && x[i - 2] != x[i - 3])
            Temp = false;
        if (i % 2 == 1)
        {
            if (x[i - 1] == 0 && x[i] == 1)
            {
                if (Start == 0)
                    Start = i;
            }
            else if (Start != 0)
            {
                Start = 0;
                if (i == 3)
                    ans += 1;
                else if (Temp)
                    ans += 2;
                else
                    ans += 3;
                if ((i - 2) / 2 > 0)
                {
                    bool tmp = true;
                    for (int j = 0; j < (i - 2) / 2; j++)
                        if (x[j] != x[i - 2 - j])
                        {
                            tmp = false;
                            break;
                        }
                    if (tmp)
                        ans--;
                }
            }
        }
    }
    if (Start != 0)
    {
        Start = 0;
        if (n - 1 == 1)
            ans += 1;
        else if (Temp)
            ans += 2;
        else
            ans += 3;
        bool tmp = true;
        for (int j = 0; j < (n - 3) / 2; j++)
            if (x[j] != x[n - 3 - j])
            {
                tmp = false;
                break;
            }
        if (tmp)
            ans--;
    }
    cout << ans << endl;
    return 0;
}