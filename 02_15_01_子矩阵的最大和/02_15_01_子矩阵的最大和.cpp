#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>
#include <YXPCommon.h>

//解法1:枚举所有子矩阵 O(N^2*M^2*M*N)
int max(int x, int y)
{
	return (x > y) ? x : y;  // 用于比较x和y的大小，返回x和y中的较大者
}

// @parameters
// A，二维数组
// n，行数
// m，列数

int Sum(int * A, int rows, int cols, int i_min, int i_max, int j_min, int j_max)
{
	int sum = 0;
	for (int i = i_min; i <= i_max; ++i)
	{
		for (int j = j_min; j <= j_max; ++j)
		{
			sum += A[i*cols + j];
		}
	}
	return sum; //not implemented
}

int MaxSum1(int* A, int rows, int cols)
{
	int maximum = std::numeric_limits<int>::min();
	for (int i_min = 0; i_min < rows; i_min++)
		for (int i_max = i_min; i_max < rows; i_max++)
			for (int j_min = 0; j_min < cols; j_min++)
				for (int j_max = j_min; j_max < cols; j_max++)
					maximum = max(maximum, Sum(A, rows, cols, i_min, i_max, j_min,
						j_max));
	return maximum;
}

//解法2:把计算到的和存起来,还是错的，没改出来（很多边界条件）。。其实这个方法反而很复杂
int MaxSum2(int* A, int rows, int cols)
{
	int max = std::numeric_limits<int>::min();
	//生成边界信息数组,PS[I][J] 表示从0,0到i,j位置子矩阵的和
	std::vector<std::vector<int>> PS(rows, std::vector<int>(cols, 0));
	PS[0][0] = A[0];
	for (int i = 1; i < rows; ++i)
		PS[i][0] = PS[i - 1][0] + A[i*cols];
	for (int j = 1; j < cols; ++j)
		PS[0][j] = PS[0][j - 1] + A[j];
	for (int i = 1; i < rows; ++i)
		for (int j = 1; j < cols; ++j)
			PS[i][j] = PS[i - 1][j] + PS[j - 1][i] - PS[i - 1][j - 1] + A[i*cols + j];

	//根据边界信息，对每个子数组，在O(1)时间内求解
	for (int lu_row = 0; lu_row < rows; ++lu_row)
		for (int lu_col = 0; lu_col < cols; ++lu_col) //左上角
			for (int rb_row = lu_row; rb_row < rows; ++rb_row)
				for (int rb_col = lu_col; rb_col < cols; ++rb_col) //右下角
				{
					int tmp;
					if (rb_col == lu_col && rb_row == lu_row)
						tmp = PS[rb_row][rb_col];
					else if (lu_row == 0) //这里的边界条件还有问题，不想改了
						tmp = PS[rb_row][rb_col] - PS[rb_row][lu_col - 1];
					else if (lu_col == 0)
						tmp = PS[rb_row][rb_col] - PS[lu_row - 1][rb_col];
					else
						tmp = PS[rb_row][rb_col] - PS[lu_row - 1][rb_col]
						- PS[rb_row][lu_col - 1] + PS[lu_row - 1][lu_col - 1];
					max = std::max(tmp, max);
				}

	return max;
}

//解法3:找以每行开始和每行结尾的，然后就可以转化成一维的情况
int MaxSumOfRow(int *arr, int n);
int MaxSum3(int* A, int rows, int cols)
{
	int max = std::numeric_limits<int>::min();
	int *rowSum = new int[cols]();
	for (int i = 0; i < rows; ++i)
	{
		memcpy(rowSum, A + i*cols, sizeof(int)*cols);
		//按照当前这一行，来找最大和
		int tmp = MaxSumOfRow(rowSum, cols);
		max = std::max(tmp, max);
		for (int j = i + 1; j < rows; ++j) //以新的行结束
		{
			for (int k = 0; k < cols; ++k)
				rowSum[k] += A[j*cols + k];
			tmp = MaxSumOfRow(rowSum, cols);
			max = std::max(tmp, max);
		}
	}
	return max;
}

//就是02_14_01连续子数组的最大和
int MaxSumOfRow(int *arr, int n)
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
	size_t rows = 10, cols = 10;
	int min = -10, max = 10;

	for (int i = 0; i < nTestTime; ++i)
	{
		int * mat = new int[rows*cols];
		yxp_utility::RandomHelper::randomMatrix(mat, rows, cols, min, max);
		auto res = MaxSum1(mat, rows, cols);
		auto res2 = MaxSum2(mat, rows, cols);
		auto res3 = MaxSum3(mat, rows, cols);
		//std::cout << res << std::endl;
		assert(res == res3);
		//assert(res == res2); //方法2没写出来
	}



	return 0;
}