#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define maxn 100005
#define i64 long long
#define mod 1000000007

#define pf(n) printf("%d\n", n)
#define sf(n) scanf("%d", &n)
#define ms(n, m) memset(n, m, sizeof(n))

struct pii
{
    int l, r, id;
}qrr[50000];

int mark[maxn], counter[maxn];
int n, m, q, mx, l, r, sqt, arr[maxn], ans[maxn];

void add(int i)
{
    ++mark[arr[i]];

    if(mark[arr[i]] > mx)
    {
        --counter[mx];
        mx = mark[arr[i]];
        ++counter[mark[arr[i]]];
    }
    else  if(mark[arr[i]] == mx)
    {
        ++counter[mx];
        --counter[mx - 1];
    }
    else
    {
        ++counter[mark[arr[i]]];
        --counter[mark[arr[i]] - 1];
    }
}

void remove(int i)
{
    if(mark[arr[i]] < mx)
    {
        --mark[arr[i]];
        ++counter[mark[arr[i]]];
        --counter[mark[arr[i]] + 1];
    }
    else
    {
        if(counter[mark[arr[i]]] - 1)
        {
            --mark[arr[i]];
            ++counter[mark[arr[i]]];
            --counter[mark[arr[i]] + 1];
        }
        else
        {
            --mark[arr[i]];
            ++counter[mark[arr[i]]];
            --counter[mark[arr[i]] + 1];
            mx = mark[arr[i]];
        }
    }
}

bool comp(pii q1, pii q2)
{
    if(q1.l / sqt != q2.l / sqt)
        return ((q1.l / sqt) < (q2.l / sqt));

    return (q1.r < q2.r);
}

int main()
{
    int t, cnt = 1;
    sf(t);

    while(t--)
    {
        ms(mark, 0), ms(counter, 0);

        sf(n), sf(m), sf(q), sqt = sqrt(n);
        l = 0, r = 0, mx = 0;

        for(int i = 0; i < n; ++i)
            sf(arr[i]);

        for(int i = 0; i < q; ++i)
            sf(qrr[i].l), sf(qrr[i].r), --qrr[i].l, qrr[i].id = i;

        sort(qrr, qrr + q, comp);

        for(int i = 0; i < q; ++i)
        {
            while(r < qrr[i].r)
                add(r), ++r;

            while(r > qrr[i].r)
                --r, remove(r);

            while(l < qrr[i].l)
                remove(l), ++l;

            while(l > qrr[i].l)
                --l, add(l);

            ans[qrr[i].id] = mx;
        }

        printf("Case %d:\n", cnt++);

        for(int i = 0; i < q; ++i)
            pf(ans[i]);
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}