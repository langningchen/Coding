#include <bits/stdc++.h>
using namespace std;
int deg[100005];
int T;
int main() {
	cin >> T;
	for (int i = 0; i < T; i++) {
		int n;
		cin >> n;
		memset(deg, 0, sizeof(deg));
		for(int i = 0; i < n - 1; i++) {
			int u, v;
			cin >> u >> v;
			deg[u]++;
			deg[v]++;
		}
		int flag = 0;
		for(int i = 0; i < n; i++) {
			if (deg[i] % 2 != 0) {
			    flag = 1;
			}
		}
		cout << (flag ? "Hifuu" : "Luna") << endl;
	}
}
