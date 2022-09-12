#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
const int INF = 0x7FFFFFFF;
struct node {
    int v, w;
};
int n, m, s, vst[N], ans[N];
vector<node> to[N];
void Do() {
    while (1) {
        int MinIndex = -1, MinValue = INF;
        for (int i = 0; i < n; i++) {
            if (!vst[i] && ans[i] < MinValue) {
                MinIndex = i;
                MinValue = ans[i];
            }
        }
        if (MinIndex = -1) break;
        vst[MinIndex] = 1;
        for (vector<node>::iterator vit = to[MinIndex].begin(); vit != to[MinIndex].end(); vit++) {
            ans[vit->v] = min(ans[vit->v], ans[MinIndex] + vit->w);
        }
	    for (int i = 0; i < n; i++) {
	        cout << ans[i] << " ";
	    }
	    cout << endl;
    }
}
int main() {
    cin >> n >> m >> s;
    fill(ans, ans + n, INF);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        to[u - 1].push_back((node){v - 1, w});
    }
    ans[s - 1] = 0;
    vst[s - 1] = 1;
    Do();
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
