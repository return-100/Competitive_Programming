#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 101010;
const long long mod = 1e9 + 7;
 
int n;
bool mark[2][1010][1010];
long long dp[2][1010][1010];
 
long long solve(int isGood, int x, int y)
{
    if ((x == y && x == n) || y > x || x > n || y > n)
        return 0;
 
    if (mark[isGood][x][y])
        return dp[isGood][x][y];
 
    mark[isGood][x][y] = true;
 
    if (isGood)
        dp[isGood][x][y] = (1 + solve(0, x + 1, y) % mod + solve(0, x, y + 1) % mod) % mod;
    else
        dp[isGood][x][y] = (solve(1, x + 1, y) % mod + solve(1, x, y + 1) % mod) % mod;
 
    return dp[isGood][x][y];
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    cin >> n;
 
    cout << solve(0, 0, 0) % mod << endl;
 
    return 0;
}
