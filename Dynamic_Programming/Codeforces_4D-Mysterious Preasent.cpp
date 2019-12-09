#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

int w, h;
vector <short int> ans;
vector <int> idx;
pair <int, int> arr[5002];
short int n, tot, dp[5002][5002];
vector <pair<int, short int>> vec[1000010];

short int getNext(int val, short int cur)
{
    short int high = vec[idx[cur]].size() - 1, low = 0, mid, ret = -1;

    while (high >= low)
    {
        mid = (high + low) / 2;

        if (vec[idx[cur]][mid].first > val)
            ret = vec[idx[cur]][mid].second, high = mid - 1;
        else
            low = mid + 1;
    }

    return ret;
}

short int solve(short int pre, short int cur)
{
    if (cur == n)
        return dp[pre][cur] = 0;

    if (dp[pre][cur] != -1)
        return dp[pre][cur];

    short int ret = solve(pre, cur + 1);

    if (pre == 0)
        ret = max(ret, (short int)(1 + solve(vec[idx[cur]][0].second, cur + 1)));
    else
    {
        short int nxt = getNext(arr[pre].second, cur);

        if (nxt != -1)
            ret = max(ret, (short int)(1 + solve(nxt, cur + 1)));
    }

    return dp[pre][cur] = ret;
}

void backtrack(short int pre, short int cur)
{
    if (cur == n || tot == 0)
        return;

    if (dp[pre][cur + 1] == tot)
        backtrack(pre, cur + 1);
    else if (pre == 0 && 1 + dp[vec[idx[cur]][0].second][cur + 1] == tot)
        ans.push_back(vec[idx[cur]][0].second), --tot, backtrack(vec[idx[cur]][0].second, cur + 1);
    else
        ans.push_back(getNext(arr[pre].second, cur)), --tot, backtrack(getNext(arr[pre].second, cur), cur + 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(dp, -1, sizeof(dp));

    cin >> n >> w >> h;

    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i + 1].first >> arr[i + 1].second;

        if (arr[i + 1].first > w&& arr[i + 1].second > h)
            vec[arr[i + 1].first].push_back({ arr[i + 1].second, i + 1 });
    }

    for (int i = w + 1; i < 1000000; ++i)
    {
        if (vec[i].size() > 0)
            sort(vec[i].begin(), vec[i].end()), idx.push_back(i);
    }

    n = idx.size();

    tot = solve(0, 0);
    backtrack(0, 0);

    cout << ans.size() << endl;

    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << " ";
    cout << endl;

    return 0;
}

/*
7 1 1
2 4
4 3
5 6
5 7
6 2
7 8
8 3
*/