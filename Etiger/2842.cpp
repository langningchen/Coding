#include <bits/stdc++.h>
using namespace std;
const int N = 8005;
struct Node
{
	int index;
	long long value;
};
bool cmp(Node cmp1, Node cmp2)
{
	if (cmp1.value < cmp2.value)
		return true;
	if (cmp1.value > cmp2.value)
		return false;
	if (cmp1.index < cmp2.index)
		return true;
	if (cmp1.index > cmp2.index)
		return false;
	return 0;
}
long long n, Q;
Node a[N];
long long f[N];
void add(int t, int v)
{
	if (a[f[t]].value == v)
		return;
	int x = 0;
	int i = 0;
	Node temp;
	temp.index = t;
	temp.value = v;
	x = f[t];
	if (cmp(temp, a[0]))
	{
		i = -1;
	}
	else
	{
		for (; i < n - 1; i++)
		{
			if (cmp(a[i], temp) && cmp(temp, a[i + 1]))
				break;
		}
	}
	if (x <= i)
	{
		for (int j = x; j < i; j++)
		{
			a[j] = a[j + 1];
			f[a[j].index] = j;
		}
		a[i] = temp;
		f[temp.index] = i;
	}
	if (i + 1 <= x)
	{
		for (int j = x; j > i + 1; j--)
		{
			a[j] = a[j - 1];
			f[a[j].index] = j;
		}
		a[i + 1] = temp;
		f[temp.index] = i + 1;
	}
}
void swap(int x, int y)
{
	Node temp;
	temp = a[x];
	a[x] = a[y];
	a[y] = temp;
	f[a[x].index] = x;
	f[a[y].index] = y;
}
void sort(int l, int r)
{
	if (l >= r)
		return;
	int m = l + 1;
	for (int i = l + 1; i <= r; i++)
		if (cmp(a[i], a[l]))
		{
			swap(i, m);
			m++;
		}
	swap(l, m - 1);
	sort(l, m - 2);
	sort(m, r);
}
int query(int x)
{
	return f[x];
}
int main()
{
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	cin >> n >> Q;
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		a[i].index = i;
		a[i].value = temp;
		f[i] = i;
	}
	sort(0, n - 1);
	for (int i = 0; i < Q; i++)
	{
		int t;
		cin >> t;
		if (t == 1)
		{
			long long x, v;
			cin >> x >> v;
			add(x - 1, v);
		}
		else
		{
			int x;
			cin >> x;
			cout << query(x - 1) + 1 << endl;
		}
	}
	return 0;
}
