#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>
double g_discount[] = { 0.05,0.1,0.2,0.25 };

void sub_vector(std::vector<int>&arr, int endIdx)
{
	for (size_t i = 0; i < arr.size() && i <= endIdx; ++i)
	{
		arr[i] -= 1;
	}
}



double calc(std::vector<int> arr) //用传值来做
{
	std::sort(arr.begin(), arr.end(), std::greater<int>()); //确保从小到大
	if (arr[0] == 0)
		return 0;
	double min = std::numeric_limits<double>::max();
	if (arr[4] >= 1)
	{
		std::vector<int> v = arr;
		sub_vector(v, 4);
		std::sort(v.begin(), v.end(),std::greater<int>()); //减了过后可能出现不一致的,比如22211,从第二个开始减  之后是11211，就需要调整成21111
		min = std::min(min, 5 * 8 * (1 - g_discount[3]) + calc(v));
	}
	if (arr[3] >= 1)
	{
		std::vector<int> v = arr;
		sub_vector(v, 3);
		std::sort(v.begin(), v.end(), std::greater<int>());
		min = std::min(min, 4 * 8 * (1 - g_discount[2]) + calc(v));
	}
	if (arr[2] >= 1)
	{
		std::vector<int> v = arr;
		sub_vector(v, 2);
		std::sort(v.begin(), v.end(), std::greater<int>());
		min = std::min(min, 3 * 8 * (1 - g_discount[1]) + calc(v));
	}
	if (arr[1] >= 1)
	{
		std::vector<int> v = arr;
		sub_vector(v, 1);
		std::sort(v.begin(), v.end(), std::greater<int>());
		min = std::min(min, 2 * 8 * (1 - g_discount[0]) + calc(v));
	}
	if (arr[0] >= 1)
	{
		std::vector<int> v = arr;
		sub_vector(v, 0);
		std::sort(v.begin(), v.end(), std::greater<int>());
		min = std::min(min, 1 * 8 + calc(v));
	}
	return min;
}




int main()
{
	std::vector<int> arr = { 2,2,2,1,1 };
	std::cout << calc(arr) << std::endl;

	return 0;
}