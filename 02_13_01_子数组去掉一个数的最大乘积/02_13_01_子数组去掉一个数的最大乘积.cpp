#include  <YXPCommon.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>
#include <numeric>

//暴力解法:
long long GetMaxProduct(const std::vector<int> &arr)
{
	long long res = std::numeric_limits<int>::min();
	for (size_t i = 0; i < arr.size(); ++i)
	{
		long long tmp = 1;
		auto arr_cp = arr;
		for (size_t j = 0; j < arr.size(); ++j)
		{
			if (j != i)
				tmp *= arr[j];
		}
		res = std::max(tmp, res);
	}
	return res;
}

//解法1:没看懂，按理说他这个解法还是O(N^2)

//解法2:通过正负性判断


long long CalcProduct(const std::vector<int> &arr)
{
	long long res = 1;
	std::for_each(arr.begin(), arr.end(), [&res](int val) { if (val) res *= val; });
	return res;
}


long long GetMaxProduct2(std::vector<int> &arr)
{
	int neg_num = 0, zero_num = 0, pos_num = 0;
	for (size_t i = 0; i < arr.size(); ++i)
	{
		if (arr[i] == 0)
			++zero_num;
		else if (arr[i] > 0)
			++pos_num;
		else 
			++neg_num;
	}

	if (zero_num >= 2) //两个0不管怎么去除都是0
		return 0;
	else if (zero_num == 1)
	{
		if ((neg_num & 1) == 0) //偶数个负数
		{
			//那么就是去掉这个0的直接相乘得到最大值
			arr.erase(std::find(arr.begin(), arr.end(), 0));
		}
		else //奇数个负数，那么就只能去掉这个负数
		{
			return 0; //去掉负数就还有一个0
		}
	}
	else //没有0
	{
		if ((neg_num & 1) == 0) //偶数个负数，没有0
		{
			if (pos_num > 0) //首先保证结果是正的，因此去掉绝对值最小的正数
			{
				int min_pos = std::numeric_limits<int>::max();
				for (size_t i = 0; i < arr.size(); ++i)
				{
					if (arr[i] > 0)
						min_pos = std::min(min_pos, arr[i]);
				}
				arr.erase(std::find(arr.begin(), arr.end(), min_pos));
			}
			else //没有正数，那么只能去掉绝对值最大的负数了
			{
				int max_neg = std::numeric_limits<int>::max();
				for (size_t i = 0; i < arr.size(); ++i)
				{
					if (arr[i] < 0) //就是找最小的负数
						max_neg = std::min(max_neg, arr[i]);
				}
				arr.erase(std::find(arr.begin(), arr.end(), max_neg));
			}
		}
		else //奇数个负数，那么就去掉绝对值最小的负数
		{
			int min_neg = std::numeric_limits<int>::min();
			for (size_t i = 0; i < arr.size(); ++i)
			{
				if (arr[i] < 0) //就是找最大的负数
					min_neg = std::max(min_neg, arr[i]);
			}
			arr.erase(std::find(arr.begin(), arr.end(), min_neg));
		}
	}
	return CalcProduct(arr);
}



int main()
{

	yxp_utility::RandomHelper::initSeed();
	int nTestTime = 1000;
	size_t nArrSize = 10;
	int min = -10, max = 10;

	for (int i = 0; i < nTestTime; ++i)
	{
		auto v = yxp_utility::RandomHelper::randomArray(nArrSize, min, max);
		auto res = GetMaxProduct(v);
		auto res2 = GetMaxProduct2(v);
		assert(res == res2);
	}

	return 0;
}