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

char str[2010];
int n, m, ans, var, st[4 * 2010], arr[2010];

int minVal(int i, int j)
{
    if(i == -1)
        return j;
    if(j == -1)
        return i;

    return arr[i] > arr[j] ? j : i;
}

void build(int ss, int se, int idx)
{
    if(ss == se)
    {
        st[idx] = ss;
        return;
    }

    int mid = (ss + se) / 2;

    build(ss, mid, 2 * idx + 1);
    build(mid + 1, se, 2 * idx + 2);

    st[idx] = minVal(st[2 * idx + 1], st[2 * idx + 2]);
}

int RMQ(int ss, int se, int qs, int qe, int idx)
{
    if(ss > qe || qs > se)
        return -1;

    if(qs <= ss && qe >= se)
        return st[idx];

    int mid = (ss + se) / 2;

    return minVal(RMQ(ss, mid, qs, qe, 2 * idx + 1), RMQ(mid + 1, se, qs, qe, 2 * idx + 2));
}

int solve(int qs, int qe)
{
    if(qe < qs)
        return -1;

    if(qs == qe)
        return arr[qs];

    int idx = RMQ(0, m - 1, qs, qe, 0);

    return max(solve(qs, idx - 1), max(solve(idx + 1, qe), (qe - qs + 1) * arr[idx]));
}

int main()
{
    int test, cs = 1;
    sf(test);

    while(test--)
    {
        ms(st, 0), ms(arr, -1);

        sf(n), sf(m), ans = 0;

        for(int i = 0; i < n; ++i)
        {
            sfs(str);

            for(int j = 0; j < m; ++j)
            {
                if(str[j] == '0' && arr[j] != -1 && arr[j])
                    ++arr[j];
                else if(str[j] == '1')
                    arr[j] = 0;
                else
                    arr[j] = 1;
            }

            build(0, m - 1, 0);

            ans = max(ans, solve(0, m - 1));
        }

        printf("Case %d: %d\n", cs++, ans);
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}

/*
2
5 7
0 1 1 0 1 1 0
0 0 0 0 0 1 0
1 0 0 0 0 0 1
0 1 0 0 0 0 1
1 1 0 0 0 1 0
3 3
0 0 1
1 0 0
1 0 1
*/