#include <iostream>
#include <stdio.h>
#include <climits>

using namespace std;

int T, N, M;
int values[20];
int dp[10001];

int main()
{
	cin >> T;

	for (int caseIdx = 0; caseIdx < T; caseIdx++)
	{
		cin >> N;

		for (int i = 0; i < N; i++)
		{
			cin >> values[i];
		}

		cin >> M;


		// init array
		for (int i = 0; i <= M; i++)
			dp[i] = 0;

		dp[0] = 1;
		
		// dynamic Programming
		/*
		for (int i = 1; i <= M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (i - values[j] >= 0 && dp[i - values[j]] != -1)
				{
					dp[i] += dp[i - values[j]];
				}
			}
		}
		*/

		for (int j = 0; j < N; j++)
		{
			for (int i = 1; i <= M; i++)
			{
				if (i - values[j] >= 0)
				{
					dp[i] += dp[i - values[j]];
				}
			}
		}

		cout << dp[M] << "\n";
	}

	return 0;
}