#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;
const long long mod = 1e9 + 7;

int n, k, arr[222], dp[222][222][1111];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    sort(arr, arr + n);

    for (int i = n; i >= 0; --i)
    {
        for (int opened = n; opened >= 0; --opened)
        {
            for (int imbalance = 0; imbalance <= k; ++imbalance)
            {
                long long ret = 0;
                int cur = opened * (i > 0 ? arr[i] - arr[i - 1] : 0) + imbalance;

                if (i == n)
                    dp[i][opened][imbalance] = (opened ? 0 : 1);
                else if (cur <= k)
                {
                    if (opened > 0)
                        ret += ((__int64) dp[i + 1][opened - 1][cur] * (__int64) opened) % mod;

                    ret += dp[i + 1][opened][cur] % mod;
                    ret += dp[i + 1][opened + 1][cur] % mod;
                    ret += ((__int64)dp[i + 1][opened][cur] * (__int64)opened) % mod;

                    dp[i][opened][imbalance] = ret % mod;
                }
            }
        }
    }

    cout << dp[0][0][0] << endl;

    return 0;
}