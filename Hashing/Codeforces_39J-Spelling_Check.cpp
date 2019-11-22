#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;
const long long p = 31;
const long long mod = 1e9 + 7;

string str, ptr;
vector <int> ans;
long long hashA, hashB, hashC, hashT, power[10 * maxn];

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
    power[0] = 1;

    for (int i = 1; i < 10 * maxn; ++i)
        power[i] = ((power[i - 1] % mod) * (p % mod)) % mod;
}

long long getVal(char ch, int pos)
{
    return (((ch - 97LL + 1LL) % mod) * (power[pos] % mod)) % mod;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    preprocess();

    cin >> str >> ptr;

    for (int i = 0; i < (int)str.size(); ++i)
        hashA = (hashA + getVal(str[i], i)) % mod;

    for (int i = 0; i < (int)ptr.size(); ++i)
        hashB = (hashB + getVal(ptr[i], i)) % mod;

    for (int i = 0; i < (int)str.size(); ++i)
    {
        hashT = ((hashA - hashC) + mod) % mod;
        hashT = ((hashT - getVal(str[i], i)) + mod) % mod;
        hashT = ((hashT % mod) * (modInverse(p) % mod)) % mod;
        hashT = (hashT + hashC) % mod;
        hashC = (hashC + getVal(str[i], i)) % mod;

        if (hashT == hashB)
            ans.push_back(i + 1);
    }

    cout << ans.size() << endl;

    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << " ";
    cout << endl;

    return 0;
}