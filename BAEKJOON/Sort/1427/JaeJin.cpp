#include <iostream>
#include <string>

using namespace std;

int main()
{
	string input;
	cin >> input;

	int array[10] = { 0, };

	for (int i = 0; i < input.size(); i++)
	{
		int num = input[i] - 48;
		array[num]++;
	}

	for (int i = 9; i >= 0; i--)
	{
		int count = array[i];

		for (int j = 0; j < count; j++)
			cout << i;
	}

}