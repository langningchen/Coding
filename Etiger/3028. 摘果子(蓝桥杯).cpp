#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, -1, 1, 0};
int m, n, Map[N][N], vst[N][N];
void dfs(int x, int y) {
//	cout << x << " " << y << endl;
    for (int i = 0; i < 4; i++) {
    	int nx = x + dx[i];
    	int ny = y + dy[i];
		if (nx >= 0 && nx < m && ny >= 0 && ny < n && !vst[nx][ny] && Map[nx][ny] == 1) {
			vst[nx][ny] = 1;
			dfs(nx, ny);
		}
	}
}
int main() {
	int Startx, Starty;
	cin >> m >> n;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 6) {
				Startx = i;
				Starty = j;
			}
		}
	}
	vst[Startx][Starty] = 1;
	dfs(Startx, Starty);
	int ans = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (vst[i][j]) {
				ans++;
			}
		}
    }
	cout << ans << endl;
	return 0;
}
