#include <bits/stdc++.h>

using namespace std;

#define i64 long long
#define endl "\n"
#define maxn 100005
#define mod 1000000007

int n, m, ans, arr[maxn], maxst[4 * maxn], minst[4 * maxn];

int buildMin(int ss, int se, int idx)
{
    if(ss == se)
    {
        minst[idx] = arr[ss];
        return arr[ss];
    }

    int mid = (ss + se) / 2;

    minst[idx] = min(buildMin(ss, mid, 2 * idx + 1), buildMin(mid + 1, se, 2 * idx + 2));

    return minst[idx];
}

int buildMax(int ss, int se, int idx)
{
    if(ss == se)
    {
        maxst[idx] = arr[ss];
        return arr[ss];
    }

    int mid = (ss + se) / 2;

    maxst[idx] = max(buildMax(ss, mid, 2 * idx + 1), buildMax(mid + 1, se, 2 * idx + 2));

    return maxst[idx];
}

int RMQmin(int ss, int se, int qs, int qe, int idx)
{
    if(ss > qe || se < qs) return INT_MAX;

    if(qs <= ss && qe >= se) return minst[idx];

    int mid = (ss + se) / 2;

    return min(RMQmin(ss, mid, qs, qe, 2 * idx + 1), RMQmin(mid + 1, se, qs, qe, 2 * idx + 2));
}

int RMQmax(int ss, int se, int qs, int qe, int idx)
{
    if(ss > qe || se < qs) return INT_MIN;

    if(qs <= ss && qe >= se) return maxst[idx];

    int mid = (ss + se) / 2;

    return max(RMQmax(ss, mid, qs, qe, 2 * idx + 1), RMQmax(mid + 1, se, qs, qe, 2 * idx + 2));
}

int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);*/

    int t, cnt = 1;
    scanf("%d", &t);

    while(t--)
    {
        scanf("%d %d", &n, &m), ans = 0;

        if(m == 1)
        {
            for(int i = 0; i < n; ++i)
                scanf("%d", &arr[i]);
        }
        else
        {
            for(int i = 0; i < n; ++i)
                scanf("%d", &arr[i]);

            buildMax(0, n - 1, 0);
            buildMin(0, n - 1, 0);

            for(int i = 0; i <= n - m; ++i)
            {
                int mn = RMQmin(0, n - 1, i, i + m - 1, 0), mx = RMQmax(0, n - 1, i, i + m - 1, 0);

                ans = max(ans, mx - mn);
            }
        }

        printf("Case %d: %d\n", cnt++, ans);
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}