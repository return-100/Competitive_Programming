#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define maxn 100010
#define ints size_t
#define i64 long long
#define mod 1000000007

#define sf(n) scanf("%d", &n)
#define pf(n) printf("%d\n", n)
#define sfl(n) scanf("%lld", &n)
#define sfs(str) scanf("%s", str)
#define pfl(n) printf("%lld\n", n)
#define ms(n, m) memset(n, m, sizeof(n))

int n, arr[maxn], st[4 * maxn];

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

int query(int ss, int se, int idx, int pos)
{
    --st[idx];

    if(ss == se)
        return ss;

    int mid = (ss + se) / 2, l = st[2 * idx + 1], r = st[2 * idx + 2];

    if(pos <= l)
        query(ss, mid, 2 * idx + 1, pos);
    else
        query(mid + 1, se, 2 * idx + 2, pos - l);
}

int main()
{
    int test, cs = 1;
    sf(test);

    while(test--)
    {
        ms(st, 0);

        sf(n);

        for(int i = 0; i < n; ++i)
            sf(arr[i]);

        build(0, n - 1, 0);

        for(int i = n - 1; i >= 0; --i)
            arr[i] = n - query(0, n - 1, 0, arr[i] + 1);

        printf("Case %d: %d\n", cs++, arr[0]);
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}

/*
2
7
0 1 1 0 1 2 0
7
0 1 1 1 1 1 4
*/