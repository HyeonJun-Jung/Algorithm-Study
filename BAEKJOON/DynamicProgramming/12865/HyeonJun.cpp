/*
	동적 계획법을 오랜만에 풀어서 그런가 영혼까지 탈탈 털린 문제..

	처음 접근법
	- 동적 계획법으로 풀어야겠다고 생각했으나, 실제로 구현한 건 dfs
	- 각 물건마다 분기를 나눠가며 무게를 계산 -> 시간 초과 명백 (2^100)
	
	실제 필요한 접근법
	- dp를 이용하여 이전에 계산된 value 써먹기
	- dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - curWeight] + curValue);

	느낀 점
	- 동적 계획법 관련 문제를 더 풀어봐야겠음.. 아직 감이 잘 안오는 듯
*/

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int N, K;
vector<int> weights;
vector<int> values;

int maxWeights = 0;
int dp[101][100001] = { 0, };

void solve();

int main()
{
	int weight, value;

	cin >> N >> K;

	for (int i = 0; i < N; i++)
	{
		cin >> weight >> value;

		weights.push_back(weight);
		values.push_back(value);
	}

	solve();

	return 0;
}

void solve()
{
	for (int i = 1; i <= N; i++)
	{
		int curWeight = weights[i - 1];
		int curValue = values[i - 1];

		for (int j = 1; j <= K; j++)
		{
			if (curWeight > j)
			{
				dp[i][j] = dp[i - 1][j];
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - curWeight] + curValue);
			}
		}
	}

	cout << dp[N][K];
}