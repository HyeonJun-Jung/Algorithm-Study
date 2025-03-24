#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

#define EMPTY -100

int N, M;
int answer = 0;
vector<vector<int>> board;
vector<vector<int>> temp;
vector<vector<bool>> visited;

int dirX[4] = { -1, 1, 0, 0 };
int dirY[4] = { 0, 0, -1, 1 };

struct Block
{
	Block(int inY, int inX) : Y(inY), X(inX)
	{}

	int Y, X;
};

struct BlockCmp
{
	bool operator()(Block A, Block B)
	{
		if (A.Y != B.Y) return A.Y > B.Y;
		return A.X > B.X;
	}
};

struct GroupNode
{
	GroupNode() {};
	GroupNode(int inBaseY, int inBaseX, int inSize, int inRainbow)
		: baseY(inBaseY), baseX(inBaseX), size(inSize), rainbow(inRainbow)
	{}

	int baseY, baseX, size, rainbow;
};

struct GroupCmp
{
	bool operator()(const GroupNode& A, const GroupNode& B)
	{
		if (A.size != B.size) return A.size < B.size;
		if (A.rainbow != B.rainbow) return A.rainbow < B.rainbow;
		if (A.baseY != B.baseY) return A.baseY < B.baseY;
		return A.baseX < B.baseX;
	}
};

void GetLargestGroup(priority_queue<GroupNode, vector<GroupNode>, GroupCmp>& pq);
GroupNode GetGroupNode(int startY, int startX);
void RemoveGroup(GroupNode& group);
void Gravity();
void Turn_Reverse_90();

int main()
{
	cin >> N >> M;

	board.resize(N, vector<int>(N));
	visited.resize(N, vector<bool>(N, false));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];
		}
	}

	priority_queue<GroupNode, vector<GroupNode>, GroupCmp> pq;
	GroupNode LargestGroup;
	while (true)
	{
		GetLargestGroup(pq);
		
		if (pq.empty())
			break;

		LargestGroup = pq.top();

		// Remove Largest Group
		RemoveGroup(LargestGroup);
		answer += LargestGroup.size * LargestGroup.size;
		
		// Gravity -> turn -> Gravity
		Gravity();
		Turn_Reverse_90();
		Gravity();
	}

	cout << answer;

	return 0;
}

void GetLargestGroup(priority_queue<GroupNode, vector<GroupNode>, GroupCmp>& pq)
{
	// reset queue
	while (!pq.empty()) pq.pop();

	for (int i = 0; i < visited.size(); i++)
		fill(visited[i].begin(), visited[i].end(), false);

	GroupNode newGroup;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (board[i][j] == EMPTY || board[i][j] == -1)
				continue;

			if (visited[i][j])
				continue;

			newGroup = GetGroupNode(i, j);
			if (newGroup.baseX == -1 || newGroup.baseY == -1 || newGroup.size <= 1)
				continue;

			pq.push(newGroup);
		}
	}
}

GroupNode GetGroupNode(int startY, int startX)
{
	priority_queue<Block, vector<Block>, BlockCmp> basepq;
	queue<pair<int, int>> que;

	que.push({ startY, startX });
	visited[startY][startX] = true;

	int currentY, currentX, nextY, nextX;
	int size = 1; int rainbow = 0; int color = board[startY][startX];

	if (board[startY][startX] > 0)
		basepq.push(Block({ startY, startX }));

	while (!que.empty())
	{
		currentY = que.front().first; currentX = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			nextY = currentY + dirY[i]; nextX = currentX + dirX[i];

			// out of range
			if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N)
				continue;

			// already visited || EMPTY || Black Block
			if (visited[nextY][nextX] || board[nextY][nextX] == EMPTY ||
				board[nextY][nextX] == -1)
				continue;

			// not rainbow && not Same Color
			else if (board[nextY][nextX] > 0 && board[nextY][nextX] != color)
				continue;

			// rainbow block
			else if (board[nextY][nextX] == 0)
			{
				rainbow++;
			}

			// normal block (Base block)
			else
			{
				basepq.push(Block(nextY, nextX));
			}

			// push & Check Visited
			que.push({ nextY, nextX });
			visited[nextY][nextX] = true;

			// size
			size++;
		}
	}

	for(int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (board[i][j] == 0)
			{
				visited[i][j] = false;
			}
		}

	if (basepq.empty())
	{
		return GroupNode(-1, -1, 0, 0);
	}

	return GroupNode(basepq.top().Y, basepq.top().X, size, rainbow);
}

void RemoveGroup(GroupNode& group)
{
	for(int i = 0; i < visited.size(); i++)
		fill(visited[i].begin(), visited[i].end(), false);

	queue<pair<int, int>> que;
	que.push({ group.baseY, group.baseX });

	int currentY, currentX, nextY, nextX;
	int color = board[group.baseY][group.baseX];
	while (!que.empty())
	{
		currentY = que.front().first; currentX = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			nextY = currentY + dirY[i]; nextX = currentX + dirX[i];

			// out of range
			if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N)
				continue;

			// already visited || EMPTY || Black Block
			if (visited[nextY][nextX] || board[nextY][nextX] == EMPTY ||
				board[nextY][nextX] == -1)
				continue;
			// not rainbow && not Same Color
			else if (board[nextY][nextX] > 0 && board[nextY][nextX] != color)
				continue;

			// push & Check Visited
			que.push({ nextY, nextX });
			visited[nextY][nextX] = true;

			// remove Block
			board[nextY][nextX] = EMPTY;
		}
	}
}

void Gravity()
{
	int currentY, changeY;

	// column
	for (int i = 0; i < N; i++)
	{
		// row
		for (int j = N - 1; j >= 0; j--)
		{
			if (board[j][i] != EMPTY)
				continue;

			currentY = j;

			bool find = false;
			for (int k = j - 1; k >= 0; k--)
			{
				if (board[k][i] == -1)
					break;

				if (board[k][i] >= 0)
				{
					find = true;
					changeY = k;
					break;
				}
			}

			if (find)
			{
				board[currentY][i] = board[changeY][i];
				board[changeY][i] = EMPTY;
			}
		}
	}
}

void Turn_Reverse_90()
{
	temp = board;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			board[N - 1 - j][i] = temp[i][j];
	}
}