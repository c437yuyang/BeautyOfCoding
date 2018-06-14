#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>



int CalculateStringDistance(std::string strA, int pABegin, int pAEnd, std::string strB, int pBBegin, int pBEnd)
{
	if (pABegin > pAEnd)
	{
		if (pBBegin > pBEnd)
			return 0;
		else
			return pBEnd - pBBegin + 1;
	}

	if (pBBegin > pBEnd)
	{
		if (pABegin > pAEnd)
			return 0;
		else
			return pAEnd - pABegin + 1;
	}

	if (strA[pABegin] == strB[pBBegin])
	{
		return CalculateStringDistance(strA, pABegin + 1, pAEnd,
			strB, pBBegin + 1, pBEnd);
	}
	else
	{
		int t1 = CalculateStringDistance(strA, pABegin, pAEnd, strB,
			pBBegin + 1, pBEnd); 
		int t2 = CalculateStringDistance(strA, pABegin + 1, pAEnd,
			strB, pBBegin, pBEnd);
		int t3 = CalculateStringDistance(strA, pABegin + 1, pAEnd,
			strB, pBBegin + 1, pBEnd);
		return std::min({ t1, t2, t3 }) + 1;
	}
}


int main()
{
	std::string strA = "abcdef";
	std::string strB = "abcdefg";
	std::string strC = "bcdefg";
	std::cout << CalculateStringDistance(strA, 0, strA.length() - 1,
		strB, 0, strB.length() - 1) << std::endl;

	std::cout << CalculateStringDistance(strA, 0, strA.length() - 1,
		strC, 0, strC.length() - 1) << std::endl;

	return 0;
}