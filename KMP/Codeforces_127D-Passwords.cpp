#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

string str;
int ans, midMax, sz, lcp[10 * maxn];

void preprocess()
{
    int idx = 1, jdx = 0;

    while (idx < sz)
    {
        while (jdx > 0 && str[idx] != str[jdx])
            jdx = lcp[jdx - 1];

        if (str[idx] == str[jdx])
            lcp[idx] = jdx + 1, ++jdx;

        if (idx < sz - 1)
            midMax = max(midMax, lcp[idx]);

        ++idx;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> str, sz = (int)str.size();

    preprocess();

    if (midMax >= lcp[sz - 1])
        ans = lcp[sz - 1];
    else if (lcp[sz - 1] && lcp[lcp[sz - 1] - 1])
        ans = lcp[lcp[sz - 1] - 1];

    if (ans)
        cout << str.substr(0, ans) << endl;
    else
        cout << "Just a legend" << endl;

    return 0;
}