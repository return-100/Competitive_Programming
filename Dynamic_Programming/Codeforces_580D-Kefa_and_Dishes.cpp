#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool mark[18][(1 << 18) + 1];
int n, m, k;
long long arr[18], crr[18][18], dp[18][(1 << 18) + 1];

long long solve(int idx, int mask)
{
    if (__builtin_popcount(mask) == m)
        return 0;

    if (mark[idx][mask])
        return dp[idx][mask];

    mark[idx][mask] = true;

    long long ret = 0;

    for (int i = 0; i < n; ++i)
    {
        if (!(mask & (1 << i)))
            ret = max(ret, arr[i] + (mask == 0 ? 0 : crr[idx][i]) + solve(i, mask | (1 << i)));
    }

    return dp[idx][mask] = ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    for (int i = 0; i < k; ++i)
    {
        int x, y, c;
        cin >> x >> y >> c;
        crr[x - 1][y - 1] = c;
    }

    cout << solve(0, 0) << endl;

    return 0;
}