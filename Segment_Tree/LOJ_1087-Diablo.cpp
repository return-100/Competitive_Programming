#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define maxn 100005
#define i64 long long
#define mod 1000000007

#define pf(n) printf("%d\n", n)
#define sf(n) scanf("%d", &n)
#define ms(n, m) memset(n, m, sizeof(n))

char c;
bool mark[2 * maxn];
int bit[2 * maxn], arr[2 * maxn], n, m, idx = 1;

void remove(int i)
{
    int temp = i;
    while(i <= n + m)
        --bit[i], i += (i & -i);
    mark[temp] = false;
}

void add(int i)
{
    int temp = i;
    while(i <= n + m)
        ++bit[i], i += (i & -i);
    mark[temp] = true;
}

int query(int i)
{
    int ret = 0;
    while(i > 0)
        ret += bit[i], i -= i & -i;
    return ret;
}

int binarySearch(int low, int high, int val)
{
    int mid, check;

    while(low <= high)
    {
        mid = (high + low) / 2;
        check = query(mid);

        if(check == val && mark[mid])
            return mid;
        else if(check == val && mid == low)
            low = mid + 1;
        else if(check == val)
            high = mid - 1;
        else if(check < val)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main()
{
    int t, cnt = 1;
    sf(t);

    while(t--)
    {
        ms(mark, false), ms(bit, 0), idx = 1;

        sf(n), sf(m);
        for(int i = 1; i <= n; ++i)
            sf(arr[idx]), add(idx++);

        printf("Case %d:\n", cnt++);

        for(int i = 0, var; i < m; ++i)
        {
            scanf(" %c ", &c), sf(var);

            if(c == 'c')
            {
                int temp = binarySearch(1, idx - 1, var);

                if(temp == -1)
                    printf("none\n");
                else
                    pf(arr[temp]), remove(temp);
            }
            else
                arr[idx] = var, add(idx++);
        }
    }

    return 0;
}