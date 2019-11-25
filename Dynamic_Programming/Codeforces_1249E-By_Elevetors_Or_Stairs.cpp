#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int n, c, arr[2 * maxn], brr[2 * maxn], dp[2][2 * maxn];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> c;

    for (int i = 0; i < n - 1; ++i)
        cin >> arr[i];

    for (int i = 0; i < n - 1; ++i)
        cin >> brr[i];

    dp[0][0] = 0;
    dp[1][0] = c;

    for (int i = 1; i < n; ++i)
    {
        dp[0][i] = arr[i - 1] + dp[0][i - 1];
        dp[0][i] = min(dp[0][i], arr[i - 1] + dp[1][i - 1]);
        dp[1][i] = brr[i - 1] + dp[1][i - 1];
        dp[1][i] = min(dp[1][i], c + brr[i - 1] + dp[0][i - 1]);
    }

    for (int i = 0; i < n; ++i)
        cout << min(dp[0][i], dp[1][i]) << " ";

    cout << endl;

    return 0;
}