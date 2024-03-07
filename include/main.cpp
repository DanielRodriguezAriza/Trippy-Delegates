#include <iostream>
#include <vector>

#include "delegate.h"

typedef Delegate<void, int> Print;

void PrintNumber(int num)
{
	printf("Number: %d\n", num);
}

void PrintMoney(int money)
{
	printf("Money: %d\n", money);
}

void PrintThing(int t)
{
	printf("Thing! %d\n", t);
}



typedef Delegate<int, int, int> Print2;

int PrintNumber2(int a, int b)
{
	printf("Numbers: %d, %d\n", a, b);
	return 1;
}

int PrintMoney2(int a, int b)
{
	printf("Money Money Money~ : %d, %d\n", a, b);
	return 2;
}


int main()
{
	printf("\n\nPrint: (checking order keeping):\n");
	Print p = PrintNumber;
	p += PrintMoney;
	p += PrintThing;
	p += PrintNumber;
	p -= PrintNumber;
	p(1);
	
	printf("\n\nPrint:\n");
	Print printDelegate = PrintNumber;
	printDelegate(1);
	
	printDelegate += PrintMoney;
	printDelegate(2);
	
	printDelegate -= PrintMoney;
	printDelegate(3);
	
	printDelegate -= PrintNumber;
	printDelegate(4);
	
	
	printf("\n\nPrint2:\n");
	
	int x = 0;
	
	Print2 printDelegate2 = PrintNumber2;
	x = printDelegate2(10, 20);
	printf("x = %d\n", x);
	
	printDelegate2 += PrintMoney2;
	x = printDelegate2(30,40);
	printf("x = %d\n", x);
	
	printDelegate2 -= PrintMoney2;
	printDelegate2(69, 420);
	
	printDelegate2 -= PrintNumber2;
	printDelegate2(10,10);
	
	printf("\n\nMe he fumado 4 porros\n");
	
	return 0;
}
