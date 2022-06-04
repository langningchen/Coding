#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
const long long N = 1005;
const long long INF = 0x7FFFFFFF;
const long long dy[3] = {1, 0, 0};
const long long dx[3] = {0, -1, 1};
long long m, n, a[N][N], vst[N][N], f[N][N];
void Output() {
	system("cls");
	for (long long i = 0; i < n; i++) {
		for (long long j = 0; j < m; j++) {
			cout << vst[i][j] << "\t";
		}
		cout << endl;
	}
	_getch();
}
long long dfs(long long x, long long y) {
	Output();
	if (x == n - 1 && y == m - 1) {
		return a[x][y];
	}
//	if (f[x][y] != -INF) {
//		return f[x][y];
//	}
	long long ans = -INF;
	for (long long i = 0; i < 3; i++) {
		long long nx = x + dx[i];
		long long ny = y + dy[i];
		if (nx < 0 || nx >= n || ny < 0 || ny >= m || vst[nx][ny] != 0) {
			continue;
		}
		vst[nx][ny] = vst[x][y] + a[x][y];
        ans = max(ans, dfs(nx, ny));
        vst[nx][ny] = 0;
	}
	Output();
	f[x][y] = a[x][y] + ans;
	return f[x][y];
}
int main() {
//	freopen("number.in", "r", stdin);
//	freopen("number.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			f[i][j] = -INF;
		}
	}
	for (long long i = 0; i < n; i++) for (long long j = 0; j < m; j++) cin >> a[i][j];
	vst[0][0] = 1;
	cout << dfs(0, 0) << endl;
	return 0;
}
