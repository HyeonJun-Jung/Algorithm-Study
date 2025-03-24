#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits.h>

using namespace std;

int R, C;

// 0 : empty   1 : wall
vector<vector<int>> board;
vector<vector<bool>> visited;

int dirY[3] = { -1, 0, 1 };
int dirX[3] = { 1, 1, 1 };

bool dfs(int y, int x);

int main()
{
	cin >> R >> C;

	board.resize(R, vector<int>(C + 2));
	visited.resize(R, vector<bool>(C + 2, false));

	string str;
	for (int i = 0; i < R; i++)
	{
		cin >> str;
		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] == '.')
			{
				board[i][j] = 0;
			}
			else
			{
				board[i][j] = 1;
			}
		}
	}

	int answer = 0;
	for (int i = 0; i < R; i++)
	{
		if (dfs(i, 0))
			answer++;
	}

	cout << answer;

	return 0;
}

bool dfs(int y, int x)
{
	if (x == C + 1)
	{
		return true;
	}

	int nextY, nextX;
	for (int i = 0; i < 3; i++) 
	{
		nextY = y + dirY[i]; nextX = x + dirX[i];

		if (nextY < 0 || nextY >= R)
			continue;

		// Wall or Visited
		if (board[nextY][nextX] == 1 || visited[nextY][nextX])
			continue;

		visited[nextY][nextX] = true;
		if (dfs(nextY, nextX))
		{
			return true;
		}
	}

	return false;
}