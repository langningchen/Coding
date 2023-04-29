#include <bits/stdc++.h>
using namespace std;
int l, r, ans;
int count2(int x)
{
    string tmp = to_string(x);
    int cnt = 0;
    for (int i = 0; i < tmp.size(); i++)
        if (tmp[i] == '2')
            cnt++;
    return cnt;
}
int main()
{
    cin >> l >> r;
    for (int i = l; i <= r; i++)
        ans += count2(i);
    cout << ans << endl;
    return 0;
}