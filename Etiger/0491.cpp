#include <bits/stdc++.h>
using namespace std;
set<int> day;
const int N = 1005;
int x[N];
int cnt[N];
int main()
{
    int n, k = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        if (!day.count(x[i]))
        {
            day.insert(x[i]);
            k++;
        }
    }
    int sum = 0, ans = n + 1;
    int tail = 0, head = 0;
    while (1)
    {
        while (head < n && sum < k)
        {
            int num = x[head++];
            ++cnt[num];
            if (cnt[num] == 1)
                sum++;
        }
        if (sum < k)
            break;
        ans = min(ans, head - tail);
        int num = x[tail++];
        --cnt[num];
        if (cnt[num] == 0)
            sum--;
    }
    cout << ans << endl;
    return 0;
}
