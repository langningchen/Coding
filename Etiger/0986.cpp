#include <bits/stdc++.h>
using namespace std;
const int N = 50050;
const int INF = 0x7FFFFFF;
int n, m, dst[N], vst[N];
vector<int> to[N];
vector<int> w[N];
void add(int a, int b, int c) {
}
void dijkstra() {
	while (1) {
		int MinValue = INF;
		int MinIndex = -1;
		for (int i = 1; i <= n; i++) {
			if (!vst[i] && dst[i] < MinValue) {
				MinIndex = i;
				MinValue = dst[i];
			}
		}
		if (MinIndex == -1) {
			break;
		}
		vst[MinIndex] = true;
		for (int i = 0; i < to[MinIndex].size(); i++) {
			int v = to[MinIndex][i];
			dst[v] = min(dst[v], dst[MinIndex] + w[MinIndex][i]);
		}
	}
}
int main() {
//	freopen("bonus.in", "r", stdin);
//	freopen("bonus.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 2; i <= n; i++) {
		dst[i] = INF;
	}
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);	
		to[a].push_back(b);
		w[a].push_back(c);
	}
	dijkstra();
	cout << dst[2] << endl;
	return 0;
}

