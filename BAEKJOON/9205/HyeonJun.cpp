/*
	*초기 접근법
	- DFS를 이용한 접근
	- 문제가 애매모호해서 틀림 (제대로 안읽기도 함)
	
	*보편적인 접근법
	- BFS
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int t, n;
vector<pair<int, int>> vertexs;
bool visited[102] = { false, };
bool ans = false;

void dfs(int idx);
void bfs();

int main()
{
	cin >> t;

	for (int caseIdx = 0; caseIdx < t; caseIdx++)
	{
		vertexs.clear();
		for (int i = 0; i <= 101; i++)
			visited[i] = false;

		cin >> n;

		int x, y;
		for (int i = 0; i < n + 2; i++)
		{
			cin >> x >> y;
			vertexs.push_back({ x, y });
		}

		ans = false;
		// dfs(0);
		bfs();

		if (ans)
			cout << "happy\n";
		else
			cout << "sad\n";
	}
}

void dfs(int idx)
{
	visited[idx] = true;

	if (idx == n + 1)
		ans = true;

	if (ans)
		return;

	int x, y, nextx, nexty, dist;

	x = vertexs[idx].first; y = vertexs[idx].second;

	for (int i = 0; i < n + 2; i++)
	{
		if (visited[i])
			continue;

		nextx = vertexs[i].first; nexty = vertexs[i].second;
		dist = abs(nextx - x) + abs(nexty - y);

		if (dist <= 1000)
		{
			dfs(i);
			if (ans)
				return;
		}
	}

	return;
}

void bfs()
{
	queue<int> nodes;
	nodes.push(0);

	while (!nodes.empty())
	{
		int idx = nodes.front();
		nodes.pop();

		visited[idx] = true;

		if (idx == n + 1)
		{
			ans = true;
			return;
		}

		int x = vertexs[idx].first; int y = vertexs[idx].second;

		int nextx, nexty, dist;
		for (int i = 0; i < n + 2; i++)
		{
			if (visited[i])
				continue;

			nextx = vertexs[i].first; nexty = vertexs[i].second;
			dist = abs(x - nextx) + abs(y - nexty);

			if (dist <= 1000)
				nodes.push(i);
		}
	}
}
