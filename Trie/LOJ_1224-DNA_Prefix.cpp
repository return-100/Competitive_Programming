#include <bits/stdc++.h>

using namespace std;

string str;
int n, nxt, idx, ans, trie[2500002][4], cnt[2500002][4];

int get_idx(char ch)
{
    if (ch == 'A') {
        return 0;
    }
    else if (ch == 'C') {
        return 1;
    }
    else if (ch == 'G') {
        return 2;
    }
    else {
        return 3;
    }
}

void insert(int val, int cur_sz)
{
    if (trie[nxt][val] == -1) {
        trie[nxt][val] = ++idx;
    }

    cnt[nxt][val] += 1;
    ans = max(ans, cur_sz * cnt[nxt][val]);
    nxt = trie[nxt][val];
}

int main()
{
    int t, cs = 1;
    cin >> t;

    while (t--) {
        memset(trie, -1, sizeof(trie));
        memset(cnt, 0, sizeof(cnt));

        cin >> n;

        idx = 0;
        ans = 0;

        for (int i = 0; i < n; ++i) {
            cin >> str;
            
            nxt = 0;

            for (int j = 0; j < str.size(); ++j) {
                insert(get_idx(str[j]), j + 1);
            }
        }

        cout << "Case " << cs++ << ": " << ans << endl;
    }

    return 0;
}