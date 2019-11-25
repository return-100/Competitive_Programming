#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int n, m, ans, mark[5050], color[5050];
vector < pair<int, int> > vec[5050];

void dfs(int u)
{
    mark[u] = 1;

    for (int i = 0; i < vec[u].size(); ++i)
    {
        int v = vec[u][i].first;

        if (mark[v] == 1)
        {
            ans = 2;
            color[vec[u][i].second] = 2;
        }
        else if (mark[v] == 2)
            color[vec[u][i].second] = 1;
        else
        {
            dfs(v);
            color[vec[u][i].second] = 1;
        }
    }

    mark[u] = 2;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m, ans = 1;

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        vec[u - 1].push_back({v - 1, i});
    }

    for (int i = 0; i < n; ++i)
    {
        if (vec[i].size() && mark[i] == 0)
            dfs(i);
    }

    cout << ans << endl;

    for (int i = 0; i < m; ++i)
        cout << color[i] << " ";
    cout << endl;

    return 0;
}