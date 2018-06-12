#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>
#include <YXPCommon.h>

//解法1:暴力遍历O(N^3)
int MaxSum1(int *arr, int n)
{
	if (arr == nullptr || n <= 0)
		return 0;

	int max = std::numeric_limits<int>::min();

	for (int i = 0; i < n; ++i) //以每一个位置开始
	{
		for (int j = i; j < n; ++j) //以每一个位置结束
		{
			int curSum = 0;
			for (int k = i; k <= j; ++k) //当前开始和结束的子数组之和
				curSum += arr[k];
			max = std::max(curSum, max);
		}
	}
	return max;
}

//解法2:优化一下O(N^2)
int MaxSum2(int *arr, int n)
{
	if (arr == nullptr || n <= 0)
		return 0;

	int max = std::numeric_limits<int>::min();

	for (int i = 0; i < n; ++i) //以每一个位置开始
	{
		int curSum = 0;
		for (int j = i; j < n; ++j) //以每一个位置结束
		{
			curSum += arr[j]; //其实固定了开始，结尾变的子数组，后一个比前一个就之多下一个数的大小
			max = std::max(curSum, max);
		}
	}
	return max;
}

//解法3:分治思想 O(NlogN)
//情况3，跨越两个子部分的时候(A[0]开始和A(n/2)开始的最大子数组之和)怎么求(用方法7的遍历一次能够求到，但是意义不大了这样)

//解法4:动态规划 递归版本
void MaxSumProcess4(int *arr, int i, int j, int *allMax, int *startMax);
int MaxSum4(int *arr, int n)
{
	int *allMax = new int[n]; //当前位置到n-1位置范围上的的最大子数组和
	int *startMax = new int[n]; //必须以当前位置开始的到n-1范围的最大子数组和
	MaxSumProcess4(arr, 0, n - 1, allMax, startMax);
	int res = allMax[0];
	delete[]allMax;
	delete[]startMax;
	return res;
}
//对i->j位置，求allMax和startMax
void MaxSumProcess4(int *arr, int i, int j, int *allMax, int *startMax) //由于需要维持两个dp数组，采用参数返回值的做法
{
	if (i == j)
	{
		startMax[i] = arr[i];
		allMax[i] = arr[i];
		return;
	}

	MaxSumProcess4(arr, i + 1, j, allMax, startMax);
	startMax[i] = std::max(startMax[i + 1] + arr[i], arr[i]);
	allMax[i] = std::max(startMax[i + 1] + arr[i], allMax[i + 1]);
}

//迭代版本
int MaxSum5(int *arr, int n)
{
	int *allMax = new int[n]; //当前位置到n-1位置范围上的的最大子数组和
	int *startMax = new int[n]; //必须以当前位置开始的到n-1范围的最大子数组和
	allMax[n - 1] = arr[n - 1];
	startMax[n - 1] = arr[n - 1];
	for (int i = n - 2; i >= 0; --i)
	{
		startMax[i] = std::max(startMax[i + 1] + arr[i], arr[i]);
		//allMax[i] = std::max(startMax[i + 1] + arr[i], allMax[i + 1]);
		allMax[i] = std::max(startMax[i], allMax[i + 1]); //这样也就行了
	}
	int res = allMax[0];
	delete[]allMax;
	delete[]startMax;
	return res;
}

//迭代版本,空间优化
int MaxSum6(int *arr, int n)
{
	int nStartMax = arr[n - 1];
	int nAllMax = arr[n - 1];
	for (int i = n - 2; i >= 0; --i)
	{
		nStartMax = std::max(nStartMax + arr[i], arr[i]);
		nAllMax = std::max(nStartMax, nAllMax); //这里第一个参数是nStartMax！！！
	}
	return nAllMax;
}

//最终，就是我们平时看到的版本了
int MaxSum7(int *arr, int n)
{
	int curMax = 0;
	int max = std::numeric_limits<int>::min();
	for (int i = 0; i < n; ++i)
	{
		curMax += arr[i];
		max = std::max(max, curMax);
		curMax = curMax < 0 ? 0 : curMax;
	}
	return max;
}


int main()
{
	yxp_utility::RandomHelper::initSeed();
	int nTestTime = 1000;
	size_t nArrSize = 100;
	int min = -100, max = 100;

	for (int i = 0; i < nTestTime; ++i)
	{
		auto v = yxp_utility::RandomHelper::randomArray(nArrSize, min, max);
		auto res = MaxSum1(&v[0], v.size());
		auto res2 = MaxSum2(&v[0], v.size());
		auto res4 = MaxSum4(&v[0], v.size());
		auto res5 = MaxSum5(&v[0], v.size());
		auto res6 = MaxSum6(&v[0], v.size());
		auto res7 = MaxSum7(&v[0], v.size());
		assert(res == res2);
		assert(res4 == res2);
		assert(res5 == res2);
		assert(res6 == res2);
		assert(res7 == res2);
	}

	return 0;
}