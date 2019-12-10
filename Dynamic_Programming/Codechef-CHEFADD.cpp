#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int test, a, b, c, dp[2][33][33][33];

int solve(int val, int isCarry, int idx, int cnta, int cntb)
{
    if (val == 0)
        return (cnta == 0 && cntb == 0 && !isCarry) ? 1 : 0;
    
    if (idx > 29)
        return 0;
    
    if (dp[isCarry][idx][cnta][cntb] != -1)
        return dp[isCarry][idx][cnta][cntb];
    
    int ret = 0;
    
    if (c & (1 << idx))
    {
        if (isCarry)
            ret += solve(val ^ (1 << idx), 0, idx + 1, cnta, cntb);
            
        if (isCarry && cnta && cntb)
            ret += solve(val ^ (1 << idx), 1, idx + 1, cnta - 1, cntb - 1);
        
        if (!isCarry && cnta)
            ret += solve(val ^ (1 << idx), 0, idx + 1, cnta - 1, cntb);
        
        if (!isCarry && cntb)
            ret += solve(val ^ (1 << idx), 0, idx + 1, cnta, cntb - 1);
    }
    else
    {
        if (!isCarry)
            ret += solve(val, 0, idx + 1, cnta, cntb);
        
        if (!isCarry && cnta && cntb)
            ret += solve(val, 1, idx + 1, cnta - 1, cntb - 1);
        
        if (isCarry && cnta)
            ret += solve(val, 1, idx + 1, cnta - 1, cntb);
        
        if (isCarry && cntb)
            ret += solve(val, 1, idx + 1, cnta, cntb - 1);
    }
    
    return dp[isCarry][idx][cnta][cntb] = ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> test;
    
    while (test--)
    {
        memset(dp, -1, sizeof(dp));
        
        cin >> a >> b >> c;
        
        cout << solve(c, 0, 0, __builtin_popcount(a), __builtin_popcount(b)) << endl;
    }
     
    return 0;
}
