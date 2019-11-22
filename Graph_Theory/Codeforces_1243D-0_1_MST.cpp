#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool mark[maxn];
int n, m, u, v, ans;
queue <int> q, tq;
set <int> st, adj[maxn];

void bfs(int s)
{
    q.push(s);

    while (!q.empty())
    {
        u = q.front();
        q.pop();
        mark[u] = true;

        for (auto v : st)
        {
            if (adj[u].find(v) == adj[u].end())
                tq.push(v), q.push(v);
        }

        while (!tq.empty())
            st.erase(tq.front()), tq.pop();
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < m; ++i)
        cin >> u >> v, adj[u].insert(v), adj[v].insert(u);

    for (int i = 1; i <= n; ++i)
        st.insert(i);

    for (int i = 1; i <= n; ++i)
    {
        if (!mark[i])
            ++ans, bfs(i);
    }

    cout << ans - 1 << endl;

    return 0;
}