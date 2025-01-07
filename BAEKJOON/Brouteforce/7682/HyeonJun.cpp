/*

	* 접근 방식
	- 누군가가 이겼는지 체크
	- 테스트 케이스를 직접 다 겪으며 수정해 나갔음..
		-> 매우 비효율적

	* 실제 필요한 접근 방식
	- 문제를 처음 읽을 때 자세히 이해하기

	* 문제 해답
	- 각 케이스마다 틱택토에서 불가능한 경우를 모두 체크
		1. O가 더 많거나 X가 2개 이상 많이 둔 경우 
		2. 마지막으로 둔 쪽이 이기지 않은 경우
		3. 게임이 끝이 나지 않은 경우 (누구도 이기지 않고, 모든 보드가 채워지지 않음)
	
	* 정리
	- 문제에 대한 이해를 좀 더 자세히 할 것
		- 테스트 케이스를 참고

*/


#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;
string board;

bool vertical[3] = { false, };
bool Horizontal[3] = { false, };
bool diagonal[2] = { false, };

int x = 0, o = 0;

void Solve();

int main()
{
	
	while (true)
	{
		cin >> board;

		if (board == "end")
			break;

		for (int i = 0; i < board.size(); i++)
		{
			if (board[i] == 'X')
				x++;
			else if (board[i] == 'O')
				o++;
		}

		Solve();

		x = 0; o = 0;
	}

	return 0;
}

void Solve()
{
	int idx = 0;
	bool XWin = false;
	bool OWin = false;

	if (o > x || x > o + 1)
	{
		cout << "invalid" << "\n";
		return;
	}

	// Horizontal
	for (int i = 0; i < board.size(); i += 3)
	{
		if (board[i + 1] != board[i])
			continue;

		if (board[i + 2] != board[i + 1])
			continue;

		Horizontal[idx++] = true;

		if (board[i] == 'O')
			OWin = true;
		else if (board[i] == 'X')
			XWin = true;
	}

	// Vertical
	idx = 0;
	for (int i = 0; i < 3; i++)
	{
		if (board[i + 3] != board[i])
			continue;

		if (board[i + 6] != board[i + 3])
			continue;

		vertical[idx++] = true;

		if (board[i] == 'O')
			OWin = true;
		else if (board[i] == 'X')
			XWin = true;
	}

	// diagonal
	idx = 0;
	if (board[0] == board[4] && board[4] == board[8])
	{
		diagonal[idx++] = true;

		if (board[0] == 'O')
			OWin = true;
		else if (board[0] == 'X')
			XWin = true;
	}

	if (board[2] == board[4] && board[4] == board[6])
	{
		diagonal[idx++] = true;

		if (board[2] == 'O')
			OWin = true;
		else if (board[2] == 'X')
			XWin = true;
	}

	if (x == o && XWin)
	{
		cout << "invalid" << "\n";
		return;
	}
	
	if (x == o + 1 && OWin)
	{
		cout << "invalid" << "\n";
		return;
	}

	if ((!XWin && !OWin) && (o != 4 || x != 5))
	{
		cout << "invalid" << "\n";
		return;
	}
	
	cout << "valid" << "\n";
}

