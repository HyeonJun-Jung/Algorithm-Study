#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

int N;
vector<vector<int>> board;
vector<vector<int>> AreaBoard;

void Divide(int baseX, int baseY, int d1, int d2);

int main()
{
	cin >> N;

	board.resize(N + 1, vector<int>(N + 1));
	AreaBoard.resize(N + 1, vector<int>(N + 1));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> board[i][j];

	Divide(2, 4, 2, 2);

	return 0;
}

void Divide(int baseX, int baseY, int d1, int d2)
{
	int currentX; int currentY;
	int topX, bottomX;

	// 1번 경계선
	for (int i = 0; i <= d1; i++)
	{
		currentX = baseX + i; currentY = baseY - i;

		if (currentX <= 0 || currentX > N || currentY <= 0 || currentY > N)
			continue;

		AreaBoard[currentX][currentY] = 5;
	}

	// 2번 경계선
	for (int i = 0; i <= d2; i++)
	{
		currentX = baseX + i; currentY = baseY + i;

		if (currentX <= 0 || currentX > N || currentY <= 0 || currentY > N)
			continue;

		AreaBoard[currentX][currentY] = 5;
	}

	// 3번 경계선
	for (int i = 0; i <= d2; i++)
	{
		currentX = baseX + d1 + i; currentY = baseY -d1 + i;

		if (currentX <= 0 || currentX > N || currentY <= 0 || currentY > N)
			continue;

		AreaBoard[currentX][currentY] = 5;
	}

	// 4번 경계선
	for (int i = 0; i <= d1; i++)
	{
		currentX = baseX + d2 + i; currentY = baseY + d2 - i;

		if (currentX <= 0 || currentX > N || currentY <= 0 || currentY > N)
			continue;

		AreaBoard[currentX][currentY] = 5;
	}

	// 5번 선거구
	queue<pair<int, int>> que;
	for (int i = 1; i <= N; i++)
	{
		bool find = false;
		for (int j = 1; j <= N; j++)
		{
			currentX = i; currentY = j;

			if (currentX <= 0 || currentX > N || currentY <= 0 || currentY > N)
				continue;

			if (!find && AreaBoard[i][j] == 5)
			{
				find = true;
			}
			else if (find && AreaBoard[i][j] == 5)
			{
				break;
			}

			if(find)
				que.push({ i,j });
		}

		if (find)
		{

		}

		while (!que.empty())
		{
			currentX = que.front().first; currentY = que.front().second;
			que.pop();
			AreaBoard[currentX][currentY] = 5;
		}
	}


	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (AreaBoard[r][c] == 5)
				continue;

			if (1 <= r && r < baseX + d1 && 1 <= c && c <= baseY)
			{
				AreaBoard[r][c] = 1;
			}
			else if (1 <= r && r <= baseX + d2 && baseY < c && c <= N)
			{
				AreaBoard[r][c] = 2;
			}
			else if (baseX + d1 <= r && r <= N && 1 <= c && c < baseY - d1 + d2)
			{
				AreaBoard[r][c] = 3;
			}
			else if (baseX + d2 < r && r <= N && baseY - d1 + d2 <= c && c <= N)
			{
				AreaBoard[r][c] = 4;
			}
		}
	}
}

void FindAnswer()
{

}
