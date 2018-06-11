#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>

//My Own
int first1posOfFactorial(int n) //实质上就是2的因子的个数，因为二进制1出现，说明就是2的倍数 
{
	int res = 0;
	while (n)
	{
		//res += n / 2;
		//n /= 2;

		n >>= 1;
		res += n;
	}
	return res + 1; //比如3，最右边二进制1在倒数第二位，res=1
}

int main()
{
	assert(first1posOfFactorial(30) == 27);

	return 0;
}