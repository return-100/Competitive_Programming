#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

vector < pair<int, int> > vec;
int n, m, p, s, power[2 * maxn], hst[8 * maxn], mst[8 * maxn];

void build1(int ss, int se, int idx)
{
    int mid = (ss + se) / 2;

    if (ss == se)
    {
        mst[idx] = power[ss];
        return;
    }

    build1(ss, mid, 2 * idx + 1);
    build1(mid + 1, se, 2 * idx + 2);

    mst[idx] = max(mst[2 * idx + 1], mst[2 * idx + 2]);
}

void build2(int ss, int se, int idx)
{
    int mid = (ss + se) / 2;

    if (ss == se)
    {
        hst[idx] = vec[ss].second;
        return;
    }

    build2(ss, mid, 2 * idx + 1);
    build2(mid + 1, se, 2 * idx + 2);

    hst[idx] = max(hst[2 * idx + 1], hst[2 * idx + 2]);
}

int query1(int ss, int se, int qs, int qe, int idx)
{
    if (qe < ss || se < qs)
        return 0;

    if (qs <= ss && qe >= se)
        return mst[idx];

    int mid = (ss + se) / 2;

    return max(query1(ss, mid, qs, qe, 2 * idx + 1), query1(mid + 1, se, qs, qe, 2 * idx + 2));
}

int query2(int ss, int se, int qs, int qe, int idx)
{
    if (qe < ss || se < qs)
        return 0;

    if (qs <= ss && qe >= se)
        return hst[idx];

    int mid = (ss + se) / 2;

    return max(query2(ss, mid, qs, qe, 2 * idx + 1), query2(mid + 1, se, qs, qe, 2 * idx + 2));
}

int get(int pow)
{
    int ret = -1, high = m - 1, low = 0, mid;

    while (high >= low)
    {
        mid = (high + low) / 2;

        if (vec[mid].first >= pow)
            ret = mid, high = mid - 1;
        else
            low = mid + 1;
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--)
    {
        cin >> n;

        for (int i = 0; i < n; ++i)
            cin >> power[i];

        cin >> m;

        for (int i = 0; i < m; ++i)
            cin >> p >> s, vec.push_back({ p, s });

        sort(vec.begin(), vec.end());

        build1(0, n - 1, 0), build2(0, m - 1, 0);

        int idx = 0, day = 0;

        while (idx < n)
        {
            bool isGood = false;
            int nxt, high = n - 1, low = idx, mid;

            while (high >= low)
            {
                mid = (high + low) / 2;

                int mcnt = mid - idx + 1;
                int mpow = query1(0, n - 1, idx, mid, 0);
                int hidx = get(mpow);
                int hind = -1;

                if (hidx != -1)
                    hind = query2(0, m - 1, hidx, m - 1, 0);

                if (hind >= mcnt)
                    isGood = true, nxt = mid + 1, low = mid + 1;
                else
                    high = mid - 1;
            }

            if (isGood)
                day += 1, idx = nxt;
            else
            {
                day = -1;
                break;
            }
        }

        cout << day << endl;
        vec.clear();
    }

    return 0;
}

/*
1
2
1 8
2
3 2
100 1
*/