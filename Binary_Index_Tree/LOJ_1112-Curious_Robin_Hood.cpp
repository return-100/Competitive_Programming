#include <bits/stdc++.h>
 
using namespace std;
 
#define endl "\n"
#define maxn 100005
#define i64 long long
#define mod 1000000007
 
#define ms(n, m) memset(n, m, sizeof(n))
 
int arr[maxn], bit[maxn], n, m;
 
int sum(int idx)
{
    int result = 0;
 
    while(idx > 0)
        result += bit[idx], idx -= (idx & -idx);
 
    return result;
}
 
void remove(int idx, int val)
{
    while(idx <= n)
        bit[idx] -= val, idx += (idx & -idx);
}
 
void add(int idx, int val)
{
    while(idx <= n)
        bit[idx] += val, idx += (idx & -idx);
}
 
void init()
{
    for(int i = 0; i < n; ++i)
        add(i + 1, arr[i]);
}
 
int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);*/
 
    int t, cnt = 1;
    scanf("%d", &t);
 
    while(t--)
    {
        ms(bit, 0);
       
        scanf("%d %d", &n, &m);
 
        for(int i = 0; i < n; ++i)
            scanf("%d", &arr[i]);
 
        init();
 
        printf("Case %d:\n", cnt++);
 
        for(int i = 0; i < m; ++i)
        {
            int d, l, r;
            scanf("%d", &d);
 
            if(d == 1)
                scanf("%d", &l), remove(l + 1, arr[l]), printf("%d\n", arr[l]), arr[l] = 0;
            else if(d == 2)
                scanf("%d %d", &l, &r), arr[l] += r, add(l + 1, r);
            else
                scanf("%d %d", &l, &r), printf("%d\n", sum(r + 1) - sum(l));
        }
    }
 
    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}