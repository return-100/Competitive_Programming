#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

vector < pair<int, int> > vec, wec[2 * maxn];
int n, m, k, pos, cur, sz, arr[2 * maxn], ans[2 * maxn], st[8 * maxn];

void update(int ss, int se, int qs, int qe, int idx)
{
    if (ss > qe || qs > se)
        return;

    if (ss == se && se == qs)
    {
        ++st[idx];
        return;
    }

    int mid = (ss + se) / 2;

    update(ss, mid, qs, qe, 2 * idx + 1);
    update(mid + 1, se, qs, qe, 2 * idx + 2);

    st[idx] = st[2 * idx + 1] + st[2 * idx + 2];
}

int query(int ss, int se, int pos, int idx)
{
    int mid = (ss + se) / 2;

    if (ss == se)
        return ss;

    if (st[2 * idx + 1] >= pos)
        return query(ss, mid, pos, 2 * idx + 1);
    else
        return query(mid + 1, se, pos - st[2 * idx + 1], 2 * idx + 2);
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n, cur = n - 1, sz;

    for (int i = 0; i < n; ++i)
        cin >> arr[i], vec.push_back({ arr[i], -i });

    cin >> m;

    for (int i = 0; i < m; ++i)
        cin >> k >> pos, wec[k].push_back({ pos, i });

    sort(vec.begin(), vec.end());

    for (int i = 0; i < 2 * maxn; ++i)
    {
        if (wec[i].size() > 0)
        {
            while (sz < i && cur >= 0)
                ++sz, update(0, n - 1, -1 * vec[cur].second, -1 * vec[cur].second, 0), --cur;

            for (int j = 0; j < (int)wec[i].size(); ++j)
                ans[wec[i][j].second] = arr[query(0, n - 1, wec[i][j].first, 0)];
        }
    }

    for (int i = 0; i < m; ++i)
        cout << ans[i] << endl;

    return 0;
}