#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

int answer = INT_MAX;
int N, M;
vector<vector<int>> board;
vector<pair<int, int>> houses;
vector<pair<int, int>> stores;
vector<vector<int>> chickenDists;
vector<int> MinChickenDists;
vector<bool> selected;

void CalculateChickenDists();
void BruteForce(int current, int numOfSelected);

int main()
{
	cin >> N >> M;

	board.resize(N, vector<int>(N));

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];

			if (board[i][j] == 1)
				houses.push_back({ i,j });
			else if (board[i][j] == 2)
				stores.push_back({ i,j });
		}
	}

	selected.resize(stores.size());
	MinChickenDists.resize(houses.size(), INT_MAX);

	CalculateChickenDists();
	BruteForce(0, 0);

	cout << answer;

	return 0;
}

void CalculateChickenDists()
{
	chickenDists.resize(houses.size(), vector<int>(stores.size()));

	for (int i = 0; i < houses.size(); i++)
	{
		for (int j = 0; j < stores.size(); j++)
		{
			chickenDists[i][j] =
				abs(houses[i].first - stores[j].first) + abs(houses[i].second - stores[j].second);
		}
	}
}

void BruteForce(int current, int numOfSelected)
{
	if (numOfSelected == M)
	{
		int sum = 0;

		fill(MinChickenDists.begin(), MinChickenDists.end(), INT_MAX);

		for (int i = 0; i < selected.size(); i++)
		{
			if (!selected[i])
				continue;

			for (int j = 0; j < MinChickenDists.size(); j++)
				MinChickenDists[j] = min(MinChickenDists[j], chickenDists[j][i]);
		}

		for (int i = 0; i < MinChickenDists.size(); i++)
		{
			sum += MinChickenDists[i];
		}

		answer = min(answer, sum);

		return;
	}

	for (int i = current; i < stores.size(); i++)
	{
		selected[i] = true;
		BruteForce(i + 1, numOfSelected + 1);
		selected[i] = false;
	}
}