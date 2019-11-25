#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int n, arr[3 * maxn];
long long brr[3 * maxn], dp[3][3 * maxn];

long long solve(int isChanged, int idx)
{
    if (idx == n)
        return 0;

    if (dp[isChanged][idx] != -1)
        return dp[isChanged][idx];

    long long ret = LONG_LONG_MAX;

    for (int i = 0; i < 3; ++i)
    {
        if (idx == 0 || arr[idx] + i != arr[idx - 1] + isChanged)
            ret = min(ret, brr[idx] * i + solve(i, idx + 1));
    }

    return dp[isChanged][idx] = ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--)
    {
        cin >> n;

        for (int i = 0; i < n; ++i)
            dp[0][i] = dp[1][i] = dp[2][i] = -1;

        for (int i = 0; i < n; ++i)
            cin >> arr[i] >> brr[i];

        cout << solve(0, 0) << endl;
    }

    return 0;
}