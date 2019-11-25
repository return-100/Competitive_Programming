#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

char c;
bool isGood;
bool mark[maxn];
int n, m, sz[2], st[maxn];
vector <int> s, t, ans[2];
vector < pair<int, int> > vec[maxn];

bool dfs(int u, int set_idx, int cur_color)
{
    if (mark[u])
        return st[u] == set_idx;

    mark[u] = true;
    st[u] = set_idx;

    if (set_idx == 0)
        s.push_back(u);
    else
        t.push_back(u);

    for (int i = 0; i < vec[u].size(); ++i)
    {
        int v = vec[u][i].first, nxt_idx = set_idx;
        
        if (vec[u][i].second != cur_color)
            nxt_idx = (set_idx ? 0 : 1);

        if (!dfs(v, nxt_idx, cur_color))
            return false;
    }

    return true;
}

void go(int cur_color)
{
    memset(mark, false, sizeof(mark));

    for (int i = 0; i < n; ++i)
    {
        if (!mark[i])
        {
            s.clear();
            t.clear();

            if (!dfs(i, 0, cur_color))
            {
                isGood = (isGood | false);
                sz[cur_color] = maxn;
                return;
            }

            if (s.size() < t.size())
                ans[cur_color].insert(ans[cur_color].end(), s.begin(), s.end());
            else
                ans[cur_color].insert(ans[cur_color].end(), t.begin(), t.end());
        }
    }

    isGood = true;
    sz[cur_color] = ans[cur_color].size();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v >> c;
        vec[u - 1].push_back({ v - 1, c == 'R' ? 0 : 1 });
        vec[v - 1].push_back({ u - 1, c == 'R' ? 0 : 1 });
    }

    go(0);
    go(1);

    if (!isGood)
        cout << -1 << endl;
    else
    {
        cout << min(sz[0], sz[1]) << endl;

        int idx = (sz[0] < sz[1] ? 0 : 1);

        for (int i = 0; i < ans[idx].size(); ++i)
            cout << ans[idx][i] + 1 << " ";

        cout << endl;
    }

    return 0;
}