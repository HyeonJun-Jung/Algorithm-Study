/*
	*접근법
	- BFS로 접근

	*개선할 점
	- https://www.acmicpc.net/source/88634698
	- Tuple을 사용했으면 더 좋았을 듯.
		- auto[_Z, _Y, _X] = que.front();
	- Day를 계산할 때, board를 날짜로 이용했으면 더 좋았을 듯
*/


#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;

int M, N, H;
int board[100][100][100];
int ans = 0;
int n = 0;

queue<pair<int, pair<int, pair<int, int>>>> que;

int dirZ[6] = {1, -1, 0, 0, 0, 0};
int dirY[6] = { 0, 0, 1, -1, 0, 0 };
int dirX[6] = { 0, 0, 0, 0, 1, -1 };

void BFS();

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> M >> N >> H;

	for (int i = 0; i < H; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < M; k++)
			{
				cin >> board[i][j][k];

				if (board[i][j][k] == 0)
				{
					n++;
				}
				else if (board[i][j][k] == 1)
				{
					que.push({ 0, { i, {j, k} } });
				}
			}

	BFS();

	if (n == 0)
		cout << ans;
	else
		cout << "-1";
}

void BFS()
{
	int day, currentZ, currentY, currentX, nextZ, nextY, nextX;
	pair<int, pair<int, pair<int, int>>> current;
	pair<int, pair<int, int>> position;

	while (!que.empty())
	{
		pair<int, pair<int, pair<int, int>>> current = que.front();
		que.pop();

		day = current.first; position = current.second;
		currentZ = position.first; currentY = position.second.first; currentX = position.second.second;

		for (int i = 0; i < 6; i++)
		{
			nextZ = currentZ + dirZ[i]; nextY = currentY + dirY[i]; nextX = currentX + dirX[i];

			if (nextZ < 0 || nextZ >= H || nextY < 0 || nextY >= N || nextX < 0 || nextX >= M)
				continue;
			
			if (board[nextZ][nextY][nextX] == 0)
			{
				n--;

				if (n == 0)
				{
					ans = day + 1;
					return;
				}

				board[nextZ][nextY][nextX] = 1;
				que.push({ day + 1, { nextZ, {nextY, nextX} } });
			}
		}
	}
}