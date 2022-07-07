#include <bits/stdc++.h>
using namespace std;
void getSG() {
	for (int x = 1; x < R; x++) {
		fill(ok, ok + R, 0);
		for (int i = 1; i <= m; i++)
			if (x - b[i] >= 0)
				ok[sg[x - b[i]]] = 1;
		for (int k = 0; k <= 1000; k++)
			if (!ok[k]) {
				sg[x] = k;
				break;
			}
	}
}
int main() {
	freopen("stomach.in", "r", stdin);
	freopen("stomach.out", "w", stdout);
	return 0;
}

