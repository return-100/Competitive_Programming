#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool mark[2 * maxn];
int n, m, arr[maxn], rel[2 * maxn];
stack <int> st;
set <int> component;
vector <int> vec[maxn], adj[2 * maxn];

void constructGraph()
{
    for (int i = 0; i < n; ++i)
    {
        int u = 2 * vec[i][0];
        int v = 2 * vec[i][1];

        if (arr[i])
        {
            adj[u].push_back(v);
            adj[v].push_back(u);
            adj[u + 1].push_back(v + 1);
            adj[v + 1].push_back(u + 1);
        }
        else
        {
            adj[u].push_back(v + 1);
            adj[v + 1].push_back(u);
            adj[v].push_back(u + 1);
            adj[u + 1].push_back(v);
        }
    }
}

void dfs1(int u)
{
    mark[u] = true;
    st.push(u);

    for (int i = 0; i < adj[u].size(); ++i)
    {
        if (!mark[adj[u][i]])
            dfs1(adj[u][i]);
    }
}

void dfs2(int u)
{
    mark[u] = true;
    component.insert(u);

    for (int i = 0; i < adj[u].size(); ++i)
    {
        if (!mark[adj[u][i]])
            dfs2(adj[u][i]);
    }
}

string kosaraju()
{
    for (int i = 0; i < 2 * m; ++i)
    {
        if (!mark[i])
            dfs1(i);
    }

    memset(mark, false, sizeof(mark));

    while (!st.empty())
    {
        if (!mark[st.top()])
        {
            dfs2(st.top());
            st.pop();

            set <int> :: iterator itr = component.begin();

            for (itr; itr != component.end(); ++itr)
            {
                if (component.count(rel[*itr]))
                    return "NO";
            }

            component.clear();
        }
        else
            st.pop();
    }

    return "YES";
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    for (int i = 0; i < m; ++i)
    {
        rel[2 * i] = (2 * i) + 1;
        rel[(2 * i) + 1] = 2 * i;

        int var, room;

        cin >> var;

        for (int j = 0; j < var; ++j)
            cin >> room, vec[room - 1].push_back(i);
    }

    constructGraph();

    cout << kosaraju() << endl;

    return 0;
}