#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define maxn 100010
#define ints size_t
#define i64 long long
#define mod 1000000007

#define sf(n) scanf("%d", &n)
#define pf(n) printf("%d\n", n)
#define sc(c) scanf(" %c ", &c)
#define sl(n) scanf("%lld", &n)
#define ss(str) scanf("%s", str)
#define pl(n) printf("%lld\n", n)
#define ms(n, m) memset(n, m, sizeof(n))

int n, m, p, q, r, arr[510][510], st[4 * 510][4 * 510];

void build_y(int lx, int rx, int ly, int ry, int idx, int idy)
{
    if(ly == ry)
    {
        if(lx == rx)
            st[idx][idy] = arr[lx][ly];
        else
            st[idx][idy] = max(st[2 * idx + 1][idy], st[2 * idx + 2][idy]);

        return;
    }

    int mid = (ly + ry) / 2;

    build_y(lx, rx, ly, mid, idx, 2 * idy + 1);
    build_y(lx, rx, mid + 1, ry, idx, 2 * idy + 2);

    st[idx][idy] = max(st[idx][2 * idy + 1], st[idx][2 * idy + 2]);
}

void build_x(int lx, int rx, int idx)
{
    if(lx != rx)
    {
        int mid = (lx + rx) / 2;
        build_x(lx, mid, 2 * idx + 1);
        build_x(mid + 1, rx, 2 * idx + 2);
    }

    build_y(lx, rx, 0, n - 1, idx, 0);
}

int query_y(int ss, int se, int ly, int ry, int idx, int idy)
{
    if(ly > se || ry < ss)
        return -1;

    if(ly <= ss && ry >= se)
        return st[idx][idy];

    int mid = (ss + se) / 2;

    return max(query_y(ss, mid, ly, ry, idx, 2 * idy + 1), query_y(mid + 1, se, ly, ry, idx, 2 * idy + 2));
}

int query_x(int ss, int se, int lx, int rx, int ly, int ry, int idx)
{
    if(lx > se || rx < ss)
        return -1;

    if(lx <= ss && rx >= se)
        return query_y(0, n - 1, ly, ry, idx, 0);

    int mid = (ss + se) / 2;

    return max(query_x(ss, mid, lx, rx, ly, ry, 2 * idx + 1), query_x(mid + 1, se, lx, rx, ly, ry, 2 * idx + 2));
}

int main()
{
    int test, cs = 1;
    sf(test);

    while(test--)
    {
        ms(st, 0);

        sf(n), sf(m);

        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
                sf(arr[i][j]);
        }

        build_x(0, n - 1, 0);

        printf("Case %d:\n", cs++);

        for(int i = 0; i < m; ++i)
        {
            sf(p), sf(q), sf(r);

            --p, --q;

            pf(query_x(0, n - 1, p, p + r - 1, q, q + r - 1, 0));
        }
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}