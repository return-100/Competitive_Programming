#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define maxn 100005
#define i64 long long
#define mod 1000000007

#define mem(arr, value) memset(arr, value, sizeof(arr))

int n, m, st[4 * maxn], lz[4 * maxn], d, l, r, val;

int gcd(int a, int b) 
{
    return b ? gcd(b, a % b) : a;
}

void update(int ss, int se, int qs, int qe, int idx, int val)
{
    if(lz[idx] != -1)
    {
        st[idx] = (se - ss + 1) * lz[idx];

        if(ss != se)
            lz[2 * idx + 1] = lz[idx], lz[2 * idx + 2] = lz[idx];

        lz[idx] = -1;
    }

    if(ss > qe || qs > se)
        return;

    if(qs <= ss && qe >= se)
    {
        st[idx] = (se - ss + 1) * val;

        if(ss != se)
            lz[2 * idx + 1] = val, lz[2 * idx + 2] = val;

        lz[idx] = -1;

        return;
    }

    int mid = (ss + se) / 2;

    update(ss, mid, qs, qe, 2 * idx + 1, val);
    update(mid + 1, se, qs, qe, 2 * idx + 2, val);

    st[idx] = st[2 * idx + 1] + st[2 * idx + 2];
}

int query(int ss, int se, int qs, int qe, int idx)
{
    if(lz[idx] != -1)
    {
        st[idx] = (se - ss + 1) * lz[idx];

        if(ss != se)
            lz[2 * idx + 1] = lz[idx], lz[2 * idx + 2] = lz[idx];

        lz[idx] = -1;
    }

    if(ss > qe || qs > se)
        return 0;

    if(qs <= ss && qe >= se)
        return st[idx];

    int mid = (ss + se) / 2;

    return query(ss, mid, qs, qe, 2 * idx + 1) + query(mid + 1, se, qs, qe, 2 * idx + 2);
}

int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);*/

    int t, cnt = 1;
    scanf("%d", &t);

    while(t--)
    {
        mem(st, 0), mem(lz, -1);

        scanf("%d %d", &n, &m);

        printf("Case %d:\n", cnt++);

        for(int i = 0, temp, var; i < m; ++i)
        {
            scanf("%d", &d);

            if(d == 1)
            {
                scanf("%d %d %d", &l, &r, &val);
                update(0, n - 1, l, r, 0, val);
            }
            else
            {
                scanf("%d %d", &l, &r);
                temp = query(0, n - 1, l, r, 0), var = gcd(temp, r - l + 1);

                if(temp % (r - l + 1) == 0)
                    printf("%d\n", temp / (r - l + 1));
                else
                    printf("%d/%d\n", temp / var, (r - l + 1) / var);
            }
        }
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}
