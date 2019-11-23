#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int n;
bool mark[5555][5555];
long long dp[5555][5555];
pair<int, long long> arr[5555];

long long solve(int idx, int cnt)
{
    if (idx == 0)
    {
        if (cnt >= arr[idx].first)
            return 0;
        else
            return arr[idx].second;
    }

    if (mark[idx][cnt])
        return dp[idx][cnt];

    mark[idx][cnt] = true;
    dp[idx][cnt] = 1e16;

    if (cnt >= arr[idx].first)
        dp[idx][cnt] = solve(idx - 1, cnt + 1);
    else if (idx + cnt >= arr[idx].first)
        dp[idx][cnt] = solve(idx - 1, cnt);
    
    dp[idx][cnt] = min(dp[idx][cnt], arr[idx].second + solve(idx - 1, cnt + 1));

    return dp[idx][cnt];
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
            cin >> arr[i].first >> arr[i].second;

        sort(arr, arr + n);

        cout << solve(n - 1, 0) << endl;

        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= n; ++j)
                mark[i][j] = false;
        }
    }

    return 0;
}