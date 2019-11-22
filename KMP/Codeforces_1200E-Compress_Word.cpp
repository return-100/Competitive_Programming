#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 101010;
 
string str, ptr, ans;
int n, lcp[10 * maxn];
 
void failureFunction()
{
    for (int i = 1, j = 0; i < (int)ptr.size(); ++i)
    {
        while (j > 0 && ptr[i] != ptr[j])
            j = lcp[j - 1];
 
        if (ptr[i] == ptr[j])
            lcp[i] = j + 1, ++j;
    }
}
 
void solve(int sz)
{
    int start = max(0, (int)ans.size() - sz), curSz = 0;
 
    for (int i = start; i < (int)ans.size(); ++i)
        ptr += ans[i], ++curSz;
 
    failureFunction();
 
    start = min(lcp[(int)ptr.size() - 1], curSz);
 
    for (int i = start; i < (int)str.size(); ++i)
        ans += str[i];
 
    for (int i = 0; i < (int)ptr.size(); ++i)
        lcp[i] = 0;
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    cin >> n, ans = "";
 
    for (int i = 0; i < n; ++i)
    {
        cin >> str, ptr = str + '$';
        solve((int)str.size());
    }
 
    cout << ans << endl;
 
    return 0;
}