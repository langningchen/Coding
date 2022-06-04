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
    ll l = 1;                        //��ʼ����˵㣬���𰸿��ܵ���Сֵ
    ll r = *max_element(x, x + n);    //��ʼ���Ҷ˵㣬���𰸿��ܵ����ֵ
    ll ans = 0;                        //��ʼ���𰸾���С
    while (l <= r) {                //�������ڴ����ҷ�Χ
        ll mid = l + (r - l) / 2;    //���ַ�Χ���е�Ϊmid
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
