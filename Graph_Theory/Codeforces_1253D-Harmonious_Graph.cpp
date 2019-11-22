#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool mark[2 * maxn], isGood[2 * maxn];
int n, m, compCnt, u, v, node[2 * maxn];
vector <int> vec[2 * maxn], component[2 * maxn];

void dfs(int u)
{
    mark[u] = true;
    node[u] = compCnt;
    component[compCnt].push_back(u);

    for (int i = 0; i < vec[u].size(); ++i)
    {
        if (!mark[vec[u][i]])
            dfs(vec[u][i]);
    }
}

int add(int idx, int mn, int mx)
{
    int ret = 0, jdx = 2 * maxn - 1;

    for (int i = mn; i <= mx; ++i)
    {
        jdx = node[i];

        if (jdx != idx)
        {
            if (jdx != -1)
            {
                mx = max(mx, component[jdx].back());

                for (int j = 0; j < component[jdx].size(); ++j)
                    node[component[jdx][j]] = idx;

                component[jdx].clear();
            }

            ++ret;
        }
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(node, -1, sizeof(node));

    cin >> n >> m;

    for (int i = 0; i < m; ++i)
        cin >> u >> v, vec[u].push_back(v), vec[v].push_back(u);

    for (int i = 1; i <= n; ++i)
    {
        if (!mark[i] && vec[i].size() > 0)
            dfs(i), ++compCnt;
    }

    int ans = 0;

    for (int i = 0; i < compCnt; ++i)
        sort(component[i].begin(), component[i].end());

    for (int i = 0; i < compCnt; ++i)
    {
        if (component[i].size() > 0)
        {
            int mn = component[i].front();
            int mx = component[i].back();
            ans += add(i, mn, mx);
        }
    }

    cout << ans << endl;

    return 0;
}