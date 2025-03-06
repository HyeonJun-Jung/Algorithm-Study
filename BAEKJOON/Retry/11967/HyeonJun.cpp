#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;

int N, M;
bool lighted[101][101] = { false, };
bool visited[101][101] = { false, };
int board[101][101] = { 0, };
vector<pair<int, int>> adjs[101][101];

int dirY[4] = { 0, 0, -1, 1 };
int dirX[4] = { -1, 1, 0, 0 };

int ans = 1;

void bfs();
bool canVisit(int startY, int startX, int destY, int destX);

int main()
{
	cin >> N >> M;

	int fromy, fromx, toy, tox;
	while (M--)
	{
		cin >> fromy >> fromx >> toy >> tox;
		adjs[fromy][fromx].push_back({ toy, tox });
	}

	bfs();

	cout << ans;
}

void bfs()
{
	queue<pair<int, int>> que;
	int currentY, currentX, nextY, nextX;

	que.push({ 1,1 });
	visited[1][1] = true;
	lighted[1][1] = true;

	while (!que.empty())
	{
		pair<int, int> current = que.front();
		que.pop();

		currentY = current.first; currentX = current.second;
		
		// light
		for (int i = 0; i < adjs[currentY][currentX].size(); i++)
		{
			nextY = adjs[currentY][currentX][i].first;
			nextX = adjs[currentY][currentX][i].second;

			if (!lighted[nextY][nextX])
			{
				ans++;
				lighted[nextY][nextX] = true;
			}
		}

		// move to light position
		for (int i = 0; i < adjs[currentY][currentX].size(); i++)
		{
			nextY = adjs[currentY][currentX][i].first;
			nextX = adjs[currentY][currentX][i].second;

			if (!visited[nextY][nextX] && canVisit(currentY, currentX, nextY, nextX))
			{
				visited[nextY][nextX] = true;
				que.push({ nextY, nextX });
			}
		}

		// move up down left right
		for (int i = 0; i < 4; i++)
		{
			nextY = currentY + dirY[i]; nextX = currentX + dirX[i];

			if (nextY < 0 || nextY > N || nextX < 0 || nextX > N)
				continue;

			if (lighted[nextY][nextX] && !visited[nextY][nextX])
			{
				visited[nextY][nextX] = true;
				que.push({ nextY, nextX });
			}
		}
	}
}

bool canVisit(int startY, int startX, int destY, int destX)
{
	bool canVisit[101][101] = { false, };
	queue<pair<int, int>> que;
	que.push({ startY, startX });
	canVisit[startY][startX] = true;

	int currentY, currentX, nextY, nextX;
	while (!que.empty())
	{
		pair<int, int> current = que.front();
		que.pop();

		currentY = current.first; currentX = current.second;

		if (currentY == destY && currentX == destX)
		{
			return true;
		}

		for (int i = 0; i < 4; i++)
		{
			nextY = currentY + dirY[i]; nextX = currentX + dirX[i];

			if (nextY < 0 || nextY > N || nextX < 0 || nextX > N)
				continue;

			if (lighted[nextY][nextX] && !canVisit[nextY][nextX])
			{
				canVisit[nextY][nextX] = true;
				que.push({ nextY, nextX });
			}
		}
	}

	return false;
}