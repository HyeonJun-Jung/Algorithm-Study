/*
	*처음 접근법
	- 앞에서부터 동적 계획법을 사용해나감
	- 불가능?

	*옳은 접근법
	- dp[i] = values[i];
	- dp[i] = max(dp[i + 1], dp[i] + dp[finDate]);

	*느낀점
	- 동적 계획법을 사용할 때, 역방향 순으로 하는 것이 훨씬 편할 때가 많은 것 같다.
	- 점화식을 먼저 세우고 코드를 작성하자.
*/

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> durations;
vector<int> values;
int dp[1500001] = { 0, };

int main()
{
	cin >> N;

	int duration, value;
	for (int i = 0; i < N; i++)
	{
		cin >> duration >> value;
		durations.push_back(duration);
		values.push_back(value);
	}

	int finDate;
	for (int i = N - 1; i >= 0; i--)
	{
		finDate = i + durations[i];

		if (i + durations[i] < N + 1)
		{
			dp[i] = values[i];
			dp[i] = max(dp[i + 1], dp[i] + dp[finDate]);
		}
		else
		{
			dp[i] = dp[i + 1];
		}
	}

	cout << dp[0];

	return 0;
}