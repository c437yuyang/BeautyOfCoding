#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>
#include <YXPCommon.h>

//递归版本:
int LISProcess(int *arr, int j);
int LIS(int *arr, int n)
{
	if (arr == nullptr || n <= 0)
		return 0;
	int *dp = new int[n];
	int max = std::numeric_limits<int>::min();
	for (int i = 0; i < n; ++i)
	{
		dp[i] = LISProcess(arr, i);
		max = std::max(dp[i], max);
	}
	delete[]dp; //这里只是保存一下，没用，但是输出最长子序列的时候是有用的
	dp = nullptr;
	return max;
}

//对于给定结尾，最长子序列的长度
int LISProcess(int *arr, int end)
{
	if (end == 0) //长度为0，一定就是1
		return 1;

	int res = 1;
	for (int i = end - 1; i >= 0; --i) //找之前的每一个数
	{
		if (arr[i] < arr[end]) //如果这个数小于当前结尾，那么就有可能添加进来
			res = std::max(res, LISProcess(arr, i) + 1);
		else
			res = std::max(1, res);
	}
	return res;
}



//解法2:动态规划,O(N^2)
int LIS2(int *arr, int n)
{
	if (arr == nullptr || n <= 0)
		return 0;

	int *dp = new int[n];
	int max = std::numeric_limits<int>::min();
	for (int i = 0; i < n; ++i)
	{
		int curMax = 1; //当前数一个数
		for (int j = i - 1; j >= 0; --j) //找它前面的数，看能不能形成IS
			if (arr[i] > arr[j])
				curMax = std::max(curMax, dp[j] + 1);
		dp[i] = curMax;
		max = std::max(dp[i], max);
	}

	delete[]dp;
	dp = nullptr;
	return max;
}

//记住(长度为i的最长递增子序列的最大值)的最小值来求解，仍然是O(N^2)
int LIS3(const std::vector<int>&arr)
{
	//(长度为i的最长递增子序列的最大值)的最小值
	std::vector<int> maxLenMinVal(arr.size() + 1, arr[0]);
	int curMaxLen = 1; //初始的时候，第一个位置，长度为1
	for (size_t i = 1; i < arr.size(); ++i)
	{
		if (arr[i] > maxLenMinVal[curMaxLen])
			maxLenMinVal[++curMaxLen] = arr[i];
		else
		{
			for (size_t j = 1; j <= curMaxLen; ++j)
			{
				if (maxLenMinVal[j] >= arr[i]) //等于的时候一定要终止循环!!!,否则会出现替换后1,3,5,5,...
				{
					maxLenMinVal[j] = arr[i];
					break;
				}
			}
		}
	}
	return curMaxLen;
}

//改成二分搜索，找到插入位置
int LIS4(const std::vector<int>&arr)
{
	//(长度为i的最长递增子序列的最大值)的最小值
	std::vector<int> maxLenMinVal(arr.size() + 1, arr[0]);
	int curMaxLen = 1; //初始的时候，第一个位置，长度为1
	for (size_t i = 1; i < arr.size(); ++i)
	{
		if (arr[i] > maxLenMinVal[curMaxLen])
			maxLenMinVal[++curMaxLen] = arr[i];
		else
		{
			*std::lower_bound(maxLenMinVal.begin() + 1, maxLenMinVal.begin() + curMaxLen + 1, arr[i]) = arr[i];
		}
	}
	return curMaxLen;
}


int main()
{
	int arr[] = { 2,1 ,5 ,3 ,6,4,8 ,9, 7 };
	size_t n = sizeof(arr) / sizeof(arr[0]);
	std::cout << LIS(arr, n) << std::endl;
	std::cout << LIS2(arr, n) << std::endl;
	std::cout << LIS3(std::vector<int>(arr, arr + n)) << std::endl;
	std::cout << LIS4(std::vector<int>(arr, arr + n)) << std::endl;
	yxp_utility::RandomHelper::initSeed();
	int nTestTime = 1000;
	size_t nArrSize = 10;
	int min = 0, max = 100;

	for (int i = 0; i < nTestTime; ++i)
	{
		auto v = yxp_utility::RandomHelper::randomArray(nArrSize, min, max);
		auto res = LIS(&v[0], v.size());
		auto res2 = LIS2(&v[0], v.size());
		auto res3 = LIS3(v);
		auto res4 = LIS4(v);
		assert(res == res2);
		assert(res == res3);
		assert(res == res4);
	}



	return 0;
}