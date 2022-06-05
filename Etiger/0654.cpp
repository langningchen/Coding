#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int x[100000], m, n, cnt, ans;
bool OK(ll len) {
    ll cnt = 0;
    for (ll i = 0; i < n; i++) {
        cnt += x[i] / len;
        if (cnt >= m) return 1;
    }
    return 0;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    ll l = 1;                        //初始化左端点，即答案可能的最小值
    ll r = *max_element(x, x + n);    //初始化右端点，即答案可能的最大值
    ll ans = 0;                        //初始化答案尽量小
    while (l <= r) {                //当还存在待查找范围
        ll mid = l + (r - l) / 2;    //二分范围：中点为mid
        if (OK(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    cout << ans;
    return 0;
}
