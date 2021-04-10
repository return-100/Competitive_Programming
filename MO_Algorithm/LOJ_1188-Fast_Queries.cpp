#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define maxn 100005
#define i64 long long
#define mod 1000000007

struct pii
{
    int l, r, id;
}qrr[50000];

int mark[maxn];
int n, m, sqt, l, r, tot, ans[50000], arr[maxn];

bool comp(pii q1, pii q2)
{
    if(q1.l / sqt != q2.l / sqt)
        return ((q1.l / sqt) < (q2.l / sqt));

    return (q1.r < q2.r);
}

void include(int idx)
{
    ++mark[arr[idx]];

    if(mark[arr[idx]] == 1)
        ++tot;
}

void exclude(int idx)
{
    --mark[arr[idx]];

    if(!mark[arr[idx]])
        --tot;
}

int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);*/

    int t, cnt = 1;
    scanf("%d", &t);

    while(t--)
    {
        memset(mark, 0, sizeof(mark));

        scanf("%d %d", &n, &m);
        tot = 0, sqt = (int) sqrt(n);

        for(int i = 0; i < n; ++i)
            scanf("%d", &arr[i]);

        for(int i = 0; i < m; ++i)
        {
            scanf("%d %d", &qrr[i].l, &qrr[i].r), --qrr[i].l, qrr[i].r;
            qrr[i].id = i;
        }

        sort(qrr, qrr+m, comp);

        l = 0, r = 0;

        printf("Case %d:\n", cnt++);

        for(int i = 0; i < m; ++i)
        {
            while(r < qrr[i].r)
                include(r), ++r;

            while(r > qrr[i].r)
                --r, exclude(r);

            while(l < qrr[i].l)
                exclude(l), ++l;

            while(l > qrr[i].l)
                --l, include(l);

            ans[qrr[i].id] = tot;
        }

        for(int i = 0; i < m; ++i)
            printf("%d\n", ans[i]);
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}
