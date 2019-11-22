#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool mark[maxn];
int n, m, dp[maxn];
pair<int, int> arr[88];

int solve(int pos)
{
    if (pos > m)
        return 0;

    if (mark[pos])
        return dp[pos];

    mark[pos] = true;

    int l, r, del, ret = m - pos + 1;
    
    for (int i = 0; i < n; ++i)
    {
        l = arr[i].first - arr[i].second;
        r = arr[i].first + arr[i].second;

        if (pos <= r)
        {
            if (pos >= l)
                ret = min(ret, solve(r + 1));
            else
                ret = min(ret, l - pos + solve(r + l - pos + 1));
        }
    }

    return dp[pos] = ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        cin >> arr[i].first >> arr[i].second;

    sort(arr, arr + n);

    cout << solve(1) << endl;

    return 0;
}