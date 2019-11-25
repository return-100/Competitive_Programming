#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int n, ans, dp[3 * maxn];
vector <int> vec[3 * maxn];

void dfs(int u, int par)
{
    int deg = 0, mx1 = 0, mx2 = 0;

    for (int i = 0; i < vec[u].size(); ++i)
    {
        int v = vec[u][i];

        if (v != par)
        {
            dfs(v, u), ++deg;

            if (mx1 < dp[v])
                mx2 = mx1, mx1 = dp[v];
            else if (mx2 < dp[v])
                mx2 = dp[v];
        }
    }

    ans = max(ans, deg + mx1 + mx2 - (par == u));
    dp[u] = max(1, deg + mx1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--)
    {
        cin >> n, ans = 2;

        for (int i = 0; i < n; ++i)
            vec[i].clear(), dp[i] = 0;

        for (int i = 0; i < n - 1; ++i)
        {
            int u, v;

            cin >> u >> v;
            vec[u - 1].push_back(v - 1);
            vec[v - 1].push_back(u - 1);
        }

        for (int i = 0; i < n; ++i)
        {
            if (vec[i].size() > 1)
            {
                dfs(i, i);
                break;
            }
        }

        cout << ans << endl;
    }

    return 0;
}