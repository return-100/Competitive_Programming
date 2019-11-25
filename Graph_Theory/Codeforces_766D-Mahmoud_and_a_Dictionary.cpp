#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

string str, ptr;
map <string, int> mp;
int type, n, m, q, u, v, paru, parv;
int par[maxn], sz[maxn], op[maxn];

int find(int u)
{
    if (par[u] == u)
        return u;

    return par[u] = find(par[u]);
}

int merge(int u, int v)
{
    if (v == 0)
        return u;

    if (u == 0)
        return v;

    if (sz[u] > sz[v])
        par[v] = u, sz[u] += sz[v];
    else
        par[u] = v, sz[v] += sz[u];

    return (sz[v] > sz[u] ? v : u);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> q;

    for (int i = 0; i < n; ++i)
    {
        cin >> str;
        mp[str] = i + 1;
        sz[i + 1] = 1;
        par[i + 1] = i + 1;
        op[i + 1] = 0;
    }

    for (int i = 0; i < m; ++i)
    {
        cin >> type >> str >> ptr;
        u = mp[str], paru = find(u);
        v = mp[ptr], parv = find(v);

        if ((type == 2 && paru == parv) || (type == 1 && op[parv] == paru))
            cout << "NO" << endl;
        else
        {
            if (type == 1)
            {
                int p1 = merge(paru, parv);
                int p2 = merge(op[paru], op[parv]);
                op[p1] = p2;
                op[p2] = p1;
            }
            else
            {
                int p1 = merge(op[paru], parv);
                int p2 = merge(op[parv], paru);
                op[p1] = p2;
                op[p2] = p1;
            }

            cout << "YES" << endl;
        }
    }

    for (int i = 0; i < q; ++i)
    {
        cin >> str >> ptr;
        u = mp[str], paru = find(u);
        v = mp[ptr], parv = find(v);

        if (paru == parv)
            cout << 1 << endl;
        else if (op[parv] == paru)
            cout << 2 << endl;
        else
            cout << 3 << endl;
    }

    return 0;
}