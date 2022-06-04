#include <iostream>
#include <algorithm>
using namespace std;
const int R = 11;
int n, cnt[R], x;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        cnt[x]++;
    }
    cout << *max_element(cnt + 1, cnt + R) - *min_element(cnt + 1, cnt + R) << endl;
    return 0;
}
