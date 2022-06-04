#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
const int INF = 1000000;
int n, A[N][N], ans, ok[N], d[N];
void Dijkstra() {
    fill(ok, ok + n + 1, 0);
    fill(d, d + n + 2, INF);
    d[1] = 0;
    for (int k = 1; k <= n; k++) {
        int now = n + 1;
        for (int j = 1; j <= n; j++)
            if (!ok[j] && d[j] < d[now]) now = j;
        ok[now] = 1;
        for (int j = 1; j <= n; j++)
            d[j] = min(d[j], d[now] + A[now][j]);
    }
} 
int main() {
    freopen("meeting.in","r",stdin);
    freopen("meeting.out","w",stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            A[i][j] = (j * 200 + i * i) % 233;
    Dijkstra();
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += d[i];
    cout << ans << endl;
    return 0;
}
