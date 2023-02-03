#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50005;
ll T, n, a[N], Counter, Temp[N];
void MergeSort(ll *ArrayToSort, ll LeftBound, ll RightBound)
{
    if (LeftBound == RightBound)
        return;
    ll MiddleBound = (LeftBound + RightBound) / 2;
    MergeSort(ArrayToSort, LeftBound, MiddleBound);
    MergeSort(ArrayToSort, MiddleBound + 1, RightBound);
    ll LeftArrayPointer = LeftBound;
    ll RightArrayPointer = MiddleBound + 1;
    ll TempSize = 0;
    while (LeftArrayPointer <= MiddleBound && RightArrayPointer <= RightBound)
        if (ArrayToSort[LeftArrayPointer] <= ArrayToSort[RightArrayPointer])
            Temp[TempSize++] = ArrayToSort[LeftArrayPointer++];
        else
        {
            Temp[TempSize++] = ArrayToSort[RightArrayPointer++];
            Counter += MiddleBound - LeftArrayPointer + 1;
        }
    while (LeftArrayPointer <= MiddleBound)
        Temp[TempSize++] = ArrayToSort[LeftArrayPointer++];
    while (RightArrayPointer <= RightBound)
        Temp[TempSize++] = ArrayToSort[RightArrayPointer++];
    for (int i = LeftBound; i <= RightBound; i++)
        a[i] = Temp[i - LeftBound];
}
int main()
{
    scanf("%lld", &T);
    while (T--)
    {
        Counter = 0;
        scanf("%lld", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%lld", &a[i]);
        }
        MergeSort(a, 0, n - 1);
        printf("%lld\n", Counter);
    }
    return 0;
}
