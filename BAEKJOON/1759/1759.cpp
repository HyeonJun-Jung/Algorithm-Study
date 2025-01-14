/*
	*접근법
	- 백트래킹을 이용하여 모든 경우의 수 탐색

	*틀린 점
	- 답을 사전 순으로 출력해야 함
	- 자음 2개 모음 1개 안지킴
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int L, C;
vector<char> alp;
vector<bool> selected;

void FindAns(int idx, int con, int vow);

int main()
{
	cin >> L >> C;

	alp.resize(C); selected.resize(C);
	for (int i = 0; i < C; i++)
		cin >> alp[i];

	sort(alp.begin(), alp.end());

	FindAns(0, 0, 0);
}

void FindAns(int idx, int con, int vow)
{
	if (con >= 2 && vow >= 1 && con + vow == L)
	{
		for (int i = 0; i < idx; i++)
		{
			if (selected[i])
				cout << alp[i];
		}
		cout << "\n";
		return;
	}

	if (idx >= alp.size())
		return;
	
	// idx selected
	selected[idx] = true;
	if (alp[idx] == 'a' || alp[idx] == 'e' || alp[idx] == 'i' || alp[idx] == 'o' || alp[idx] == 'u')
	{
		FindAns(idx + 1, con , vow + 1);
	}
	else
	{
		FindAns(idx + 1, con + 1, vow);
	}
	selected[idx] = false;

	// Non Select
	FindAns(idx + 1, con, vow);
}