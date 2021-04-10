#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define maxn 100010
#define i64 long long
#define mod 1000000007

#define pf(n) printf("%d\n", n)
#define sf(n) scanf("%d", &n)
#define ms(n, m) memset(n, m, sizeof(n))

int n, m, sz, del, st[60 * maxn];

void build(int ss, int se, int idx)
{
    if(ss == se)
    {
        st[idx] = 1;
        return;
    }

    int mid = (ss + se) / 2;

    build(ss, mid, 2 * idx + 1);
    build(mid + 1, se, 2 * idx + 2);

    st[idx] = st[2 * idx + 1] + st[2 * idx + 2];
}

int update(int ss, int se, int idx, int num)
{
    if(ss == se && num == st[idx])
    {
        --st[idx];
        return ss;
    }
    else if(ss != se)
    {
        int l = st[2 * idx + 1], r = st[2 * idx + 2];

        if(num <= l + r)
        {
            --st[idx];

            int mid = (ss + se) / 2;

            if(num <= l)
                return update(ss, mid, 2 * idx + 1, num);
            else
                return update(mid + 1, se, 2 * idx + 2, num - l);
        }
    }
}

int query(int ss, int se, int idx, int num)
{
    if(ss == se && num == st[idx])
        return (ss + 1);
    else
    {
        int l = st[2 * idx + 1], r = st[2 * idx + 2];

        if(num <= l + r)
        {
            int mid = (ss + se) / 2;

            if(num <= l)
                return query(ss, mid, 2 * idx + 1, num);
            else
                return query(mid + 1, se, 2 * idx + 2, num - l);
        }
    }
}

void init()
{
    build(0, 15 * 100000 - 1, 0), sz = 15 * 100000, del = 2;

    for(int i = 1; i <= 100000; ++i)
    {
        for(int j = 1, k = 0; j <= sz / del; ++j, ++k)
            update(0, 15 * 100000 - 1, 0, del * j - k);

        sz -= sz / del;

        del = query(0, 15 * 100000 - 1, 0, i + 1);
    }
}

int main()
{
    int test, cs = 1;
    sf(test);

    init();

    while(test--)
    {
        sf(m);

        printf("Case %d: %d\n", cs++, query(0, 15 * 100000 - 1, 0, m));
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}