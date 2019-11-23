#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

string str;
vector <pair<int, int>> vec;
int sz, cnt[maxn], lcp[maxn];

void preprocess()
{
    int j = 0;

    for (int i = 1; i < sz; ++i)
    {
        while (j > 0 && str[i] != str[j])
            j = lcp[j - 1];

        if (str[i] == str[j])
            lcp[i] = j + 1, ++j;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> str;

    sz = (int)str.size();
    preprocess();

    for (int i = 1; i <= sz; ++i)
        ++cnt[lcp[i]];

    for (int i = sz - 1; i >= 0; --i)
        cnt[lcp[i - 1]] += cnt[i];

    int idx = sz;

    while (idx)
        vec.push_back({ idx, cnt[idx] }), idx = lcp[idx - 1];

    cout << vec.size() << endl;

    for (int i = (int)vec.size() - 1; i >= 0; --i)
        cout << vec[i].first << " " << vec[i].second + 1 << endl;

    return 0;
}