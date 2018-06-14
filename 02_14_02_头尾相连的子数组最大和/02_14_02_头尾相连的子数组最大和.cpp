#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>
#include <YXPUtility>

//解法1:暴力遍历O(N^3)
int MaxSum1(int *arr, int n)
{
	if (arr == nullptr || n <= 0)
		return 0;

	int max = std::numeric_limits<int>::min();

	for (int i = 0; i < n; ++i) //以每一个位置开始
	{
		for (int j = i;;) //以每一个位置结束,这时因为是循环的，就判断回到起始位置为结束
		{
			int curSum = 0;
			for (int k = i;;) //当前开始和结束的子数组之和
			{
				curSum += arr[k];
				k = k == n - 1 ? 0 : ++k;
				if (k == j)
					break;
			}
			curSum += i == j ? 0 : arr[j]; //最后补一个,如果开始和结束不是同一个才补
			max = i == j ? std::max(max, arr[i]) : max; //如果是同一个开始同一个结束的话，上面的只计算了i,i+1,..n-1,i这种，还有一种情况就是自身
			max = std::max(curSum, max);
			j = j == n - 1 ? 0 : ++j;
			if (j == i)
				break;
		}
	}
	return max;
}

//动态规划的解法:就是在原始问题的基础上，添加一个可能是跨越了的情况，就找A[0]开头，和A[n-1]结束的



int main()
{
	//yxp_utility::RandomHelper::initSeed();
	//int nTestTime = 1000;
	//size_t nArrSize = 10;
	//int min = -100, max = 100;

	//for (int i = 0; i < nTestTime; ++i)
	//{
	//	auto v = yxp_utility::RandomHelper::randomArray(nArrSize, min, max);
	//	yxp_utility::ArrayHelper::printArr(v);
	//	auto res = MaxSum1(&v[0], v.size());
	//	std::cout << res << std::endl;
	//}


	std::vector<int> v = { 10,-30,20 };
	auto res = MaxSum1(&v[0], v.size());
	assert(res == 30);
	std::cout << res << std::endl;

	v = { 10,30,-20 };
	res = MaxSum1(&v[0], v.size());
	assert(res == 40);
	std::cout << res << std::endl;

	v = { -10,30,-20 };
	res = MaxSum1(&v[0], v.size());
	assert(res == 30);
	std::cout << res << std::endl;

	v = { -10,-30,-20 };
	res = MaxSum1(&v[0], v.size());
	assert(res == -10);
	std::cout << res << std::endl;

	return 0;
}