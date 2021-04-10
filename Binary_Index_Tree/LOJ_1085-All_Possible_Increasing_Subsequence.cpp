#include <bits/stdc++.h>
 
using namespace std;
 
#define endl "\n"
#define maxn 100010
#define ints size_t
#define i64 long long
#define mod 1000000007
 
#define sf(n) scanf("%d", &n)
#define pf(n) printf("%d\n", n)
#define sc(c) scanf(" %c ", &c)
#define sl(n) scanf("%lld", &n)
#define ss(str) scanf("%s", str)
#define pl(n) printf("%lld\n", n)
#define ms(n, m) memset(n, m, sizeof(n))
 
map <i64, i64> mp;
vector <i64> vec;
i64 n, ans, arr[maxn], bit[maxn];
 
void update(int idx, i64 val)
{
    while(idx <= n)
        bit[idx] += val, idx += (idx & -idx);
}
 
i64 query(int idx)
{
    i64 ret = 0;
 
    while(idx > 0)
        ret += bit[idx], idx -= (idx & -idx);
 
    return ret;
}
 
int main()
{
    int test, cs = 1;
    sf(test);
 
    while(test--)
    {
        ms(bit, 0);
 
        sl(n), ans = 0;
 
        for(int i = 0; i < n; ++i)
            sl(arr[i]), vec.push_back(arr[i]);
 
        sort(vec.begin(), vec.end());
 
        for(ints i = 0; i < vec.size(); ++i)
            mp[vec[i]] = i + 1;
 
        for(int i = 0; i < n; ++i)
        {
            i64 idx = mp[arr[i]];
            i64 temp = query(idx - 1);
            update(idx, (temp + 1) % mod);
            ans = (ans + temp + 1) % mod;
        }
 
        printf("Case %d: %lld\n", cs++, ans);
 
        vec.clear(), mp.clear();
    }
 
    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}