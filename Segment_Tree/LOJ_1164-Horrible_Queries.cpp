#include <stdio.h>
#include <string.h>

#define i64 long long
#define endl "\n"
#define maxn 100005
#define mod 1000000007

i64 st[4 * maxn], lz[4 * maxn];

void update(int ss, int se, int qs, int qe, int idx, i64 dx)
{
    int mid = (ss + se) / 2;

    if(ss > qe || se < qs)
        return;

    if(ss == se && qs <= ss && qe >= se)
    {
        st[idx] += lz[idx] + dx, lz[idx] = 0;
        return;
    }

    if(qs <= ss && qe >= se)
    {
        lz[idx] += dx;
        st[idx] += lz[idx] * (se - ss + 1);
        lz[2 * idx + 1] += lz[idx];
        lz[2 * idx + 2] += lz[idx];
        lz[idx] = 0;
        return;
    }

    if(ss <= qs && se >= qe)
        st[idx] += dx * (qe - qs + 1);
    else if(ss <= qs && se <= qe)
        st[idx] += dx * (se - qs + 1);
    else
        st[idx] += dx * (qe - ss + 1);

    update(ss, mid, qs, qe, 2 * idx + 1, dx);
    update(mid + 1, se, qs, qe, 2 * idx + 2, dx);
}

i64 query(int ss, int se, int qs, int qe, int idx)
{
    int mid = (ss + se) / 2;

    if(ss > qe || se < qs)
        return 0;

    st[idx] += lz[idx] * (se - ss + 1);

    if(ss == se && qs <= ss && qe >= se)
    {
        lz[idx] = 0;
        return st[idx];
    }

    if(qs <= ss && qe >= se)
    {
        lz[2 * idx + 1] += lz[idx];
        lz[2 * idx + 2] += lz[idx];
        lz[idx] = 0;
        return st[idx];
    }

    lz[2 * idx + 1] += lz[idx];
    lz[2 * idx + 2] += lz[idx];
    lz[idx] = 0;

    return query(ss, mid, qs, qe, 2 * idx + 1) + query(mid + 1, se, qs, qe, 2 * idx + 2);
}

i64 build(int ss, int se, int idx)
{
    int mid = (ss + se) / 2;

    if(ss == se)
    {
        st[idx] = 0;
        return st[idx];
    }

    st[idx] = build(ss, mid, 2 * idx + 1) + build(mid + 1, se, 2 * idx + 2);

    return st[idx];
}

int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);*/

    int t, cnt = 1;
    scanf("%d", &t);

    while(t--)
    {
        memset(lz, 0, sizeof(lz));

        int n, m;
        scanf("%d %d", &n, &m);

        build(0, n - 1, 0);

        printf("Case %d:\n", cnt++);

        for(int i = 0; i < m; ++i)
        {
            int q, l, r, dx;
            scanf("%d", &q);
            if(q)
            {
                scanf("%d %d", &l, &r);
                printf("%lld\n", query(0, n - 1, l, r, 0));
            }
            else
            {
                scanf("%d %d %d", &l, &r, &dx);
                update(0, n - 1, l, r, 0, dx);
            }
        }
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}