#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>
#include <random>

unsigned int gcd1(unsigned int x, unsigned int y)
{
	return (y == 0) ? x : gcd1(y, x%y);
}


//但是这个做法有问题，当出现y==1,x较大(比如随机数的%10000)的时候，会一直每次减一递归，造成堆栈溢出
unsigned int gcd2(unsigned int x, unsigned int y)
{
	if (x < y)
		return gcd2(y, x);
	if (y == 0)
		return x;
	else
		return gcd2(x - y, y);
}


int main()
{
	std::srand(0);
	std::default_random_engine e;
	for (int i = 0; i < 10000; ++i)
	{
		unsigned int num1 = e()%1000, num2 = e()% 1000;
		assert(gcd1(num1, num2) == gcd2(num1, num2));
		//gcd1(num1, num2);
		//gcd2(num1, num2);
	}




	return 0;
}