#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int N;
	cin >> N;

	vector<pair<int, int>> array(N, { 0, 0 });
	vector<pair<int, int>> orderAry;

	int input;

	for (int i = 0; i < N; i++)
	{
		cin >> input;
		orderAry.push_back(make_pair(input, i));
	}

	sort(orderAry.begin(), orderAry.end());

	for (int i = 0; i < N; i++)
	{
		array[i].first = orderAry[i].second;
	}

	for (int i = 1; i < N; i++)
	{
		if (orderAry[i].first != orderAry[i - 1].first)
		{
			array[i].second = array[i - 1].second + 1;
		}
		else
		{
			array[i].second = array[i - 1].second;
		}
	}

	sort(array.begin(), array.end());

	for (int i = 0; i < N; i++)
		cout << array[i].second << " ";

	return 0;
}