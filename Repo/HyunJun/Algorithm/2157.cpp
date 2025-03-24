#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>

using namespace std;

int N, M, K;

// {Toward, point}
vector<vector<pair<int, int>>> edges;
vector<vector<int>> dp;

int Solve(int now, int numOfVisted);

int main()
{
	cin >> N >> M >> K;

	edges.resize(N + 1);
	
	int from, to, value;
	for (int i = 0; i < K; i++)
	{
		cin >> from >> to >> value;
		edges[from].push_back({ to, value });
	}

	dp.resize(N + 1, vector<int>(M + 1, INT_MIN));
	cout << Solve(1, 1);

	return 0;
}

int Solve(int now, int numOfVisted)
{
	if (now == N && numOfVisted <= M)
	{
		return 0;
	}
	else if (numOfVisted > M)
		return INT_MIN;

	if (dp[now][numOfVisted] != INT_MIN)
		return dp[now][numOfVisted];

	dp[now][numOfVisted] = INT_MIN;
	for (int i = 0; i < edges[now].size(); i++)
	{
		if (edges[now][i].first < now)
			continue;
		dp[now][numOfVisted] = max(dp[now][numOfVisted], Solve(edges[now][i].first, numOfVisted + 1) + edges[now][i].second);
	}

	return dp[now][numOfVisted];
}