#include <bits/stdc++.h>
using namespace std;
const int N = 400005;
const int INF = 0x7FFFFFFF;
int n, s[N], x[N], leftMax[N], rightMax[N], preMax[N], postMax[N], leftMin[N], rightMin[N], preMin[N], postMin[N];
void solveMax()
{
	leftMax[1] = x[1];
	for (int i = 2; i <= n; i++)
		leftMax[i] = max(leftMax[i - 1], 0) + x[i];
	preMax[1] = leftMax[1];
	for (int i = 2; i <= n; i++)
		preMax[i] = max(preMax[i - 1], leftMax[i]);
	rightMax[n] = x[n];
	for (int i = n - 1; i >= 1; i--)
		rightMax[i] = max(rightMax[i + 1], 0) + x[i];
	postMax[n] = rightMax[n];
	for (int i = n - 1; i >= 1; i--)
		postMax[i] = max(postMax[i + 1], rightMax[i]);
}
void solveMin()
{
	leftMin[1] = x[1];
	for (int i = 2; i <= n; i++)
		leftMin[i] = min(leftMin[i - 1], 0) + x[i];
	preMin[1] = leftMin[1];
	for (int i = 2; i <= n; i++)
		preMin[i] = min(preMin[i - 1], leftMin[i]);
	rightMin[n] = x[n];
	for (int i = n - 1; i >= 1; i--)
		rightMin[i] = min(rightMin[i + 1], 0) + x[i];
	postMin[n] = rightMin[n];
	for (int i = n - 1; i >= 1; i--)
		postMin[i] = min(postMin[i + 1], rightMin[i]);
}
int main()
{
	freopen("wang.in", "r", stdin);
	freopen("wang.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> x[i];
	int sum = 0;
	for (int i = 1; i <= n; i++)
		sum += x[i];
	solveMax();
	solveMin();
	int ans = -INF;
	for (int i = 1; i <= n - 1; i++)
		ans = max(ans, preMax[i] + postMax[i + 1]);
	for (int i = 1; i <= n - 1; i++)
		ans = max(ans, sum - preMin[i] - postMin[i + 1]);
	cout << ans << endl;
	return 0;
}
