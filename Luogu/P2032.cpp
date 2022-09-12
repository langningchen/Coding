#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
int n, k, a[N], q[N];
int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int head = 0, tail = 0;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && q[head] + k <= i)
            head++;
        while (head < tail && a[q[tail - 1]] < a[i])
            tail--;
        q[tail] = i;
        tail++;
        if (i >= k)
            cout << a[q[head]] << endl;
    }
    return 0;
}