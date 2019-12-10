#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool mark[1010][1010];
vector <pair<int, int>> vec;
int n, mx, arr[1010], dp[1010][1010];

int solve(int pre, int cur)
{
    if (cur == n)
        return dp[pre][cur] = arr[pre];

    if (cur == n - 1)
        return dp[pre][cur] = max(arr[pre], arr[cur]);

    if (mark[pre][cur])
        return dp[pre][cur];

    mark[pre][cur] = true;

    int ret = 1e9;

    ret = min(ret, max(arr[pre], arr[cur]) + solve(cur + 1, cur + 2));
    ret = min(ret, max(arr[pre], arr[cur + 1]) + solve(cur, cur + 2));
    ret = min(ret, max(arr[cur], arr[cur + 1]) + solve(pre, cur + 2));

    return dp[pre][cur] = ret;
}

void backTrack(int pre, int cur)
{
    if (cur == n)
    {
        vec.push_back({ pre + 1, -1 });
        return;
    }

    if (cur == n - 1)
    {
        vec.push_back({ pre + 1, cur + 1 });
        return;
    }

    if (max(arr[pre], arr[cur]) + dp[cur + 1][cur + 2] == mx)
        mx -= max(arr[pre], arr[cur]), vec.push_back({ pre + 1, cur + 1 }), backTrack(cur + 1, cur + 2);
    else if (max(arr[pre], arr[cur + 1]) + dp[cur][cur + 2] == mx)
        mx -= max(arr[pre], arr[cur + 1]), vec.push_back({ pre + 1, cur + 2 }), backTrack(cur, cur + 2);
    else
        mx -= max(arr[cur], arr[cur + 1]), vec.push_back({ cur + 1, cur + 2 }), backTrack(pre, cur + 2);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    mx = solve(0, 1);

    cout << mx << endl;

    backTrack(0, 1);

    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i].second == -1)
            cout << vec[i].first << endl;
        else
            cout << vec[i].first << " " << vec[i].second << endl;
    }

    return 0;
}