#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

vector <int> vec;
int n, var, dp[3 * maxn], start_idx[3 * maxn], end_idx[3 * maxn];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    memset(start_idx, -1, sizeof(start_idx));

    while (t--)
    {
        cin >> n, dp[0] = 1;

        for (int i = 0; i < n; ++i)
        {
            cin >> var;

            if (start_idx[var] == -1)
                start_idx[var] = i, vec.push_back(var);

            end_idx[var] = i;
        }

        sort(vec.begin(), vec.end());

        for (int i = 1; i < vec.size(); ++i)
        {
            if (end_idx[vec[i - 1]] > start_idx[vec[i]])
                dp[i] = 1;
            else
                dp[i] = dp[i - 1] + 1;
        }

        int ans = vec.size();

        for (int i = 0; i < (int) vec.size(); ++i)
            ans = min(ans, (int) vec.size() - dp[i]);

        cout << ans << endl;

        for (int i = 0; i < vec.size(); ++i)
            start_idx[vec[i]] = -1;

        vec.clear();
    }

    return 0;
}