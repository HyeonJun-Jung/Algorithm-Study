/*
	* 초기 접근 방식
	- dfs를 통해서 dp 최종 결과 도출
	- 비트마스킹 사용

	* 잘못한 점
	- 탑 다운 방식으로 최종 결과를 얻어와야 하는데 바텀 업 방식으로 최종 결과를 도출하려고 함.
		- 바텀 업 방식으로 dfs를 진행하면 메모이제이션을 사용하기가 어렵다
		-> 탑 다운 방식으로 진행
	
	* 최종 접근 방식
	- 점화식 : dp[current][mask] = min(dp[current][mask], values[current][i] + dfs_(i, mask | (1 << i)));
	- 메모이제이션 : dp[current][mask] != -1 를 통해 이미 계산된 결과는 스킵
	- 비트마스킹 : 

*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

#define INF 1000000000

int N;
vector<vector<int>> values;
vector<vector<int>> dp;

void dfs(int current, int mask, int cost);
int dfs_(int current, int mask);

int main()
{
	cin >> N;

	int k = (1 << N) - 1;

	values.resize(N, vector<int>(N, 0));
	dp.resize(N, vector<int>(k + 1, -1));

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> values[i][j];

	// dfs(0, 0, 0);
	// cout << dp[0][k];

	cout << dfs_(0, 1);

	return 0;
}

// 잘못된 방식
void dfs(int current, int mask, int cost)
{
	if (dp[current][mask] < cost || dp[0][(1 << N) - 1] < cost)
		return;

	dp[current][mask] = min(dp[current][mask], cost);

	if (dp[current][mask] != -1)
		return;

	if (current == 0 && (mask & (1 << 0)) > 0)
	{
		return;
	}

	// dp 
	for (int i = 0; i < values[current].size(); i++)
	{
		if (values[current][i] == 0 || (mask & (1 << i)) > 0) continue;

		mask = mask | (1 << i);
		dfs(i, mask, cost + values[current][i]);
		mask = mask & ~(1 << i);
	}
}

// 옳게된 방식
int dfs_(int current, int mask)
{
	// visit StartPoint
	if (mask == (1 << N) - 1)
	{
		if (values[current][0] > 0)
			return values[current][0];
		else
			return INF;
	}

	// Already Calculated
	if (dp[current][mask] != -1)
		return dp[current][mask];

	// Calculate
	dp[current][mask] = INF; 
	for (int i = 0; i < values[current].size(); i++)
	{
		if (values[current][i] == 0 || (mask & (1 << i)) > 0) continue;

		// dp[current][mask] is Value "from current to 0" with mask 
		dp[current][mask] = min(dp[current][mask], values[current][i] + dfs_(i, mask | (1 << i)));
	}

	return dp[current][mask];
}