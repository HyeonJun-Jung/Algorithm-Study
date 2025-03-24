#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>

using namespace std;

int N, M, X;

vector<bool> visited;
vector<vector<pair<int, int>>> edges;
vector<int> nodeWeights;

int dfs(int current, int dest, int totalWeight);
int dijkstra(int from, int to);

int main()
{
	cin >> N >> M >> X;

	edges.resize(N + 1, vector<pair<int, int>>());
	visited.resize(N + 1);
	nodeWeights.resize(N + 1);

	int from, to, weight;
	for (int i = 1; i <= M; i++)
	{
		cin >> from >> to >> weight;
		edges[from].push_back({ to, weight });
	}

	int maxValue = 0;
	for (int i = 1; i <= N; i++)
	{
		// maxValue = max(maxValue, dfs(i, X, 0) + dfs(X, i, 0));
		maxValue = max(maxValue, dijkstra(i, X) + dijkstra(X, i));
	}

	cout << maxValue;

	return 0;
}

int dfs(int current, int dest, int totalWeight)
{
	if (current == dest)
	{
		return totalWeight;
	}

	int minValue = INT_MAX;
	int nextNode, edgeWeight;
	for (int i = 0; i < edges[current].size(); i++)
	{
		nextNode = edges[current][i].first; edgeWeight = edges[current][i].second;

		if (visited[nextNode])
			continue;
		
		visited[nextNode] = true;
		minValue = min(minValue, dfs(nextNode, dest, totalWeight + edgeWeight));
		visited[nextNode] = false;
	}

	return minValue;
}

int dijkstra(int from, int to)
{
	fill(nodeWeights.begin(), nodeWeights.end(), INT_MAX);

	nodeWeights[from] = 0;

	// {cost, node}
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, from });

	int curCost, cur, nextCost, next;
	while (!pq.empty())
	{
		curCost = pq.top().first; cur = pq.top().second;
		pq.pop();

		for (int i = 0; i < edges[cur].size(); i++)
		{
			next = edges[cur][i].first; nextCost = edges[cur][i].second;

			if (nodeWeights[next] > curCost + nextCost)
			{
				nodeWeights[next] = curCost + nextCost;
				pq.push({ nodeWeights[next] , next });
			}
		}
	}

	return nodeWeights[to];
}