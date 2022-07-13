#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N];
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    *(max_element(a, a + n)) = 100001;
    *(min_element(a, a + n)) = 100001;
    for (int i = 0; i < n; i++)
    {
        if (a[i] != 100001)
            cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
