/*
	*접근법
	- 동적 계획법를 이용하여 접근 : dp[초][이동횟수][위치]
		if (fall[i] == 1)
		{
			dp[i][j][0] = max(dp[i - 1][j][0] + 1, dp[i - 1][j - 1][1] + 1);
			dp[i][j][1] = dp[i - 1][j][1];
		}
		else
		{
			dp[i][j][0] = dp[i - 1][j][0];
			dp[i][j][1] = max(dp[i - 1][j][1] + 1, dp[i - 1][j - 1][0] + 1);
		}
	- 현재 위치가 1일 때와 2일 때를 구분하여 작성
	- 1초는 따로 처리해줌 (1초 넣을 시, W 인덱스 범위 OUT) 
*/

#include <stdio.h>
#include <iostream>

using namespace std;

int T, W;
int fall[1001] = { 0, };
int dp[1001][31][2] = { 0, };

int main()
{
	cin >> T >> W;

	for (int i = 1; i <= T; i++)
		cin >> fall[i];

	if (fall[1] == 1)
		dp[1][0][0] = 1;
	else
		dp[1][1][1] = 1;

	for (int i = 2; i <= T; i++)
	{
		if (fall[i] == 1)
		{
			dp[i][0][0] = dp[i - 1][0][0] + 1;
		}
		else
		{
			dp[i][0][0] = dp[i - 1][0][0];
		}

		for (int j = 1; j <= W; j++)
		{
			if (fall[i] == 1)
			{
				dp[i][j][0] = max(dp[i - 1][j][0] + 1, dp[i - 1][j - 1][1] + 1);
				dp[i][j][1] = dp[i - 1][j][1];
			}
			else
			{
				dp[i][j][0] = dp[i - 1][j][0];
				dp[i][j][1] = max(dp[i - 1][j][1] + 1, dp[i - 1][j - 1][0] + 1);
			}

		}
	}

	int ans = 0;
	for (int i = 0; i <= W; i++)
	{
		ans = max(ans, dp[T][i][0]);
		ans = max(ans, dp[T][i][1]);
	}

	cout << ans;

	return 0;
}