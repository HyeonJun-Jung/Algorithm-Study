/*
	*나의 접근 방식
	- 현재 위치에서 왼쪽 위에 존재하는 정사각형의 크기를 이용하여 계산
		- 현재 위치에서 for문 이용하여 행 열 확인

	*더 나은 접근 방식
	- 현재 위치에서 왼쪽 위에 존재하는 정사각형의 크기를 이용하여 계산
		- 현재 위치에서 왼쪽, 위쪽 확인 (왼쪽과 위쪽은 현재 위치에서 가장 큰 정사각형에 포함되는 정사각형)
*/


#include <iostream>
#include <stdio.h>

using namespace std;

int N, M;

char board[1002][1002];
int dp[1002][1002] = { 0, };

int main()
{
	int ans = 0;

	cin >> N >> M;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			cin >> board[i][j];

			if (board[i][j] == '1')
			{
				dp[i][j] = 1;
				ans = 1;
			}
		}

	for (int i = 2; i <= N; i++)
	{
		for (int j = 2; j <= M; j++)
		{
			if (board[i][j] == 1) {
				dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
				ans = max(ans, dp[i][j]);
			}
		}
	}

	/*for (int i = 2; i <= N; i++)
		for (int j = 2; j <= M; j++)
		{
			if (board[i][j] == '0')
				continue;

			int size = dp[i - 1][j - 1];

			for (int t = size; t >= 1; t--)
			{
				bool success = true;

				for (int k = i; k >= i - t; k--)
				{
					if (board[k][j] == '0')
					{
						success = false;
						break;
					}
				}

				if (success == false)
					continue;

				for (int k = j; k >= j - t; k--)
				{
					if (board[i][k] == '0')
					{
						success = false;
						break;
					}
				}

				if (success == false)
					continue;

				dp[i][j] = t + 1;
				ans = max(ans, dp[i][j] * dp[i][j]);

				break;
			}
		}*/

	cout << ans;

	return 0;
}