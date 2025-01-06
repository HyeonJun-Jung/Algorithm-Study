/*
	*접근법
	- 동적 계획법을 사용하여 접근
	- dp[i] = min(dp[i], dp[i - values[j]] + 1);

	*틀린점
	- 맨 처음 dp 배열을 -1로 초기화 -> INT_MAX로 초기화
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int N, K;
int dp[10001] = { INT_MAX, };
vector<int> values;

int main()
{
	cin >> N >> K;

	int value;

	for (int i = 0; i < N; i++)
	{
		cin >> value;
		values.push_back(value);
	}

	dp[0] = 0;

	for (int i = 1; i <= K; i++)
	{
		dp[i] = INT_MAX;

		for (int j = 0; j < N; j++)
		{
			if (i - values[j] >= 0 && dp[i - values[j]] != INT_MAX)
				dp[i] = min(dp[i], dp[i - values[j]] + 1);
		}
	}

	if (dp[K] == INT_MAX)
		cout << "-1";
	else
		cout << dp[K];
}