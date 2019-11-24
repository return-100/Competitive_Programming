#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;
const long long mod = 998244353;

bool isGood[1111];
int n, arr[1111];
long long ans, fact[1111], dp[1111];

long long bigMod(long long base, long long pow)
{
    long long ret = 1;

    while (pow)
    {
        if (pow & 1)
            ret *= base, ret %= mod;

        base *= base, base %= mod;
        pow >>= 1;
    }

    return ret;
}

long long modInverse(long long base)
{
    return bigMod(base, mod - 2);
}

long long ncr(int n, int r)
{
    long long ret = fact[n];
    ret = (ret * modInverse(fact[r])) % mod;
    ret = (ret * modInverse(fact[n - r])) % mod;

    return ret % mod;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fact[0] = 1;

    for (int i = 1; i < 1111; ++i)
        fact[i] = (i * fact[i - 1]) % mod;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];

        if (arr[i] > 0 && arr[i] <= n - i - 1)
            isGood[i] = true;
    }

    for (int i = n - 1; i >= 0; --i)
    {
        dp[i] = dp[i + 1];

        if (!isGood[i])
            continue;

        for (int j = i + arr[i]; j < n; ++j)
        {
            long long cur = ncr(j - i - 1, arr[i] - 1);
            dp[i] = (dp[i] + cur + cur * dp[j + 1]) % mod;
        }
    }

    cout << dp[0] % mod << endl;

    return 0;
}