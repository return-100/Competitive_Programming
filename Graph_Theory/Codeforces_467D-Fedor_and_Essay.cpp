#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

stack <int> st;
string str, ptr;
bool mark[3 * maxn];
map <string, int> mp;
set <int> adj[3 * maxn];
vector <int> vec[3 * maxn], wec[3 * maxn];
long long rcount[3 * maxn], len[3 * maxn];
pair <long long, long long> component[3 * maxn];
int n, m, nodeCnt, compCnt, arr[maxn], compNum[3 * maxn];

void dfs1(int u)
{
    mark[u] = true;

    for (int i = 0; i < vec[u].size(); ++i)
    {
        if (!mark[vec[u][i]])
            dfs1(vec[u][i]);
    }

    st.push(u);
}

void dfs2(int u)
{
    mark[u] = true;
    compNum[u] = compCnt;
    
    if (component[compCnt].first > rcount[u])
        component[compCnt] = { rcount[u], len[u] };
    else if (component[compCnt].first == rcount[u])
        component[compCnt].second = min(component[compCnt].second, len[u]);

    for (int i = 0; i < wec[u].size(); ++i)
    {
        if (!mark[wec[u][i]])
            dfs2(wec[u][i]);
    }
}

void dfs3(int u)
{
    mark[u] = true;

    for (int i = 0; i < vec[u].size(); ++i)
    {
        if (compNum[vec[u][i]] != compNum[u])
            adj[compNum[u]].insert(compNum[vec[u][i]]);

        if (!mark[vec[u][i]])
            dfs3(vec[u][i]);
    }
}

void dfs4(int u)
{
    mark[u] = true;

    for (auto v : adj[u])
    {
        if (!mark[v])
            dfs4(v);

        if (component[v].first < component[u].first)
            component[u] = component[v];
        else if (component[v].first == component[u].first)
            component[u].second = min(component[u].second, component[v].second);
    }
}

void kosaraju()
{
    for (int i = 1; i < nodeCnt; ++i)
    {
        if (!mark[i])
            dfs1(i);
    }

    memset(mark, false, sizeof(mark));

    for (int i = 1; i < nodeCnt; ++i)
    {
        for (int j = 0; j < vec[i].size(); ++j)
            wec[vec[i][j]].push_back(i);
    }

    while (!st.empty())
    {
        if (!mark[st.top()])
            component[compCnt] = {1e15, 1e15}, dfs2(st.top()), st.pop(), ++compCnt;
        else
            st.pop();
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n, nodeCnt = 1;

    for (int i = 0; i < n; ++i)
    {
        cin >> str;
        transform(str.begin(), str.end(), str.begin(), ::tolower);

        if (!mp[str])
            len[nodeCnt] = str.size(), rcount[nodeCnt] = count(str.begin(), str.end(), 'r'), mp[str] = nodeCnt++;

        arr[i] = mp[str];
    }

    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        cin >> str >> ptr;
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        transform(ptr.begin(), ptr.end(), ptr.begin(), ::tolower);

        if (!mp[str])
            len[nodeCnt] = str.size(), rcount[nodeCnt] = count(str.begin(), str.end(), 'r'), mp[str] = nodeCnt++;

        if (!mp[ptr])
            len[nodeCnt] = ptr.size(), rcount[nodeCnt] = count(ptr.begin(), ptr.end(), 'r'), mp[ptr] = nodeCnt++;

        vec[mp[str]].push_back(mp[ptr]);
    }

    kosaraju();

    memset(mark, false, sizeof(mark));

    for (int i = 1; i < nodeCnt; ++i)
    {
        if (!mark[i])
            dfs3(i);
    }

    memset(mark, false, sizeof(mark));

    for (int i = 0; i < compCnt; ++i)
    {
        if (!mark[i])
            dfs4(i);
    }

    long long ansRcnt = 0, ansSz = 0;

    for (int i = 0; i < n; ++i)
        ansRcnt += component[compNum[arr[i]]].first, ansSz += component[compNum[arr[i]]].second;

    cout << ansRcnt << " " << ansSz << endl;

    return 0;
}