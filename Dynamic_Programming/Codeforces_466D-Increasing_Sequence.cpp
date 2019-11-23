#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;
const long long mod = 1e9 + 7;

bool mark[2222][2222];
int n, h, arr[2222];
long long dp[2222][2222];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> h;

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    for (int i = n; i >= 0; --i)
    {
        for (int opened = n; opened >= 0; --opened)
        {
            if (i == n)
                dp[i][opened] = (opened ? 0 : 1);

            if (arr[i] + opened == h)
            {
                dp[i][opened] += dp[i + 1][opened] % mod;
                dp[i][opened] += ((opened ? dp[i + 1][opened - 1] : 0) * opened) % mod;
            }

            if (arr[i] + opened + 1 == h)
            {
                dp[i][opened] += dp[i + 1][opened + 1] % mod;
                dp[i][opened] += (dp[i + 1][opened] * (opened + 1)) % mod;
            }
        }
    }

    cout << dp[0][0] % mod << endl;

    return 0;
}