#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, a[N], b[N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    auto Do = [](int a[], int b[]) -> int
    {
        int LeftA = 1, RightA = n, LeftB = 1, RightB = n, Answer = 0;
        while (LeftA <= RightA && LeftB <= RightB)
            if (a[LeftA] > b[LeftB])
            {
                Answer += 2;
                LeftA++;
                LeftB++;
            }
            else if (a[RightA] > b[RightB])
            {
                Answer += 2;
                RightA--;
                RightB--;
            }
            else
            {
                Answer += a[LeftA] == b[RightB];
                LeftA++;
                RightB--;
            }
        return Answer;
    };
    printf("%d %d\n", Do(a, b), 2 * n - Do(b, a));
}
