#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int n;
long long sum, ans, arr[10 * maxn];
vector <long long> prime;
vector < pair<long long, long long> > vec;

void generatePrime(long long val)
{
    for (long long i = 2; i * i <= val; ++i)
    {
        if (val % i == 0)
        {
            prime.push_back(i);

            while (val % i == 0)
                val /= i;
        }
    }

    if (val > 1)
        prime.push_back(val);
}

long long getCost(long long k)
{
    long long ret = 0, cur = 0, idx, mid = (k / 2) + (k % 2);

    for (int i = 0; i < vec.size(); ++i)
    {
        cur += vec[i].second;

        if (cur >= mid)
        {
            idx = vec[i].first;
            break;
        }
    }

    for (int i = 0; i < vec.size(); ++i)
        ret += abs(vec[i].first - idx) * vec[i].second;

    return ret;
}

long long solve(long long k)
{
    long long ret = 0, cur = 0;

    for (int i = 0; i < n; ++i)
    {
        if (cur + arr[i] < k)
            cur += arr[i], vec.push_back({ i, arr[i] });
        else
        {
            vec.push_back({ i, k - cur });
            ret += getCost(k);
            cur = (arr[i] - (k - cur)) % k;
            vec.clear();
            vec.push_back({ i, cur });
        }
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n, ans = 1e18;

    for (int i = 0; i < n; ++i)
        cin >> arr[i], sum += arr[i];

    generatePrime(sum);

    for (int i = 0; i < prime.size(); ++i)
        ans = min(ans, solve(prime[i]));

    if (sum <= 1)
        cout << -1 << endl;
    else
        cout << ans << endl;

    return 0;
}