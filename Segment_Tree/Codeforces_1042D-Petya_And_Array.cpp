#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

vector <long long> vec[8 * maxn];
long long ans, n, k, arr[2 * maxn], st[8 * maxn];

long long solve(int idx, long long val)
{
    long long ret = 0;
    int low = 0, high = (int) vec[idx].size() - 1;

    while (high >= low)
    {
        int mid = (high + low) / 2;

        if (vec[idx][mid] <= val)
            low = mid + 1;
        else
            ret = (long long) vec[idx].size() - (long long) mid, high = mid - 1;
    }

    return ret;
}

void build(int ss, int se, int idx)
{
    int mid = (ss + se) / 2;

    if (ss == se)
    {
        vec[idx].push_back(arr[ss]);
        return;
    }

    build(ss, mid, 2 * idx + 1);
    build(mid + 1, se, 2 * idx + 2);
    merge(vec[2 * idx + 1].begin(), vec[2 * idx + 1].end(), vec[2 * idx + 2].begin(), vec[2 * idx + 2].end(), back_inserter(vec[idx]));
    sort(vec[idx].begin(), vec[idx].end());
}

long long query(int ss, int se, int qs, int qe, int idx, long long val)
{
    int mid = (ss + se) / 2;
    
    if (ss > qe || se < qs)
        return 0;

    if (qs <= ss && qe >= se)
        return solve(idx, val);

    return query(ss, mid, qs, qe, 2 * idx + 1, val) + query(mid + 1, se, qs, qe, 2 * idx + 2, val);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k, arr[0] = ans = 0;

    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];

        if (i > 0)
            arr[i] += arr[i - 1];
    }

    build(0, n, 0);

    for (int i = 1; i <= n; ++i)
        ans += query(0, n, 0, i - 1, 0, arr[i] - k);

    cout << ans << endl;

    return 0;
}