#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
struct student
{
	int id, score;
};
int n;
student f[N];
bool cmp(const student &a, const student &b)
{
	if (a.score > b.score)
		return true;
	if (a.score < b.score)
		return false;
	if (a.id < b.id)
		return true;
	return false;
}
int main()
{
	freopen("rank.in", "r", stdin);
	freopen("rank.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> f[i].score;
		f[i].id = i + 1;
	}
	sort(f, f + n, cmp);
	for (int i = 0; i < n; i++)
	{
		cout << f[i].id << " ";
		cout << f[i].score << endl;
	}
	return 0;
}
