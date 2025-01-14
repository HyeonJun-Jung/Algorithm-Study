/*
	*접근법
	- BFS 사용하여 해결
	- 초가 바뀔 때 마다 벽을 움직인다.
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

vector<pair<int, int>> walls;
list<pair<int, pair<int, int>>> player;

int dirY[9] = { 0, -1, 1, 0, 0, -1, 1, -1, 1 };
int dirX[9] = {0, 0, 0, -1, 1, -1, -1, 1, 1 };
char board[8][8];
bool check[10][8][8] = { false, };

bool Bfs();
void MoveWalls();

int main()
{
	for(int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			char character;
			cin >> character;

			board[i][j] = character;

			if (character == '#')
			{
				walls.push_back({ i, j });
			}
		}

	bool success = Bfs();

	if (success)
	{
		cout << "1";
	}
	else
	{
		cout << "0";
	}

	return 0;
}

bool Bfs()
{
	int second = 0;
	player.push_back({ second, {7, 0} });

	while (!player.empty())
	{
		pair<int, pair<int, int>> current = player.front();

		if (second != current.first)
		{
			second = current.first;

			MoveWalls();

			if (player.size() == 0)
				return false;

			if (walls.size() == 0 && player.size() > 0)
				return true;
		}

		current = player.front();
		pair<int, int> position = current.second;

		for (int i = 0; i < 9; i++)
		{
			int nextY = position.first + dirY[i];
			int nextX = position.second + dirX[i];

			if (nextY < 0 || nextY >= 8 || nextX < 0 || nextX >= 8)
				continue;

			if (board[nextY][nextX] == '#')
				continue;

			if (check[second + 1][nextY][nextX])
				continue;

			check[second + 1][nextY][nextX] = true;
			player.push_back({ second + 1, {nextY, nextX} });
		}
	
		player.pop_front();
	}

	return false;
}

void MoveWalls()
{
	vector<pair<int, int>>::iterator it;
	list<pair<int, pair<int, int>>>::iterator playerIter;

	for (it = walls.begin(); it != walls.end(); it++)
	{
		board[it->first][it->second] = '.';
	}

	for (it = walls.begin(); it != walls.end();)
	{
		it->first += 1;

		if (it->first >= 8)
		{
			it = walls.erase(it);
		}
		else
		{
			// check wall meet player
			for (playerIter = player.begin(); playerIter != player.end();)
			{
				if (it->first == playerIter->second.first 
					&& it->second == playerIter->second.second)
				{
					playerIter = player.erase(playerIter);
				}
				else
					playerIter++;
			}

			it++;
		}
	}

	for (it = walls.begin(); it != walls.end(); it++)
	{
		board[it->first][it->second] = '#';
	}
}