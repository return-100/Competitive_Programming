#include <bits/stdc++.h>
 
using namespace std;
 
#define endl "\n"
#define maxn 100010
#define i64 long long
#define mod 1000000007
 
#define pf(n) printf("%d\n", n)
#define sf(n) scanf("%d", &n)
#define ms(n, m) memset(n, m, sizeof(n))
 
int n, m, st[4 * maxn][3], lz[4 * maxn];
 
void rotation(int idx)
{
    int temp = st[idx][2];
 
    st[idx][2] = st[idx][1];
    st[idx][1] = st[idx][0];
    st[idx][0] = temp;
}
 
void build(int ss, int se, int idx)
{
    if(ss == se)
    {
        st[idx][0] = 1;
        return;
    }
 
    int mid = (ss + se) / 2;
 
    build(ss, mid, 2 * idx + 1);
    build(mid + 1, se, 2 * idx + 2);
 
    st[idx][0] = st[2 * idx + 1][0] + st[2 * idx + 2][0];
}
 
void update(int ss, int se, int qs, int qe, int idx)
{
    if(lz[idx])
    {
        lz[idx] %= 3;
 
        for(int i = 0; i < lz[idx]; ++i)
            rotation(idx);
 
        if(ss != se)
            lz[2 * idx + 1] += lz[idx], lz[2 * idx + 2] += lz[idx];
 
        lz[idx] = 0;
    }
 
    if(ss > qe || se < qs)
        return;
 
    if(qs <= ss && qe >= se)
    {
        lz[idx] += 1, lz[idx] %= 3;
 
        for(int i = 0; i < lz[idx]; ++i)
            rotation(idx);
 
        if(ss != se)
            lz[2 * idx + 1] += lz[idx], lz[2 * idx + 2] += lz[idx];
 
        lz[idx] = 0;
 
        return;
    }
 
    int mid = (ss + se) / 2;
 
    update(ss, mid, qs, qe, 2 * idx + 1);
    update(mid + 1, se, qs, qe, 2 * idx + 2);
 
    st[idx][0] = st[2 * idx + 1][0] + st[2 * idx + 2][0];
    st[idx][1] = st[2 * idx + 1][1] + st[2 * idx + 2][1];
    st[idx][2] = st[2 * idx + 1][2] + st[2 * idx + 2][2];
}
 
int query(int ss, int se, int qs, int qe, int idx)
{
    if(lz[idx])
    {
        lz[idx] %= 3;
 
        for(int i = 0; i < lz[idx]; ++i)
            rotation(idx);
 
        if(ss != se)
            lz[2 * idx + 1] += lz[idx], lz[2 * idx + 2] += lz[idx];
 
        lz[idx] = 0;
    }
 
    if(ss > qe || se < qs)
        return 0;
 
    if(qs <= ss && qe >= se)
        return st[idx][0];
 
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
 
        sf(n), sf(m);
 
        build(0, n - 1, 0);
 
        printf("Case %d:\n", cs++);
 
        for(int i = 0; i < m; ++i)
        {
            int q, l, r;
           
            sf(q), sf(l), sf(r);
 
            if(!q)
                update(0, n - 1, l, r, 0);
            else
                pf(query(0, n - 1, l, r, 0));
        }
    }
 
    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}