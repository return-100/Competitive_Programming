#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool mark[3][2 * maxn];
int n, k1, k2, k3, var, arr[2 * maxn], dp[3][2 * maxn];

int solve(int idx, int pos)
{
    if (idx > 2)
        return 2 * maxn;

    if (pos == n)
        return 0;

    if (mark[idx][pos])
        return dp[idx][pos];

    mark[idx][pos] = true;

    int ret = solve(idx + 1, pos);
    
    if (arr[pos] == idx)
        ret = min(ret, solve(idx, pos + 1));
    else
        ret = min(ret, 1 + solve(idx, pos + 1));

    return dp[idx][pos] = ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> k1 >> k2 >> k3;
    n = k1 + k2 + k3;

    for (int i = 0; i < k1; ++i)
        cin >> var, arr[var - 1] = 0;

    for (int i = 0; i < k2; ++i)
        cin >> var, arr[var - 1] = 1;

    for (int i = 0; i < k3; ++i)
        cin >> var, arr[var - 1] = 2;

    cout << solve(0, 0) << endl;

    return 0;
}