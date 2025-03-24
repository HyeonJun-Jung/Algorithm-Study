#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>

using namespace std;

int N, K;

struct Jewel
{
	Jewel() {};
	Jewel(int inValue, int inWeight) : value(inValue), weight(inWeight) {};
	int value, weight;
};

struct JewelValueComp
{
	bool operator() (const Jewel& s1, const Jewel& s2)
	{
		return s1.value > s2.value;
	}
};

bool JewelWeightComp(const Jewel& s1, const Jewel& s2)
{
	return s1.weight < s2.weight;
}


struct Bag
{
	Bag() {};
	Bag(int inMaxWeight, int inValue = 0) : maxWeight(inMaxWeight), value(inValue){};
	int maxWeight, value;
};

bool BagComp(const Bag& s1, const Bag& s2)
{
	return s1.maxWeight < s2.maxWeight;
};

vector<Jewel> jewels;
vector<Bag> bags;

int maxWeight;

int main()
{
	cin >> N >> K;

	int val, wgt;
	for (int i = 0; i < N; i++)
	{
		cin >> wgt >> val;
		jewels.push_back(Jewel(val, wgt));
	}

	bags.resize(K, 0);
	for (int i = 0; i < K; i++)
	{
		cin >> bags[i].maxWeight;
	}

	sort(jewels.begin(), jewels.end(), JewelWeightComp);
	sort(bags.begin(), bags.end(), BagComp);

	priority_queue<int> pq;
	int idx = 0; long sum = 0;
	for (int i = 0; i < K; i++)
	{
		while (idx < N && bags[i].maxWeight >= jewels[idx].weight)
		{
			pq.push(jewels[idx].value);
			idx++;
		}

		if (!pq.empty())
		{
			sum += pq.top();
			pq.pop();
		}
	}

	for (int i = 0; i < K; i++)
	{
		sum += bags[i].value;
	}

	cout << sum;

	return 0;
}