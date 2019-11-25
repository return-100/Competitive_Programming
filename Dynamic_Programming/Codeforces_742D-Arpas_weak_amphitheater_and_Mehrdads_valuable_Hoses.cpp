#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool mark[1111][1111];
vector <int> vec[1111];
int par[1111], sz[1111], totw[1111], totb[1111];
int n, w, m, arr[1111], brr[1111], dp[1111][1111], mp[1111];

int find(int u)
{
    return par[u] = (par[u] == u ? u : find(par[u]));
}

void merge(int u, int v)
{
    if (v == u)
        return;
    else if (sz[u] > sz[v])
        par[v] = u, sz[u] += sz[v], totw[u] += totw[v], totb[u] += totb[v];
    else
        par[u] = v, sz[v] += sz[u], totw[v] += totw[u], totb[v] += totb[u];
}

int solve(int idx, int need)
{
    if (idx < 0 || need == 0)
        return 0;

    if (mark[idx][need])
        return dp[idx][need];

    mark[idx][need] = true;

    int ret = 0;
    int curIdx = mp[idx];

    for (int i = 0; i < 3; ++i)
    {
        if (i == 0)
            ret = solve(idx - 1, need);
        else if (i == 2 && need - totw[curIdx] >= 0)
            ret = max(ret, totb[curIdx] + solve(idx - 1, need - totw[curIdx]));
        else
        {
            for (int j = 0; j < vec[curIdx].size(); ++j)
            {
                if (need - arr[vec[curIdx][j]] >= 0)
                    ret = max(ret, brr[vec[curIdx][j]] + solve(idx - 1, need - arr[vec[curIdx][j]]));
            }
        }
    }

    return dp[idx][need] = ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> w;

    for (int i = 0; i < n; ++i)
        cin >> arr[i], par[i] = i, sz[i] = 1, totw[i] = arr[i];

    for (int i = 0; i < n; ++i)
        cin >> brr[i], totb[i] = brr[i];

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        merge(find(u - 1), find(v - 1));
    }

    for (int i = 0; i < n; ++i)
        vec[find(i)].push_back(i);

    int sz = 0;

    for (int i = 0; i < n; ++i)
    {
        if (vec[i].size())
            mp[sz] = i, sz++;
    }

    cout << solve(sz - 1, w) << endl;

    return 0;
}