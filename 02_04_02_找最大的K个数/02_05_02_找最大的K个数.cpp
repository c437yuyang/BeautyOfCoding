#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>
#include <YXPUtility>

typedef int number;

//解法1:排序，然后拿


//解法2:partition,然后按照一个数来分，如果这个数分完后，刚好就是k位置，那么就找到了,平均:O(NlogK)

//解法3:维持一个K个数的最小堆 , O(N*logK)

bool SmallHeap(int v1, int v2)
{
	return v1 > v2;
}

void PushHeap(std::vector<number> &heap, number val)
{
	heap.push_back(val);
	std::push_heap(heap.begin(), heap.end(), SmallHeap);
}

number PopHeap(std::vector<number> &heap)
{
	std::pop_heap(heap.begin(), heap.end(),SmallHeap);
	number back_save = heap.back();
	heap.pop_back();
	return back_save;
}

std::vector<number> FindKTthLargest(const std::vector<number> &v, number K)
{

	if (v.size() < K)
		throw std::exception("invalid input");
	if (v.size() == K)
		return v;

	std::vector<number> heap;
	std::make_heap(heap.begin(), heap.end(), SmallHeap);

	for (size_t i = 0; i < v.size(); ++i)
	{
		if (heap.size() < K)
		{
			PushHeap(heap, v[i]);
		}
		else
		{
			if (v[i] > heap[0])
			{
				PopHeap(heap);
				PushHeap(heap, v[i]);
			}
		}
	}
	return heap;
}


//解法4:如果数据范围比较小的话，可以求出直方图，然后做统计O(N)

//解法5:BFPRT

int main()
{
	yxp_utility::RandomHelper::initSeed();
	size_t n = 100;
	number K = 5;
	int min = 10, max = 100;

	auto v = yxp_utility::RandomHelper::randomArray(n, min, max);
	yxp_utility::ArrayHelper::printArr(v);
	auto largestK = FindKTthLargest(v, K);
	yxp_utility::ArrayHelper::printArr(largestK);
	std::sort(largestK.begin(), largestK.end(), SmallHeap);
	yxp_utility::ArrayHelper::printArr(largestK);

	auto v_save = v;
	std::sort(v_save.begin(), v_save.end(),SmallHeap);
	yxp_utility::ArrayHelper::printArr(&v_save[0],K);

	return 0;
}