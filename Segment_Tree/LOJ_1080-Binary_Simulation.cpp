#include <bits/stdc++.h>

using namespace std;

#define i64 long long
#define endl "\n"
#define maxn 100005
#define mod 1000000007

char str[maxn];
int n, range, st[4 * maxn];

int getMid(int ss, int se)
{
    return (ss + se) / 2;
}

void query1(int ss, int se, int qs, int qe, int idx)
{
    int mid = getMid(ss, se);

    if(ss > qe || se < qs) return;

    if(qs <= ss && qe >= se && ss != se)
    {
        st[idx * 2 + 1] += 1;
        st[idx * 2 + 2] += 1;
        return;
    }
    if(qs <= ss && qe >= se && ss == se)
    {
        st[idx] += 1;
        return;
    }

    query1(ss, mid, qs, qe, 2 * idx + 1);
    query1(mid + 1, se, qs, qe, 2 * idx + 2);
}

void query2(int pos, int ss, int se, int idx)
{
    int mid = getMid(ss, se);

    if(ss > idx || se < idx) return;

    if(ss == se && ss == idx)
    {
        if(st[pos] % 2)
            str[idx] == '1' ? printf("0\n") : printf("1\n");
        else
            printf("%c\n", str[idx]);
        return;
    }

    st[2 * pos + 1] += st[pos], st[2 * pos + 2] += st[pos];
    st[pos] = 0;

    query2(2 * pos + 1, ss, mid, idx);
    query2(2 * pos + 2, mid + 1, se, idx);
}

void build(int ss, int se, int idx)
{
    if(ss == se)
    {
        st[idx] = 0;
        return;
    }

    int mid = getMid(ss, se);
    st[idx] = 0;

    build(ss, mid, 2 * idx + 1);
    build(mid + 1, se, 2 * idx + 2);
}

int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);*/

    int t, cnt = 1;
    cin >> t;

    while(t--)
    {
        scanf("%s", str);
        range = strlen(str);
        scanf("%d", &n);
        printf("Case %d:\n", cnt++);

        build(0, range - 1, 0);

        while(n--)
        {
            char c[3];
            int qs, qe;
            scanf("%s", c);

            if(c[0] == 'I')
            {
                scanf("%d %d", &qs, &qe);
                query1(0, range - 1, qs - 1, qe - 1, 0);
            }
            else
            {
                scanf("%d", &qs);
                query2(0, 0, range - 1, qs - 1);
            }
        }
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}
