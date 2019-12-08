#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int n, m, k;
bool mark[5001][5001];
long long sum[5001], dp[5001][5001];

long long solve(int idx, int need)
{
    if (need == 0)
        return 0;

    if (idx == n)
        return 0;

    if (mark[idx][need])
        return dp[idx][need];

    mark[idx][need] = true;

    long long ret = solve(idx + 1, need);

    if (idx + m < n)
        ret = max(ret, sum[idx + m] - (idx ? sum[idx - 1] : 0) + solve(idx + m + 1, need - 1));

    return dp[idx][need] = ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k, --m;

    for (int i = 0; i < n; ++i)
    {
        cin >> sum[i];

        if (i)
            sum[i] += sum[i - 1];
    }

    cout << solve(0, k) << endl;

    return 0;
}