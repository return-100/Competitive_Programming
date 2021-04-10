#include <bits/stdc++.h>
 
using namespace std;
 
#define endl "\n"
#define maxn 100010
#define i64 long long
#define mod 1000000007
 
#define pf(n) printf("%d\n", n)
#define sf(n) scanf("%d", &n)
#define ms(n, m) memset(n, m, sizeof(n))
 
struct node
{
    int parent;
    int chainIdx;
    int sz;
    int depth;
    int bitIdx;
};
 
bool mark[30001];
node arr[30001];
vector <int> vec[30001];
int n, m, u, v, q, curChain, bitBaseNodeIdx, w[30001];
int bit[30001], bitBase[30001], chainHead[30001], table[30001][15];
 
void addEdge()
{
    vec[u].push_back(v);
    vec[v].push_back(u);
}
 
void dfs(int u)
{
    mark[u] = true;
    arr[u].sz = 1;
 
    for(int i = 0; i < (int) vec[u].size(); ++i)
    {
        if(!mark[vec[u][i]])
        {
            arr[vec[u][i]].parent = u;
            arr[vec[u][i]].depth = arr[u].depth + 1;
            dfs(vec[u][i]);
            arr[u].sz += arr[vec[u][i]].sz;
        }
    }
}
 
void HLD(int u)
{
    if(chainHead[curChain] == -1)
        chainHead[curChain] = u;
 
    bitBase[bitBaseNodeIdx] = w[u];
    arr[u].bitIdx = bitBaseNodeIdx++;
    arr[u].chainIdx = curChain;
 
    int specialChild = -1;
 
    for(int i = 0; i < (int) vec[u].size(); ++i)
    {
        if(vec[u][i] != arr[u].parent)
        {
            if(specialChild == -1 || arr[specialChild].sz < arr[vec[u][i]].sz)
                specialChild = vec[u][i];
        }
    }
 
    if(specialChild != -1)
        HLD(specialChild);
 
    for(int i = 0; i < (int) vec[u].size(); ++i)
    {
        if(vec[u][i] != arr[u].parent && vec[u][i] != specialChild)
        {
            ++curChain;
            HLD(vec[u][i]);
        }
    }
}
 
void update(int idx, int val)
{
    while(idx <= n)
        bit[idx] += val, idx += (idx & -idx);
}
 
void build()
{
    for(int i = 1; i <= n; ++i)
        update(i, bitBase[i]);
}
 
int query(int idx)
{
    int ret = 0;
 
    while(idx > 0)
        ret += bit[idx], idx -= (idx & -idx);
 
    return ret;
}
 
void preprocess()
{
    ms(table, -1);
 
    for(int i = 0; i < n; ++i)
        table[i][0] = arr[i].parent;
 
    for(int j = 1; (1 << j) < n; ++j)
    {
        for(int i = 0; i < n; ++i)
        {
            if(table[i][j - 1] != -1)
                table[i][j] = table[table[i][j - 1]][j - 1];
        }
    }
}
 
int LCA(int u, int v)
{
    if(arr[u].depth < arr[v].depth)
        swap(u, v);
 
    int var = 1;
 
    while((1 << var) <= arr[u].depth)
        ++var;
 
    --var;
 
    for(int i = var; i >= 0; --i)
    {
        if(arr[u].depth - (1 << i) >= arr[v].depth)
            u = table[u][i];
    }
 
    if(u == v)
        return u;
 
    for(int i = var; i >= 0; --i)
    {
        if(table[u][i] != -1 && table[u][i] != table[v][i])
            u = table[u][i], v = table[v][i];
    }
 
    return arr[u].parent;
}
 
int crawlTree(int u, int v)
{
    int uChain = arr[u].chainIdx, vChain = arr[v].chainIdx, ans = 0;
 
    while(true)
    {
        if(uChain == vChain)
        {
            if(arr[u].bitIdx < arr[v].bitIdx)
                ans += query(arr[v].bitIdx) - query(arr[u].bitIdx - 1);
            else
                ans += query(arr[u].bitIdx) - query(arr[v].bitIdx - 1);
 
            return ans;
        }
        else
        {
            ans += query(arr[u].bitIdx) - query(arr[chainHead[uChain]].bitIdx - 1);
 
            u = arr[chainHead[uChain]].parent, uChain = arr[u].chainIdx;
        }
    }
 
    return ans;
}
 
int res(int u, int v)
{
    int lca = LCA(u, v), ans = 0;
 
    ans = crawlTree(u, lca) + crawlTree(v, lca) - w[lca];
 
    return ans;
}
 
int main()
{
    int test, cs = 1;
    sf(test);
 
    while(test--)
    {
        ms(bit, 0), ms(mark, false), ms(chainHead, -1);
 
        sf(n), curChain = 0, bitBaseNodeIdx = 1;
 
        for(int i = 0; i < n; ++i)
            sf(w[i]);
 
        for(int i = 0; i < n - 1; ++i)
        {
            sf(u), sf(v);
            addEdge();
        }
 
        arr[0].depth = 0, arr[0].parent = -1;
 
        dfs(0), HLD(0), build(), preprocess();
 
        sf(m);
 
        printf("Case %d:\n", cs++);
 
        for(int i = 0; i < m; ++i)
        {
            sf(q), sf(u), sf(v);
 
            if(q)
                update(arr[u].bitIdx, -w[u]), update(arr[u].bitIdx, v), w[u] = v;
            else
                pf(res(u, v));
        }
 
        for(int i = 0; i < n; ++i)
            vec[i].clear();
    }
 
    /*cin.clear();
    cin.ignore();
    cin.get();*/

    return 0;
}