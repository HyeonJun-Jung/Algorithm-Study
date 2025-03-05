#include <iostream>

using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N;
	cin >> N;

	int array[10000] = { 0, };

	for (int i = 0; i < N; i++)
	{
		int temp;
		cin >> temp;

		array[temp - 1]++;
	}

	for (int i = 0; i < 10000; i++)
	{
		int count = array[i];

		for (int j = 0; j < count; j++)
		{
			cout << i + 1 << '\n';
		}
	}

	return 0;
}