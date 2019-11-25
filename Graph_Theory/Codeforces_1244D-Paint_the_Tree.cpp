#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

bool isBad;
int n, color[maxn];
long long ans, arr[maxn][4], dp[4][4][maxn];
vector <int> vec[maxn];

long long dfs(int pre, int cur, int u, int par)
{
	if (dp[pre][cur][u] != -1)
		return dp[pre][cur][u];

	int nxt_color;
	long long sum = 0;

	for (int i = 1; i <= 3; ++i)
	{
		if (i != pre && i != cur)
			nxt_color = i;
	}

	for (int i = 0; i < (int)vec[u].size(); ++i)
	{
			if (vec[u][i] != par)
				sum += dfs(cur, nxt_color, vec[u][i], u);
	}

	sum += arr[u][cur];
	
	if ((int) vec[u].size() - 1 > 1)
		isBad = true;

	return dp[pre][cur][u] = sum;
}

void solve(int pre, int cur, int u, int par)
{
	color[u] = cur;
	int nxt_color;

	for (int i = 1; i <= 3; ++i)
	{
		if (i != pre && i != cur)
			nxt_color = i;
	}

	for (int i = 0; i < (int)vec[u].size(); ++i)
	{
		if (vec[u][i] != par)
			solve(cur, nxt_color, vec[u][i], u);
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(dp, -1, sizeof(dp));

	cin >> n, ans = LLONG_MAX;

	for (int i = 1; i <= 3; ++i)
	{
		for (int j = 0; j < n; ++j)
			cin >> arr[j][i];
	}

	for (int i = 0; i < n - 1; ++i)
	{
		int u, v;
		cin >> u >> v;
		vec[u - 1].push_back(v - 1);
		vec[v - 1].push_back(u - 1);
	}

	int pre, cur, root;

	for (int i = 0; i < n; ++i)
	{
		if ((int)vec[i].size() == 1)
		{
			root = i;

			for (int k = 1; k <= 3; ++k)
			{
				for (int j = 1; j <= 3; ++j)
				{
					if (k != j)
					{
						if (ans > dfs(j, k, root, -1))
							ans = dp[j][k][root], pre = j, cur = k;
					}
				}
			}
			
			break;
		}
	}

	if (isBad)
		cout << -1 << endl;
	else
	{
		cout << ans << endl;

		solve(pre, cur, root, -1);

		for (int i = 0; i < n; ++i)
			cout << color[i] << " ";
		cout << endl;
	}
	
	return 0;
}