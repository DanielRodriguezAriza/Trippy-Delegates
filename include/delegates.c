#include <stdio.h>

//this is like C#'s public delgate void Print(int value);
#define MAKE_DELEGATE(ret, args, name) typedef ret (*name) args

//typedef void (*Print)(int);
MAKE_DELEGATE(void, (int), Print);

void PrintNumber(int num)
{
	printf("Number: %d\n", num);
}

void PrintMoney(int money)
{
	printf("Money: %d\n", money);
}

int main()
{
	Print printDelegate = PrintNumber;
	printDelegate(1000);
	
	printDelegate = PrintMoney;
	printDelegate(1000);
	
	return 0;
}