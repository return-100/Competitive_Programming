/*
This is a SOS-DP. Relatively tough to come up with the idea.
There is a good tutorial on this in the link below -------->
https://codeforces.com/blog/entry/45223
There is a memory efficient code in the link but i cannot
get the proper idea how he implement that.
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

string str;
bool isGood[(1 << 20) + 1];
int n, ans, arr[(1 << 20) + 1], dp[(1 << 20) + 1][22];
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> str, n = (int) str.size();

    for (int i = 0; i < n; ++i)
    {
        int mask = 0, bit = 0;

        for (int j = i; j < n; ++j)
        {
            bit = str[j] - 97;

            if (mask & (1 << bit))
                break;

            mask |= (1 << bit);
            isGood[mask] = true;
            dp[mask][0] = j - i + 1; //base condition for sub-set dp
        }
    }

    for (int mask = 0; mask < (1 << 20); ++mask) // this loop goes through all possible mask which is not calculated so far
    {
        for (int i = 1; i <= 20; ++i) // start with 1 cause base case stored at index 0
        {
            if (mask & (1 << (i - 1)))
                dp[mask][i] = max(dp[mask][i - 1], dp[mask ^ (1 << (i - 1))][i - 1]);
            else
                dp[mask][i] = dp[mask][i - 1];
        }

        arr[mask] = dp[mask][20]; // result stored for current mask stored in arr
    }

    for (int mask = 0; mask < (1 << 20); ++mask)
    {
        if (isGood[mask])
            ans = max(ans, arr[mask] + arr[mask ^ ((1 << 20) - 1)]);
    }

    cout << ans << endl;

    return 0;
}