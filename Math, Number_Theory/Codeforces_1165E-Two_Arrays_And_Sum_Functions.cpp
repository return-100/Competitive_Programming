#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int n, idx, var;
vector <long long> vec;
long long coef[2 * maxn], brr[2 * maxn];

void init(int l, int r)
{
    long long sum = n, sub = 2;

    while (r >= l)
    {
        coef[l++] = sum, coef[r--] = sum;
        sum += (n - sub), sub += 2;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n, init(0, n - 1);

    for (int i = 0; i < n; ++i)
        cin >> var,  vec.push_back(var * coef[i]);

    sort(vec.begin(), vec.end());

    for (int i = 0; i < n; ++i)
        cin >> brr[i];

    sort(brr, brr + n);

    long long ans = 0, mod = 998244353;

    for (int i = 0; i < n; ++i)
        ans += ((vec[n - i - 1] % mod) * (brr[i] % mod)) % mod;

    cout << (ans + mod) % mod << endl;

    return 0;
}