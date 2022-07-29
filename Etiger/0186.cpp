#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
struct people
{
	int id, score;
} f[N];
int n, m;
bool cmp(const people &a, const people &b)
{
	if (a.score > b.score)
		return true;
	if (a.score < b.score)
		return false;
	if (a.id < b.id)
		return true;
	if (a.id > b.id)
		return false;
}
int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> f[i].id >> f[i].score;
	sort(f, f + n, cmp);
	int start = (int)floor(m * 1.5) - 1;
	while (start + 1 < n && f[start].score == f[start + 1].score)
		start++;
	cout << f[start].score << " " << start + 1 << endl;
	for (int i = 0; i <= start; i++)
		cout << f[i].id << " " << f[i].score << endl;
	return 0;
}
