#include <bits/stdc++.h>

using namespace std;

#define i64 long long
#define endl "\n"
#define maxn 100005
#define mod 1000000007

i64 n, arr[35000], segtree[maxn], range;

i64 middle(i64 ss, i64 se)
{
    return ss + (se - ss) / 2;
}

i64 minVal(i64 x, i64 y)
{
    if(x == -1) return y;
    if(y == -1) return x;

    return arr[x] < arr[y] ? x : y;
}

i64 RMQ(i64 ss, i64 se, i64 qs, i64 qe, i64 pos)
{
    if(qs <= ss && qe >= se)
        return segtree[pos];

    if(se < qs || ss > qe)
        return -1;

    int mid = middle(ss, se);

    return minVal(RMQ(ss, mid, qs, qe, 2 * pos + 1), RMQ(mid + 1, se, qs, qe, 2 * pos + 2));
}

i64 build(i64 start, i64 end, i64 pos)
{
    i64 mid = middle(start, end);

    if(start == end)
    {
        segtree[pos] = end;
        return segtree[pos];
    }

    segtree[pos] = minVal(build(start, mid, 2 * pos + 1), build(mid + 1, end, 2 * pos + 2));

    return segtree[pos];
}

i64 solve(i64 qs, i64 qe, i64 n)
{
    if(qs > qe)
        return INT_MIN;
    if(qs == qe)
        return arr[qs];

    int idx = RMQ(0, n - 1, qs, qe, 0);

    return max(solve(qs, idx - 1, n), max(solve(idx + 1, qe, n), (qe - qs + 1) * arr[idx]));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    i64 t, cnt = 1;
    cin >> t;

    while(t--)
    {
        cin >> n;

        range = (1 << (int) ceil(log2(n))) - 1;

        for(int i = 0; i < n; ++i)
            cin >> arr[i];

        build(0, n - 1, 0);

        cout << "Case " << cnt++ << ": " << solve(0, n - 1, n) << endl;
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}