#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define maxn 100010
#define ints size_t
#define pbk push_back
#define intl long long
#define mod 1000000007
#define pi 2 * acos(0.0)

#define sf(n) scanf("%d", &n)
#define sd(n) scanf("%lf", &n)
#define sl(n) scanf("%lld", &n)
#define sc(c) scanf(" %c", &c)
#define ss(str) scanf("%s", str)
#define pc(c) printf("%c\n", c)
#define pf(n) printf("%d\n", n)
#define pd(n) printf("%lf\n", n)
#define pl(n) printf("%lld\n", n)
#define ps(str) printf("%s\n", str)
#define ms(n, m) memset(n, m, sizeof(n))

vector < pair<intl, intl> > vec;

intl ans;
int n, m, x, y;

bool check(int p, int q, int u, int v)
{
    if(p < u && q >= v)
        return true;
    else if(p > u && q <= v)
        return true;

    return false;
}

int upper(int p, int q)
{
    int high = vec.size() - 1, low = 0, mid, ret = -1;

    while(high >= low)
    {
        int mid = (high + low) / 2;

        if(check(p, q, vec[mid].x, vec[mid].y))
            ret = mid, low = mid + 1;
        else if(vec[mid].x < p && vec[mid].y < q)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return ret;
}

int lower(int p, int q)
{
    int high = vec.size() - 1, low = 0, mid, ret = -1;

    while(high >= low)
    {
        int mid = (high + low) / 2;

        if(check(p, q, vec[mid].x, vec[mid].y))
            ret = mid, high = mid - 1;
        else if(vec[mid].x < p && vec[mid].y < q)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return ret;
}

int main()
{
    int test, cs = 1;
    sf(test);

    while(test--)
    {
        sf(n), sf(m), ans = 0;

        for(int i = 0; i < n; ++i)
        {
            sf(x), sf(y);

            vec.pbk({x, y});
        }

        sort(vec.begin(), vec.end());

        for(int i = 0; i < m; ++i)
        {
            sf(x), sf(y);

            int u = upper(x, y), l = lower(x, y);

            if(u == -1 || l == -1)
                continue;

            ans += (intl) (u - l + 1);
        }

        printf("Case %d: %lld\n", cs++, ans);

        vec.clear();
    }

    /*cin.clear();
    cin.ignore();
    cin.get();*/
    return 0;
}