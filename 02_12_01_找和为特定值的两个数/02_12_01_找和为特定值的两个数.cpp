#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>
#include <>

//解法1:暴力遍历 O(N^2)


//解法2:先排序，然后对于每一个数arr[i]，进行二分查找sum-arr[i]在数组中吗
std::vector<int> GetTwoNumOfSum2(std::vector<int> & arr, int aim)
{
	std::sort(arr.begin(), arr.end());

	for (size_t i = 0; i < arr.size(); ++i)
	{
		if (std::binary_search(arr.begin(), arr.end(), aim - arr[i])) //当然，这里没有考虑aim=16,数组里面有两个8的情况
			return{ arr[i],aim - arr[i] };
	}
	return{ -1,-1 };
}

//解法3:哈希表来存

//解法4:先排序，然后双指针法
std::vector<int> GetTwoNumOfSum4(std::vector<int> & arr, int aim)
{
	std::sort(arr.begin(), arr.end());
	int left = 0, right = arr.size() - 1;
	while (left < right)
	{
		if (arr[left] + arr[right] == aim)
			return{ arr[left],arr[right] };
		else if (arr[left] + arr[right] < aim)
			++left;
		else
			--right;
	}
	return{ -1,-1 };
}






int main()
{


	return 0;
}