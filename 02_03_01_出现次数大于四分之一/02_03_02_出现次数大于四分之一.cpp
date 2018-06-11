//补充题:

//////////////////////////////////////////////////////////////////////////
//找到数组中出现频率大于1/4的数。当然这样的数最多只有3个
//思想：每次删去4个不同的数，最后剩余的数即为候选的答案，最后还要将候选的数字带入进数
//////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

#define ARRAY_SIZE 15
#define RESULT_NUM 3 //数组中出现频率的大于1/(RESULT_NUM+1)
int gl_array[ARRAY_SIZE] = { 1,2,1,4,1,4,2,9,1,7,4,3,9,4,3 };//给定的数字集合

struct Result
{
	int iNumber;
	int iTempTimes;
};

int GetEmptyElemInResult(Result r[], int iArrayLength)
{
	int i = 0;
	for (i = 0; i < iArrayLength; i++)
	{
		if (r[i].iTempTimes <= 0)
		{
			return i;
		}
	}
	return -1;
}

int GetNumberPosInResult(int iNumber, Result r[], int iArrayLength)
{
	int i = 0;
	for (i = 0; i < iArrayLength; i++)
	{
		if (r[i].iNumber == iNumber && r[i].iTempTimes > 0)
		{//iNumber出现在候选中，并且有效（在给定的数字集合中，出现次数大于0）
			return i;
		}
	}
	return -1;
}

int main(int argc, char** argv)
{
	Result resultArray[RESULT_NUM];//结果候选集合
	int i, j, iTemp;
	for (i = 0; i < RESULT_NUM; i++)
	{
		resultArray[i].iNumber = 0;
		resultArray[i].iTempTimes = 0;
	}
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		iTemp = GetNumberPosInResult(gl_array[i], resultArray, RESULT_NUM);
		if (-1 != iTemp)
		{//若当前数出现在候选集合中，且有效，则其出现次数+1
			++resultArray[iTemp].iTempTimes;
		}
		else//不在候选中
		{
			iTemp = GetEmptyElemInResult(resultArray, RESULT_NUM);
			if (-1 != iTemp)
			{//结果候选不满RESULT_NUM个元素，将当前数插入在候选集合中
				resultArray[iTemp].iNumber = gl_array[i];
				resultArray[iTemp].iTempTimes = 1;
			}
			else
			{//没有空位了，并且当前数与候选集合中的所有元素都不相同，执行“删除”操作
				for (j = 0; j < RESULT_NUM; j++)
				{
					--resultArray[j].iTempTimes;
				}
			}
		}
	}

	//test the result in the array
	for (i = 0; i < RESULT_NUM; i++)
	{
		if (resultArray[i].iTempTimes > 0)
		{
			iTemp = 0;
			for (j = 0; j < ARRAY_SIZE; j++)
			{
				if (resultArray[i].iNumber == gl_array[j])
				{
					++iTemp;
				}
			}
			if (iTemp > ARRAY_SIZE / (RESULT_NUM + 1))//出现次数大于阈值
			{
				cout << resultArray[i].iNumber << ": " << iTemp << endl;
			}
		}
	}
	return 0;
}