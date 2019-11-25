#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

string str;

bool mark[(1 << 20) + 1];
int n, k, dp[(1 << 20) + 1], cnt[20][20];

int solve(int mask, int pos)
{
    if (pos == k)
        return dp[mask] = 0;

    if (mark[mask])
        return dp[mask];

    mark[mask] = true;

    int ret = INT_MAX;

    for (int i = 0; i < k; ++i)
    {
        if (!(mask & (1 << i)))
        {
            int val = 0;

            for (int j = 0; j < k; ++j)
            {
                if (mask & (1 << j))
                    val += (pos + 1) * cnt[i][j];
                else
                    val -= (pos + 1) * cnt[i][j];
            }

            ret = min(ret, val + solve(mask | (1 << i), pos + 1));
        }
    }

    return dp[mask] = ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k >> str;

    for (int i = 1; i < n; ++i)
    {
        int u = str[i] - 97;
        int v = str[i - 1] - 97;

        if (str[i] != str[i - 1])
            ++cnt[u][v], ++cnt[v][u];
    }

    cout << solve(0, 0) << endl;

    return 0;
}