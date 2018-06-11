#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>

typedef int Type;

//先排序，然后找n/2位置，一定就是出现次数大于一半的
Type Find1(Type* arr, int n) 
{

}

//
Type Find(Type* ID, int N)
{
	Type candidate;
	int nTimes, i;
	for (i = nTimes = 0; i < N; i++)
	{
		if (nTimes == 0)
		{
			candidate = ID[i], nTimes = 1;
		}
		else
		{
			if (candidate == ID[i])
				nTimes++;
			else
				nTimes--;
		}
	}
	return candidate;
}


int main()
{


	return 0;
}