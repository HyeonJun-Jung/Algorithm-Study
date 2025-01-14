/*
	문제 : https://www.acmicpc.net/problem/20303

	* 처음 접근법
	- BFS 사용


	* 올바른 접근법
	- 냅색(배낭문제), 즉 DP 사용

	- DP에서 0 ~ k - 1 for문을 먼저 사용하면 같은 그룹이 여러번 사용될 수 있음
		-> 이런 경우에는 for문의 순서를 바꾸어보자 ! ! !

	-> 	for (int i = 0; i < sum.size(); i++)		// group을 먼저 for문 -> group 중복 방지 (반대는 안됨)
			for (int j = K; j >= kid; j--)		// 뒤에서부터 검사함으로써 한번 더한 값에 다시 더하지 않도록 방지


	* 배워갈 점
	- 제출 사항을 참고하여 무엇을 잘못하였는가 배우기!
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, K;
vector<int> candies;
vector<vector<int>> adjs;
vector<bool> visited;
vector<int> sum;
vector<int> cry;
vector<int> dp;

void findAns();
void bfs(int start);

int main()
{
	cin >> N >> M >> K;

	candies.resize(N + 1);
	for (int i = 1; i <= N; i++)
		cin >> candies[i];

	adjs.resize(N + 1);
	int x, y;
	for (int i = 0; i < M; i++)
	{
		cin >> x >> y;
		adjs[x].push_back(y); adjs[y].push_back(x);
	}

	findAns();
}

void findAns()
{
	visited.resize(N + 1, false);
	dp.resize(K + 1);

	// bfs
	for (int i = 1; i <= N; i++)
		if (!visited[i])
		{
			bfs(i);
		}

	// dp
	int value, kid;
	for (int i = 0; i < sum.size(); i++)
	{
		value = sum[i]; kid = cry[i];

		for (int j = K - 1; j >= kid; j--)
		{
			dp[j] = max(dp[j], dp[j - kid] + value);
		}

		if (kid < K)
			dp[kid] = max(dp[kid], value);
	}

	int ans = 0;
	for (int i = 1; i < K; i++)
	{
		ans = max(ans, dp[i]);
	}

	/*for (int i = 1; i <= K; i++)
	{
		for (int j = 0; j < sum.size(); j++)
		{
		}
	}*/

	cout << ans;
}

void bfs(int start)
{
	queue<int> que; 

	visited[start] = true;
	que.push(start);

	int current, next;
	int total = 0, c = 0;
	while (!que.empty())
	{
		current = que.front();
		que.pop();

		total += candies[current];
		c += 1;

		for (int i = 0; i < adjs[current].size(); i++)
		{
			next = adjs[current][i];

			if (!visited[next])
			{
				visited[next] = true;
				que.push(next);
			}
		}
	}

	sum.push_back(total);
	cry.push_back(c);

	

	return;
}