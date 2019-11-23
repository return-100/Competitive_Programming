#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool isGood;
string str, ptr;
int ans, k, sz, cur, nxt, idx, arr[26], trie[30 * maxn][26];

void insert(char ch)
{
    if (!trie[nxt][ch - 97])
        trie[nxt][ch - 97] = ++idx;

    nxt = trie[nxt][ch - 97];
}

bool get(char ch)
{
    if (trie[nxt][ch - 97])
    {
        nxt = trie[nxt][ch - 97];
        return true;
    }

    return false;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> str >> ptr >> k, idx = 1, sz = (int)str.size();

    for (int i = 0; i < 26; ++i)
        arr[i] = (ptr[i] == '1' ? 0 : 1);

    for (int i = 0; i < sz; ++i)
    {
        isGood = false, nxt = 1, ptr = "", cur = 0;

        for (int j = i; j < sz; ++j)
        {
            cur += arr[str[j] - 97];

            if (cur > k)
                break;

            if (isGood || !get(str[j]))
                ++ans, insert(str[j]), isGood = true;
        }
    }

    cout << ans << endl;

    return 0;
}