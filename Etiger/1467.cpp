#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, x[N];
int Partition(int A[], int left, int right)
{
	int p = round(1.0 * rand() / RAND_MAX * (right - left) + left);
	swap(A[p], A[left]);
	int temp = A[left];
	while (left < right)
	{
		while (left < right && A[right] > temp)
			right--;
		A[left] = A[right];
		while (left < right && A[left] <= temp)
			left++;
		A[right] = A[left];
	}
	A[left] = temp;
	return left;
}

void quickSort(int A[], int left, int right)
{
	if (left < right)
	{
		int pos = Partition(A, left, right);
		quickSort(A, left, pos - 1);
		quickSort(A, pos + 1, right);
	}
}

int main()
{
	srand((unsigned)time(NULL));
	freopen("intelligence.in", "r", stdin);
	freopen("intelligence.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> x[i];
	quickSort(x, 0, n - 1);
	for (int i = n - 1; i >= 0; i--)
		cout << x[i] << " ";
	cout << endl;
	return 0;
}
