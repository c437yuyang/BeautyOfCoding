#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>

//My Own
int numof0InFactorial(int n) //错了，只算了最终这个数里面5的因子，应该要算1-n的数的
{
	int res = 0;
	while ((++res) * 5 <= n) {}

	return --res;
}

int numof0InFactorial1(int n)
{
	int ret = 0;
	for (int i = 1; i <= n; i++) //遍历1-n的每一个数
	{
		int j = i;
		while (j % 5 == 0)//计算这一个数的5的因子的数量
		{
			ret++;
			j /= 5;
		}
	}
	return ret;
}

int numof0InFactorial2(int n)
{
	int ret = 0;
	while (n)
	{
		ret += n / 5; //每次当前n/5就是当前能够供给的5的因子的数目，比如n一开始等于30,第一轮就是5,10,15,20,25,30,提供6个5,然后这些数全部除以5，就是1...6，只有5还能提供5
		n /= 5;
	}
}

int main()
{
	assert(numof0InFactorial1(4) == 0);
	assert(numof0InFactorial1(5) == 1);
	assert(numof0InFactorial1(10) == 2);
	assert(numof0InFactorial1(20) == 4);
	assert(numof0InFactorial1(30) == 7);

	return 0;
}