#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool mark[111][111][111];
string str, ptr, vtr, ans;
int sz, pz, vz, ansSz, lcp[111], dp[111][111][111];

void preprocess()
{
    int idx = 1, jdx = 0;

    while (idx < vz)
    {
        while (jdx > 0 && vtr[idx] != vtr[jdx])
            jdx = lcp[jdx - 1];

        lcp[idx] = (vtr[idx] == vtr[jdx] ? ++jdx : 0), ++idx;
    }
}

int solve(int i, int j, int k)
{
    if (k >= vz)
        return dp[i][j][k] = -2 * maxn;

    if (i == sz || j == pz)
        return dp[i][j][k] = 0;

    if (mark[i][j][k])
        return dp[i][j][k];

    mark[i][j][k] = true;

    int ret = -2 * maxn, tk = k;

    if (str[i] == ptr[j])
    {
        while (tk && vtr[tk] != str[i])
            tk = lcp[tk - 1];

        if (str[i] == vtr[tk])
            ++tk;

        ret = max(ret, 1 + solve(i + 1, j + 1, tk));
    }

    ret = max(ret, solve(i + 1, j, k));
    ret = max(ret, solve(i, j + 1, k));

    return dp[i][j][k] = ret;
}

void backTrack(int i, int j, int k)
{
    if (k == vz)
        return;

    if (i == sz || j == pz)
        return;

    int tk = k;

    while (tk && vtr[tk] != str[i])
        tk = lcp[tk - 1];

    if (str[i] == vtr[tk])
        ++tk;

    if (str[i] == ptr[j] && dp[i + 1][j + 1][tk] + 1 == ansSz)
        --ansSz, ans += str[i], backTrack(i + 1, j + 1, tk);
    else if (dp[i + 1][j][k] == ansSz)
        backTrack(i + 1, j, k);
    else
        backTrack(i, j + 1, k);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> str >> ptr >> vtr, ans = "";

    sz = str.size();
    pz = ptr.size();
    vz = vtr.size();

    preprocess();
    ansSz = solve(0, 0, 0);

    if (ansSz)
    {
        backTrack(0, 0, 0);
        cout << ans << endl;
    }
    else
        cout << 0 << endl;

    return 0;
}