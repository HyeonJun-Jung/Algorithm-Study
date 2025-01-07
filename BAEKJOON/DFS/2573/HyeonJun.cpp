/*
	*접근 방식
	- 10년동안 현재 빙하의 개수와 DFS에서 Visit한 빙하의 개수 비교

	*틀린 점
	- 10년이 되어도 빙하가 다 녹지 않을 가능성이 존재
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N, M;
int board[301][301];
int tempBoard[301][301];
bool visited[301][301] = { false, };
vector<pair<int, int>> icebergs;

int dirX[4] = { 0, 0, 1, -1 };
int dirY[4] = { 1, -1, 0, 0 };

int dfs(int y, int x);
void timeGo();

int main()
{
	cin >> N >> M;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			cin >> board[i][j];
			tempBoard[i][j] = board[i][j];

			if (board[i][j] > 0)
				icebergs.push_back({ i,j });
		}

	int ans = 0;
	int year = 0;
	while(true)
	{
		timeGo();
		year++;

		if (icebergs.size() == 0)
			break;

		int y = icebergs[0].first; int x = icebergs[0].second;
		int visitedNum = dfs(y, x);
		if (visitedNum != icebergs.size())
		{
			ans = year;
			break;
		}

		for(int j = 0; j < 301; j++)
			memset(visited[j], false, sizeof(bool) * 301);
	}

	cout << ans;

	return 0;
}

int dfs(int y, int x)
{
	visited[y][x] = true;

	int nexty, nextx;
	int visitedNum = 1;

	for (int i = 0; i < 4; i++)
	{
		nexty = y + dirY[i];
		nextx = x + dirX[i];

		if (nexty < 0 || nexty >= N || nextx < 0 || nextx >= M)
			continue;

		if (visited[nexty][nextx])
			continue;

		if (board[nexty][nextx] > 0)
			visitedNum += dfs(nexty, nextx);
	}

	return visitedNum;
}

void timeGo()
{
	int y, x, nexty, nextx;

	vector<pair<int, int>>::iterator iter;

	for (iter = icebergs.begin(); iter != icebergs.end();)
	{
		int count = 0;

		y = iter->first;
		x = iter->second;

		for (int j = 0; j < 4; j++)
		{
			nexty = y + dirY[j];
			nextx = x + dirX[j];
			if (nexty < 0 || nexty >= N || nextx < 0 || nextx >= M)
				continue;

			if (board[nexty][nextx] <= 0)
				count++;
		}

		tempBoard[y][x] -= count;

		if (tempBoard[y][x] <= 0)
		{
			tempBoard[y][x] = 0;
			iter = icebergs.erase(iter);
			continue;
		}
		else
		{
			iter++;
		}
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			board[i][j] = tempBoard[i][j];
}