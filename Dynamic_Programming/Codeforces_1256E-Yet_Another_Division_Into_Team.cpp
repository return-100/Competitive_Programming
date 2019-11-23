#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int n;
pair<long long, int> arr[2 * maxn];
long long res, ans[2 * maxn], dp[3][2 * maxn];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i].first, arr[i].second = i;
        dp[0][i] = dp[1][i] = dp[2][i] = 1e16;
    }

    sort(arr, arr + n);

    for (int i = n - 3; i >= 0; --i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int nxt = i + j + 2;

            if (nxt < n)
                dp[j][i] = (arr[nxt].first - arr[i].first) + min(dp[0][nxt + 1], min(dp[1][nxt + 1], dp[2][nxt + 1]));
        }
    }

    cout << (res = min(dp[0][0], min(dp[1][0], dp[2][0]))) << " ";

    int idx = 0, cur = 1, nxt;

    while (idx <= n - 3)
    {
        if (dp[0][idx] == res)
            nxt = idx + 2;
        else if (dp[1][idx] == res)
            nxt = idx + 3;
        else
            nxt = idx + 4;

        for (int i = idx; i <= nxt; ++i)
            ans[arr[i].second] = cur;

        res -= (arr[nxt].first - arr[idx].first), idx = nxt + 1, ++cur;
    }

    cout << cur - 1 << endl;

    for (int i = 0; i < n; ++i)
        cout << ans[i] << " ";

    cout << endl;

    return 0;
}