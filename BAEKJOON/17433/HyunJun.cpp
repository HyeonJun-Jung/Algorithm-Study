/*
	*처음 접근법
	- 정수의 범위가 2000까지라고 생각하고 2~2000까지 탐색
		- 정수의 범위는 -1,000,000,000 ~ 1,000,000,000
	- 매우 비효율적

	*필요한 접근법
	- 차이의 최대 공약수 이용 (gcd)
	- 특정 수 k로 나누었을 때, 나머지가 같은 수
		a % k = x
		b % k = x
		(a - b) % k = 0 
		-> (a - b)는 k의 배수 
		-> 두 수의 차이가 k의 배수일 때, a와 b를 K로 나눈 나머지가 같음
		-> 두 수의 차이들의 최대 공약수 (모든 수를 K로 나눈 나머지가 같아야 함)

	*배운 점
	- gcd
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, N;
vector<int> nums;
vector<int> diffs;

int GCD(int x, int y)
{
	if (x % y == 0) return y;
	return GCD(y, x % y);
}

int main()
{
	cin >> T;

	while(T--)
	{
		nums.clear();
		diffs.clear();

		cin >> N;

		int num;
		for (int i = 0; i < N; i++)
		{
			cin >> num;
			nums.push_back(num);
		}

		sort(nums.begin(), nums.end());

		for (int i = 1; i < N; i++)
		{
			if(nums[i] - nums[i - 1] > 0)
				diffs.push_back(nums[i] - nums[i - 1]);
		}

		if (diffs.empty())
		{
			cout << "INFINITY\n";
			continue;
		}
		
		int ans = diffs[0];
		for (int i = 1; i < diffs.size(); i++)
		{
			ans = GCD(ans, diffs[i]);
		}

		/*for (int i = 2; i <= 2000; i++)
		{
			int remain = nums[0] % i;
			bool success = true;

			for (int j = 1; j < nums.size(); j++)
			{
				if (remain != nums[j] % i)
				{
					success = false;
					break;
				}
			}

			if (success)
			{
				ans = i;
			}
		}*/

		cout << ans << "\n";
	}

	return 0;
}