#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;
const long long mod1 = 1e9 + 7;
const long long mod2 = 1e9 + 9;

bool eidx[2020];
string t, ss, se;
vector <pair<int, int>> vec;
unordered_map <long long, bool> mp;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> t >> ss >> se;

    for (int i = 0; i < t.size(); ++i)
    {
        bool isGood = false;

        if (i + ss.size() <= t.size())
        {
            for (int j = 0; j < ss.size(); ++j)
            {
                if (t[i + j] != ss[j])
                    break;

                if (j == ss.size() - 1)
                    isGood = true;
            }
        }

        if (isGood)
            vec.push_back({ i, i + ss.size() - 1 });
    }

    for (int i = 0; i < t.size(); ++i)
    {
        bool isGood = false;

        if (i + se.size() <= t.size())
        {
            for (int j = 0; j < se.size(); ++j)
            {
                if (t[i + j] != se[j])
                    break;

                if (j == se.size() - 1)
                    isGood = true;
            }
        }

        if (isGood)
            eidx[i + se.size() - 1] = true;
    }

    int ans = 0;

    for (int i = 0; i < vec.size(); ++i)
    {
        long long hash = 0, hash1 = 0, hash2 = 0;

        for (int j = vec[i].first, k = 0; j < t.size(); ++j, ++k)
        {
            hash1 = (hash1 * 26 + (t[j] - 26)) % mod1;
            hash2 = (hash2 * 26 + (t[j] - 26)) % mod2;
            hash = hash1 * (mod2 + 1) + hash2;

            if (eidx[j] && (j - se.size() + 1) >= vec[i].first && j >= vec[i].second)
            {
                if (!mp[hash])
                    mp[hash] = true, ++ans;
            }
        }
    }

    cout << ans << endl;

    return 0;
}