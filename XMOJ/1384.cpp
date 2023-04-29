#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 5005;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll T, n, a[2 * N], aCopy[N], Temp[N], Counter;
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
    for (ll i = LeftBound; i <= RightBound; i++)
        ArrayToSort[i] = Temp[i - LeftBound];
}
int main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld", &n);
        for (ll i = 0; i < n; i++)
        {
            scanf("%lld", &a[i]);
            a[i + n] = a[i];
            aCopy[i] = a[i];
        }
        Counter = 0;
        MergeSort(aCopy, 0, n - 1);
        ll ans = Counter;
        for (ll i = 1; i < n; i++)
        {
            Counter += n - 1 - 2 * a[i - 1];
            ans = min(ans, Counter);
        }
        printf("%lld\n", ans);
    }
    return 0;
}