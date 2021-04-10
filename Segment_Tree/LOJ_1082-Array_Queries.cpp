#include <bits/stdc++.h>

using namespace std;

#define i64 long long
#define endl "\n"
#define maxn 100005
#define mod 1000000007

int n, m, l, r, arr[maxn], st[4 * maxn];

int getMid(int ss, int se)
{
    return (se + ss) / 2;
}

int build(int ss, int se, int idx)
{
    int mid = getMid(ss, se);

    if(ss == se)
    {
        st[idx] = arr[ss];
        return st[idx];
    }

    st[idx] = min(build(ss, mid, 2 * idx + 1), build(mid + 1, se, 2 * idx + 2));

    return st[idx];
}

int query(int ss, int se, int qs, int qe, int idx)
{
    int mid = getMid(ss, se);

    if(ss > qe || qs > se) return INT_MAX;

    if(qs <= ss && qe >= se) return st[idx];

    return min(query(ss, mid, qs, qe, 2 * idx + 1), query(mid + 1, se, qs, qe, 2 * idx + 2));
}

int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);*/

    int t, cnt = 1;
    scanf("%d", &t);

    while(t--)
    {
        cin >> n >> m;
        for(int i = 0; i < n; ++i)
            scanf("%d", &arr[i]);

        build(0, n - 1, 0);

        printf("Case %d:\n", cnt++);

        for(int i = 0; i < m; ++i)
        {
            scanf("%d %d", &l, &r), --l, --r;
            printf("%d\n", query(0, n - 1, l, r, 0));
        }
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}