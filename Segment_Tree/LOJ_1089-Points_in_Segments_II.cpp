#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define maxn 100005
#define i64 long long
#define mod 1000000007

#define pf(n) printf("%d\n", n)
#define sf(n) scanf("%d", &n)
#define ms(n, m) memset(n, m, sizeof(n))

map <int, int> mp;
map <int, bool> mark;
vector < pair<int, int> > vec(50000);
int n, m, l, r, idx, counter, seg[5 * maxn], arr[5 * maxn], qrr[50000];

int main()
{
    int t, cnt = 1;
    sf(t);

    while(t--)
    {
        ms(seg, 0), ms(arr, 0);
        sf(n), sf(m), counter = 0, idx = 0;

        for(int i = 0; i < n; ++i)
        {
            sf(vec[i].first), sf(vec[i].second);

            if(!mark[vec[i].first])
                arr[idx++] = vec[i].first, mark[vec[i].first] = true;
            if(!mark[vec[i].second])
                arr[idx++] = vec[i].second, mark[vec[i].second] = true;
        }

        for(int i = 0; i < m; ++i)
        {
            sf(qrr[i]);

            if(!mark[qrr[i]])
                arr[idx++] = qrr[i], mark[qrr[i]] = true;
        }

        sort(arr, arr + idx);

        for(int i = 0; i < idx; ++i)
            mp[arr[i]] = counter, counter += 2;

        for(int i = 0; i < n; ++i)
        {
            ++seg[mp[vec[i].first]];
            --seg[mp[vec[i].second] + 1];
        }

        for(int i = 1; i < counter; ++i)
            seg[i] += seg[i - 1];

        printf("Case %d:\n", cnt++);

        for(int i = 0; i < m; ++i)
            pf(seg[mp[qrr[i]]]);

        mp.clear();
        vec.clear();
        mark.clear();
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define maxn 100005
#define i64 long long
#define mod 1000000007

#define pf(n) printf("%d\n", n)
#define sf(n) scanf("%d", &n)
#define ms(n, m) memset(n, m, sizeof(n))

map <int, int> mp;
map <int, bool> mark;
vector < pair<int, int> > vec(50000);
int n, m, l, r, idx, counter, seg[5 * maxn], arr[5 * maxn], qrr[50000];

int main()
{
    int t, cnt = 1;
    sf(t);

    while(t--)
    {
        ms(seg, 0), ms(arr, 0);
        sf(n), sf(m), counter = 0, idx = 0;

        for(int i = 0; i < n; ++i)
        {
            sf(vec[i].first), sf(vec[i].second);

            if(!mark[vec[i].first])
                arr[idx++] = vec[i].first, mark[vec[i].first] = true;
            if(!mark[vec[i].second])
                arr[idx++] = vec[i].second, mark[vec[i].second] = true;
        }

        for(int i = 0; i < m; ++i)
        {
            sf(qrr[i]);

            if(!mark[qrr[i]])
                arr[idx++] = qrr[i], mark[qrr[i]] = true;
        }

        sort(arr, arr + idx);

        for(int i = 0; i < idx; ++i)
            mp[arr[i]] = counter, counter += 2;

        for(int i = 0; i < n; ++i)
        {
            ++seg[mp[vec[i].first]];
            --seg[mp[vec[i].second] + 1];
        }

        for(int i = 1; i < counter; ++i)
            seg[i] += seg[i - 1];

        printf("Case %d:\n", cnt++);

        for(int i = 0; i < m; ++i)
            pf(seg[mp[qrr[i]]]);

        mp.clear();
        vec.clear();
        mark.clear();
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}