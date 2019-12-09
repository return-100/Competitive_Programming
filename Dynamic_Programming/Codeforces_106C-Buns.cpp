#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool mark[11][1010];
int n, m, c0, d0, arr[11][4], dp[11][1010];

int solve(int idx, int dough)
{
    if (idx == m)
        return (dough / c0) * d0;

    if (mark[idx][dough])
        return dp[idx][dough];

    mark[idx][dough] = true;

    for (int i = 0; (i * arr[idx][1]) <= arr[idx][0]; ++i)
    {
        if (dough >= i * arr[idx][2])
            dp[idx][dough] = max(dp[idx][dough], i * arr[idx][3] + solve(idx + 1, dough - (i * arr[idx][2])));
    }

    return dp[idx][dough];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> c0 >> d0;

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < 4; ++j)
            cin >> arr[i][j];
    }

    cout << solve(0, n) << endl;

    return 0;
}