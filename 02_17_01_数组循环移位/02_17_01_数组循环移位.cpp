#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>

//解法1:直接进行移位
void CycleShift1(int *arr, int n, int K) //移动K位
{
	for (int i = 0; i < K; ++i) //循环K次
	{
		int last = arr[n - 1];
		for (int j = n - 1; j > 0; --j)
		{
			arr[j] = arr[j - 1];
		}
		arr[0] = last;
	}
}


//解法2:当K大于N的时候
void CycleShift2(int *arr, int n, int K) //移动K位
{
	K %= n;
	for (int i = 0; i < K; ++i) //循环K次
	{
		int last = arr[n - 1];
		for (int j = n - 1; j > 0; --j)
		{
			arr[j] = arr[j - 1];
		}
		arr[0] = last;
	}
}

//解法3:先各自逆序，再全部逆序
void Reverse(int *arr, int i, int j);
void CycleShift3(int *arr, int n, int K) //移动K位
{
	K %= n;
	Reverse(arr, 0, n - K - 1);
	Reverse(arr, n - K, n - 1);
	Reverse(arr, 0, n - 1);

}

void Reverse(int *arr, int i, int j)
{
	while (i < j)
	{
		std::swap(arr[i++], arr[j--]);
	}
}




int main()
{
	int arr[] = { 1,2,3,4,5,6 };
	int n = sizeof(arr) / sizeof(arr[0]);
	CycleShift1(arr, n, 2);

	std::for_each(arr, arr + n, [](int val) { std::cout << val << " "; });
	std::cout << std::endl;

	CycleShift2(arr, n, 7);
	std::for_each(arr, arr + n, [](int val) { std::cout << val << " "; });
	std::cout << std::endl;

	CycleShift3(arr, n, 7);
	std::for_each(arr, arr + n, [](int val) { std::cout << val << " "; });
	std::cout << std::endl;

	CycleShift3(arr, n, 8);
	std::for_each(arr, arr + n, [](int val) { std::cout << val << " "; });
	std::cout << std::endl;

	return 0;
}