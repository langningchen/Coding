#include <bits/stdc++.h>
using namespace std;
const int N = 200000;
int n, man[N], woman[N];
string gender[N];
int main()
{
    freopen("victory.in", "r", stdin);
    freopen("victory.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> gender[i];
    int m = 0, w = 0;
    for (int i = 0; i < n; i++)
        if (gender[i] == "man")
            cin >> man[m++];
        else
            cin >> woman[w++];
    sort(man, man + m);
    sort(woman, woman + w);
    for (int i = m - 1; i >= 0; i--)
        cout << man[i] << " ";
    for (int i = 0; i <= w - 1; i++)
        cout << woman[i] << " ";
    return 0;
}
