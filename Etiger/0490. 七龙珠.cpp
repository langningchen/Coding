#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int N = 100;
int x[N];
int cnt[N];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i];
    int sum = 0, ans = n + 1;
    int tail = 0, head = 0;
    while(1) {
        while(head < n && sum < 7) {
            int num = x[head++];
            if (num < 1 || num > 7) continue;
            ++cnt[num];
            if (cnt[num] == 1) sum++;
        }
        if (sum < 7) break;
        ans = min(ans, head - tail);
        int num = x[tail++];
        if (num < 1 || num > 7) continue;
        --cnt[num];
        if (cnt[num] == 0) sum--;
    }
    if (ans == n + 1)
        cout << "bye dragon" << endl;
    else
        cout << ans << endl;
    return 0;
}
