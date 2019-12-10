#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int n;
bool mark[3003][3003];
vector < pair<long long, long long> > vec;
long long x, c, dp[3003][3003], preprocess[3003][3003];

long long solve(int preIdx, int curIdx)
{
    if (curIdx == n)
        return (preIdx == n - 1 ? 0 : 1e15);

    if (mark[preIdx][curIdx])
        return dp[preIdx][curIdx];

    mark[preIdx][curIdx] = true;

    return dp[preIdx][curIdx] = min(solve(preIdx, curIdx + 1), vec[curIdx - 1].second + preprocess[curIdx][curIdx] - preprocess[curIdx][preIdx] + solve(curIdx, curIdx + 1));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> x >> c, vec.push_back({ x, c });

    sort(vec.rbegin(), vec.rend());

    for (int i = n; i >= 1; --i)
    {
        for (int j = 1; j <= i; ++j)
            preprocess[i][j] = abs(vec[i - 1].first - vec[j - 1].first) + preprocess[i][j - 1];
    }

    ++n;

    cout << solve(0, 1) << endl;

    return 0;
}