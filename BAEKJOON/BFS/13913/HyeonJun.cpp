/*
	BFS로 접근해서 쉽게 푼 문제
*/

#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;

int N, K;
int parents[100001] = { 0, };
int board[100001] = { 0, };

void bfs();
void findAns(int current);

int main()
{
	cin >> N >> K;

	bfs();

	cout << board[K] << "\n";
	findAns(K);
}

void bfs()
{
	queue<int> que;
	que.push(N);

	while (!que.empty())
	{
		int current = que.front();
		que.pop();

		if (current == K)
			break;

		if (current - 1 >= 0 && board[current - 1] == 0)
		{
			board[current - 1] = board[current] + 1;
			parents[current - 1] = current;
			que.push(current - 1);
		}

		if (current + 1 <= 100000 && board[current + 1] == 0)
		{
			board[current + 1] = board[current] + 1;
			parents[current + 1] = current;
			que.push(current + 1);
		}

		if (current * 2 <= 100000 && board[current * 2] == 0)
		{
			board[current * 2] = board[current] + 1;
			parents[current * 2] = current;
			que.push(current * 2);
		}
	}
}

void findAns(int current)
{
	if (current != N)
	{
		findAns(parents[current]);
	}
	
	cout << current << " ";
}