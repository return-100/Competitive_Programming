#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;
const long long p = 31;
const long long mod = 1e9 + 7;

char str[5001];
long long fhash[5001], rhash[5001], inv[5001], power[5001];
int q, l, r, sz, mark[5001][5001], dp[5001][5001];

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

void preprocess()
{
    power[0] = inv[0] = 1;
    sz = strlen(str);

    for (int i = 1; i < sz; ++i)
        power[i] = (p * power[i - 1]) % mod, inv[i] = modInverse(power[i]) % mod;

    fhash[0] = (str[0] - 96LL);

    for (int i = 1; i < sz; ++i)
        fhash[i] = (fhash[i - 1] + ((str[i] - 96LL) * power[i])) % mod;

    rhash[sz - 1] = (str[sz - 1] - 96LL);

    for (int i = sz - 2, j = 1; i >= 0; --i, ++j)
        rhash[i] = (rhash[i + 1] + ((str[i] - 96LL) * power[j])) % mod;

    
    for (int i = 0; i < sz; ++i)
    {
        for (int j = i; j < sz; ++j)
        {
            long long hashA = (((fhash[j] - (i ? fhash[i - 1] : 0) + mod) % mod) * inv[i]) % mod;
            long long hashB = (((rhash[i] - rhash[j + 1] + mod) % mod) * inv[sz - j - 1]) % mod;

            if (hashA == hashB)
                mark[i][j] = 1;
        }
    }
}

int solve(int l, int r)
{
    if (l > r)
        return 0;

    if (l == r)
        return dp[l][r] = 1;

    if (dp[l][r] != -1)
        return dp[l][r];

    return dp[l][r] = mark[l][r] + solve(l, r - 1) + solve(l + 1, r) - solve(l + 1, r - 1);
}

int main()
{
    memset(dp, -1, sizeof(dp));

    scanf("%s", str);

    preprocess();

    scanf("%d", &q);

    solve(0, sz - 1);

    for (int i = 0; i < q; ++i)
    {
        scanf("%d %d", &l, &r);
        --l, --r;
        printf("%d\n", dp[l][r]);
    }

    return 0;
}