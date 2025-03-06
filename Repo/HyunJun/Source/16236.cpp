/*

	* 개선할 점
	- Fish마다 BFS를 돌려서 가장 가까운 Fish를 찾고있음
	-> BFS를 한번만 돌려서 가장 가까운 Fish를 찾을 수 있다.
	- priorityQueue 사용법 숙지하기

*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

int N;
int SharkY, SharkX, SSize;
vector<vector<int>> board;
vector<pair<int, int>> fishes;
vector<vector<bool>> visited;

int DirY[4] = { -1, 0, 0, 1 };
int DirX[4] = { 0, 1, -1 ,0 };

int EatNearestFishDist(int SSize);
int GetDist(int FishNum);
void ShowBoard(int Dist);

int main()
{
	cin >> N;

	board.resize(N, vector<int>(N));
	visited.resize(N, vector<bool>(N, false));

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];

			if (board[i][j] == 9)
			{
				SharkY = i;
				SharkX = j;
			}
			else if (board[i][j] > 0)
			{
				fishes.push_back({ i,j });
			}
		}
	
	int second = 0; SSize = 2; int count = 0;
	
	while (true)
	{
		int dist = EatNearestFishDist(SSize);
		if (dist == -1)
			break;

		second += dist;
		count++;
		if (count == SSize)
		{
			SSize++;
			count = 0;
		}
	}

	cout << second;

	return 0;
}

int EatNearestFishDist(int SSize)
{
	// Small than Shark 
	vector<int> eatableFishes; int y, x;
	for (int i = 0; i < fishes.size(); i++)
	{
		y = fishes[i].first; x = fishes[i].second;
		if (board[y][x] > 0 && board[y][x] < SSize)
		{
			eatableFishes.push_back(i);
		}
	}

	if (eatableFishes.empty())
		return -1;

	vector<pair<int, int>> fishInfos;
	int minDist = INT_MAX; 
	for (int i = 0; i < eatableFishes.size(); i++)
	{
		int dist = GetDist(eatableFishes[i]);

		if (dist != INT_MAX)
		{
			fishInfos.push_back({ eatableFishes[i], dist });

			minDist = min(minDist, dist);
		}
	}
	
	if (fishInfos.size() == 0)
		return -1;

	// remove not minimum Dist fishes
	vector<pair<int, int>>::iterator iter; int idx = 0;
	for (iter = fishInfos.begin(); iter != fishInfos.end();)
	{
		if (iter->second != minDist)
		{
			iter = fishInfos.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	// sort by Y
	sort(fishInfos.begin(), fishInfos.end(), [&](pair<int,int> a, pair<int, int> b) { return fishes[a.first].first < fishes[b.first].first; });
	for (int i = 0; i < fishInfos.size() - 1; i++)
	{
		if (fishes[fishInfos[i].first].first != fishes[fishInfos[i + 1].first].first)
		{
			fishInfos.resize(i + 1);
			break;
		}
	}

	// sort by X
	sort(fishInfos.begin(), fishInfos.end(), [&](pair<int, int> a, pair<int, int> b) { return fishes[a.first].second < fishes[b.first].second; });

	// Eat Fish
	board[SharkY][SharkX] = 0;
	SharkY = fishes[fishInfos[0].first].first; SharkX = fishes[fishInfos[0].first].second;
	board[SharkY][SharkX] = 9;
	fishes.erase(fishes.begin() + fishInfos[0].first);

	// ShowBoard(fishInfos[0].second);

	return fishInfos[0].second;
}

int GetDist(int FishNum)
{
	pair<int, int>& fish = fishes[FishNum];
	queue<pair<int, pair<int, int>>> que;
	que.push({ 0, { SharkY, SharkX } });

	fill(visited.begin(), visited.end(), vector<bool>(N, false));
	visited[SharkY][SharkX] = true;

	pair<int, int> pos;
	int second = 0; int dist = INT_MAX;
	int nextY, nextX;
	while (!que.empty())
	{
		second = que.front().first;
		pos = que.front().second;

		que.pop();

		if (pos == fish)
		{
			dist = second;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			nextY = pos.first + DirY[i];
			nextX = pos.second + DirX[i];

			if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N)
				continue;

			if (board[nextY][nextX] > SSize || visited[nextY][nextX])
				continue;

			visited[nextY][nextX] = true;

			que.push({ second + 1 ,{ nextY, nextX } });
		}
	}

	return dist;
}

void ShowBoard(int Dist)
{
	cout << "\n";
	cout << "Dist : " << Dist << "   Shark Size : " << SSize << "\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << board[i][j] << " ";

		cout << "\n";
	}
}