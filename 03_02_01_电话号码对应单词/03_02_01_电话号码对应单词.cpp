#include <iostream>
#include <string>
void printProcess(const std::string& numbers, int index, std::string wait2Print);
char c[10][10] =
{
	"",    	//0
	"",          	//1
	"ABC",	//2
	"DEF",	//3
	"GHI",	//4
	"JKL",	//5
	"MNO",	//6
	"PQRS",  	//7
	"TUV",	//8
	"WXYZ",	//9
};

int total[] = { 0,0,3,3,3,3,3,4,3,4 };

void printAllWordsUseNumbers(const std::string& numbers)
{
	printProcess(numbers, 0, "");
}

void printProcess(const std::string& numbers, int index, std::string wait2Print)
{
	if (index == numbers.length())
	{
		std::cout << wait2Print << std::endl;
		return;
	}


	int number = numbers[index] - '0';
	while (total[number] <= 0)
	{
		++index;
		number = numbers[index] - '0';
	}

	for (int i = 0; i < total[number]; ++i)
	{
		std::string tmp = wait2Print + c[number][i];
		printProcess(numbers, index + 1, tmp);
	}

}


int main()
{
	printAllWordsUseNumbers("12345");
	return 0;
}
