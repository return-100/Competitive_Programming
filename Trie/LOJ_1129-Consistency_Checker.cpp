#include <bits/stdc++.h>

using namespace std;

string str[101010];
vector < pair<int, int> > vec;
int n, nxt, idx, trie[101010][10];

bool insert(char ch)
{
    bool ret = false;

    if (trie[nxt][ch - '0'] == -1) {
        trie[nxt][ch - '0'] = ++idx;
        ret = true;
    }

    nxt = trie[nxt][ch - '0'];

    return ret;
}

int main()
{
    int t, cnt = 1;
    cin >> t;

    while (t--) {
        idx = 0;
        memset(trie, -1, sizeof(trie));

        cin >> n;

        bool isGood = true;

        for (int i = 0; i < n; ++i) {
            cin >> str[i];
            vec.push_back({ str[i].size(), i });
        }

        sort(vec.begin(), vec.end());

        for (int i = n - 1; i >= 0; --i) {
            nxt = 0;
            int idx = vec[i].second;
            
            if (isGood) {
                bool isOk = false;

                for (int j = 0; j < str[idx].size(); ++j) {
                    if (insert(str[idx][j])) {
                        isOk = true;
                    }
                }

                if (!isOk) {
                    isGood = false;
                }
            }
        }

        if (isGood) {
            cout << "Case " << cnt++ << ": YES" << endl;
        }
        else {
            cout << "Case " << cnt++ << ": NO" << endl;
        }

        vec.clear();
    }

    return 0;
}