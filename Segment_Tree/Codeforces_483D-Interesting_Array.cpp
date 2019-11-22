#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool isGood;
vector < pair<pair<int, int>, int> > vec;
int n, m, l, r, q, arr[maxn], cnt[maxn][33], st[4 * maxn];

void build(int ss, int se, int idx)
{
    int mid = (ss + se) / 2;

    if (ss == se)
    {
        st[idx] = arr[ss];
        return;
    }

    build(ss, mid, 2 * idx + 1);
    build(mid + 1, se, 2 * idx + 2);
    st[idx] = st[2 * idx + 1] & st[2 * idx + 2];
}

int query(int ss, int se, int qs, int qe, int idx)
{
    if (qe < ss || se < qs)
        return ((1 << 30) - 1);

    if (qs <= ss && qe >= se)
        return st[idx];

    int mid = (ss + se) / 2;

    return (query(ss, mid, qs, qe, 2 * idx + 1) & query(mid + 1, se, qs, qe, 2 * idx + 2));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m, isGood = true;

    for (int i = 0; i < m; ++i)
    {
        cin >> l >> r >> q, vec.push_back({ {l - 1, r - 1}, q });

        for (int j = 0; j < 31; ++j)
        {
            if (q & (1 << j))
                ++cnt[l - 1][j], --cnt[r][j];
        }
    }

    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < 31; ++j)
            cnt[i][j] += cnt[i - 1][j];
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 31; ++j)
        {
            if (cnt[i][j])
                arr[i] |= (1 << j);
        }
    }

    build(0, n - 1, 0);

    for (int i = 0; i < m; ++i)
    {
        if (query(0, n - 1, vec[i].first.first, vec[i].first.second, 0) != vec[i].second)
            isGood = false;
    }

    if (!isGood)
        cout << "NO" << endl;
    else
    {
        cout << "YES" << endl;

        for (int i = 0; i < n; ++i)
            cout << arr[i] << " ";
        cout << endl;
    }

    return 0;
}