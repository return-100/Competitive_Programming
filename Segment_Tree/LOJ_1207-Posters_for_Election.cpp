#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define maxn 100010
#define i64 long long
#define mod 1000000007

#define pf(n) printf("%d\n", n)
#define sf(n) scanf("%d", &n)
#define ms(n, m) memset(n, m, sizeof(n))

int n, m, ans, st[8 * maxn], lz[8 * maxn];
vector < pair<int, int> > vec;

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

void update(int ss, int se, int qs, int qe, int idx)
{
    if(lz[idx])
    {
        st[idx] = 0;

        if(ss != se)
            lz[2 * idx + 1] = 1, lz[2 * idx + 2] = 1;

        lz[idx] = 0;
    }

    if(qs > se || ss > qe)
        return;

    if(qs <= ss && qe >= se)
    {
        st[idx] = 0;

        if(ss != se)
            lz[2 * idx + 1] = 1, lz[2 * idx + 2] = 1;

        lz[idx] = 0;

        return;
    }

    int mid = (ss + se) / 2;

    update(ss, mid, qs, qe, 2 * idx + 1);
    update(mid + 1, se, qs, qe, 2 * idx + 2);

    st[idx] = st[2 * idx + 1] + st[2 * idx + 2];
}

int query(int ss, int se, int qs, int qe, int idx)
{
    if(lz[idx])
    {
        st[idx] = 0;

        if(ss != se)
            lz[2 * idx + 1] = 1, lz[2 * idx + 2] = 1;

        lz[idx] = 0;
    }

    if(qs > se || ss > qe)
        return 0;

    if(qs <= ss && qe >= se)
        return st[idx];

    int mid = (ss + se) / 2;

    return query(ss, mid, qs, qe, 2 * idx + 1) + query(mid + 1, se, qs, qe, 2 * idx + 2);
}

int main()
{
    int test, cs = 1;
    sf(test);

    while(test--)
    {
        ms(st, 0), ms(lz, 0);
        ans = 0, m = 0;
        sf(n);

        for(int i = 0; i < n; ++i)
        {
            int l, r;
            sf(l), sf(r);
            vec.push_back({ l - 1, r - 1 });
            m = max(m, r - 1);
        }

        build(0, m, 0);

        for(int i = n - 1; i >= 0; --i)
        {
            if(query(0, m, vec[i].first, vec[i].second, 0))
                update(0, m, vec[i].first, vec[i].second, 0), ++ans;
        }

        printf("Case %d: %d\n", cs++, ans);

        vec.clear();
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}