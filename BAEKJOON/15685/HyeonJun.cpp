/*
	* 문제 접근법
	- 좌표계에 관한 문제이다. 어떠한 점을 90도 회전시켰을 때 어디에 위치하는 지 파악하는 것이 중요
		- 이것만 제대로 파악한다면 어려운 문제는 아니다. 
		- (x, y)를 시계방향으로 90도 회전시키면 (-y, x)에 위치하게 된다.
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, answer;
vector<vector<int>> board;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, -1, 0, 1 };

void DragonCurve(pair<int, int> start, int d, int g);
void dupTurn(vector<pair<int, int>>& src);
void FindAnswer();


int main()
{
	board.resize(101, vector<int>(101, 0));

	cin >> N;
	
	int x, y, d, g;
	while (N--)
	{
		cin >> x >> y >> d >> g;
		DragonCurve({ x, y }, d, g);
	}

	FindAnswer();
	cout << answer;
}

void DragonCurve(pair<int, int> start, int d, int g)
{
	vector<pair<int, int>> dc;
	dc.push_back({ 0,0 });
	dc.push_back({ dx[d], dy[d] });

	for (int i = 1; i <= g; i++)
	{
		dupTurn(dc);
	}

	int nextX, nextY;
	for (int i = 0; i < dc.size(); i++)
	{
		nextX = start.first + dc[i].first;
		nextY = start.second + dc[i].second;
		if (0 <= nextX && nextX <= 100 && 0 <= nextY && nextY <= 100)
			board[nextX][nextY] = 1;
	}
}

void dupTurn(vector<pair<int, int>>& src)
{
	pair<int, int> end = src[src.size() - 1];
	int size = src.size();

	pair<int, int> pos, gap, next;

	for (int i = size - 2; i >= 0; i--)
	{
		pos = src[i];
		gap = { pos.first - end.first, pos.second - end.second };
		next = { end.first - gap.second , end.second + gap.first };

		src.push_back(next);
	}
}

void FindAnswer()
{
	int dirX[4] = { 0, 0, 1, 1 };
	int dirY[4] = { 0, 1, 0 ,1 };

	int nextX, nextY;
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			bool success = true;

			for (int k = 0; k < 4; k++)
			{
				nextX = i + dirX[k]; nextY = j + dirY[k];
				if (nextX > 100 || nextY > 100 || board[nextX][nextY] == 0)
				{
					success = false;
					break;
				}
			}

			if (success)
				answer++;
		}
	}
}