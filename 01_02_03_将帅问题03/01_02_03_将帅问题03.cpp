#include <cstdio>
struct
{
	unsigned char a : 4;
	unsigned char b : 4;
} i;

int main()
{
	for (i.a = 1; i.a <= 9; i.a++)
		for (i.b = 1; i.b <= 9; i.b++)
			if (i.a % 3 != i.b % 3)
				printf("A = %d, B = %d\n", i.a, i.b);
	return 0;
}
