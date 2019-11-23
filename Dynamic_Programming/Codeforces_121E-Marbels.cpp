#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool mark[(1 << 20) + 1];
bool isGood[22];
vector <int> vec[22];
int n, mxMask, val;
long long cnt[22][22], dp[(1 << 20) + 1];

void preprocessing()
{
    for (int i = 1; i <= 20; ++i)
    {
        for (int j = 1; j <= 20; ++j)
        {
            if (i == j || !isGood[j])
                continue;

            int idx = 0;

            for (int k = 0; k < (int)vec[i].size(); ++k)
                cnt[i][j] += upper_bound(vec[j].begin(), vec[j].end(), vec[i][k]) - lower_bound(vec[j].begin(), vec[j].end(), 0);
        }
    }
}

long long solve(int mask)
{
    if (mask == (1 << 20) - 1)
        return 0;

    if (mark[mask])
        return dp[mask];
        
    mark[mask] = true;

    long long ret = 1e18;

    for (int i = 1; i <= 20; ++i)
    {
        if (!(mask & (1 << (i - 1))))
        {
            long long cur = 0;

            for (int j = 1; j <= 20; ++j)
            {
                if (!(mask & (1 << (j - 1))))
                    cur += cnt[i][j];
            }

            ret = min(ret, cur + solve(mask | (1 << (i - 1))));
        }
    }

    return dp[mask] = ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> val, vec[val].push_back(i), isGood[val] = true;
    
    preprocessing();

    cout << solve(0) << endl;

    return 0;
}