#include <iostream>
using namespace std;
const int SIZE = 105;
int matrix[SIZE][SIZE], rowsum[SIZE][SIZE], m, n, i, j, first, last, area, ans;
int main()
{
    cin >> m >> n;
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            cin >> matrix[i][j];
    ans = matrix[m][n];
    for (i = 1; i <= m; i++)
        rowsum[i][0] = 0;
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            rowsum[i][j] = rowsum[i][j - 1] + matrix[i][j];
    for (first = 1; first <= n; first++)
        for (last = first; last <= n; last++)
        {
            area = 0;
            for (i = 1; i <= m; i++)
            {
                area += rowsum[i][last] - rowsum[i][first] + matrix[i][first];
                if (area > ans)
                    ans = area;
                if (area < 0)
                    area = 0;
            }
        }
    cout << ans << endl;
    return 0;
}
