#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define maxn 100010
#define ints size_t
#define pbk push_back
#define intl long long
#define mod 1000000007
#define pi 2 * acos(0.0)

#define sf(n) scanf("%d", &n)
#define sd(n) scanf("%lf", &n)
#define sl(n) scanf("%lld", &n)
#define sc(c) scanf(" %c", &c)
#define ss(str) scanf("%s", str)
#define pc(c) printf("%c\n", c)
#define pf(n) printf("%d\n", n)
#define pd(n) printf("%lf\n", n)
#define pl(n) printf("%lld\n", n)
#define ps(str) printf("%s\n", str)
#define ms(n, m) memset(n, m, sizeof(n))

struct node
{
    intl r, cnt;
}lz[4 * 254321][3];

char ch;
int l, r, n;
intl value, st[4 * 254321];

void clear(int idx)
{
    for(int i = 0; i < 3; ++i)
        lz[idx][i].r = lz[idx][i].cnt = 0;
}

void push(intl ss, intl se, intl idx)
{
    if(ss != se)
    {
        if(lz[idx][2].cnt)
        {
            clear(2 * idx + 1), clear(2 * idx + 2);

            lz[2 * idx + 1][2].r = lz[2 * idx + 2][2].r = lz[idx][2].r;
            lz[2 * idx + 1][2].cnt = lz[2 * idx + 2][2].cnt = lz[idx][2].cnt;
        }

        for(int i = 0; i < 2; ++i)
        {
            lz[2 * idx + 1][i].r += lz[idx][i].r;
            lz[2 * idx + 1][i].cnt += lz[idx][i].cnt;

            lz[2 * idx + 2][i].r += lz[idx][i].r;
            lz[2 * idx + 2][i].cnt += lz[idx][i].cnt;
        }
    }

    intl cur = (se - ss + 1);

    if(lz[idx][2].cnt)
        st[idx] = cur * lz[idx][2].r;

    intl var = (((se + 2) * (se + 1)) - (ss * (ss + 1))) / 2;

    st[idx] += (var + cur) * lz[idx][0].cnt - lz[idx][0].r * cur;
    st[idx] += lz[idx][1].r * cur - (var - cur) * lz[idx][1].cnt;

    clear(idx);
}

void update(intl ss, intl se, intl qs, intl qe, intl idx)
{
    push(ss, se, idx);

    if(ss > qe || qs > se)
        return;

    if(qs <= ss && qe >= se)
    {
        if(ch == 'C')
        {
            clear(idx);
            lz[idx][2].r = value;
            lz[idx][2].cnt = 1;
        }
        else if(ch == 'A')
            lz[idx][0].r += l, ++lz[idx][0].cnt;
        else
            lz[idx][1].r += r, ++lz[idx][1].cnt;

        push(ss, se, idx);

        return;
    }

    int mid = (ss + se) / 2;

    update(ss, mid, qs, qe, 2 * idx + 1);
    update(mid + 1, se, qs, qe, 2 * idx + 2);

    st[idx] = st[2 * idx + 1] + st[2 * idx + 2];
}

intl query(int ss, int se, int qs, int qe, int idx)
{
    push(ss, se, idx);

    if(se < qs || qe < ss)
        return 0;

    if(qs <= ss && qe >= se)
        return st[idx];

    int mid = (ss + se) / 2;

    intl l = query(ss, mid, qs, qe, 2 * idx + 1);
    intl r = query(mid + 1, se, qs, qe, 2 * idx + 2);

    st[idx] = st[2 * idx + 1] + st[2 * idx + 2];

    return (l + r);
}

int main()
{
    int test, cs = 1;
    sf(test);

    while(test--)
    {
        for(int i = 0; i < 4 * 254310; ++i)
            clear(i), st[i] = 0;

        sf(n);

        printf("Case %d:\n", cs++);

        for(int i = 0; i < n; ++i)
        {
            sc(ch);

            sf(l), sf(r);

            intl seg = 249999;

            if(ch == 'S')
                pl(query(0, (int) seg, l - 1, r - 1, 0));
            else if(ch == 'C')
                sl(value);

            if(ch != 'S')
                update(0, seg, l - 1, r - 1, 0);
        }
    }

    
    return 0;
}