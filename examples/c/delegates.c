#include <stdio.h>
#include <stdlib.h>

#define DELEGATE_IMPLEMENTATION
#include "PrintDelegate.h"
#define DELEGATE_IMPLEMENTATION
#include "PrintDelegateVoid.h"

int PrintNumber(int x, int y)
{
	printf("x = %d, y = %d\n", x,y);
	return 1;
}

int PrintMoney(int x, int y)
{
	printf("DINERO! x = %d, y = %d\n", x*2,y*3);
	return 2;
}

void PrintNumberVoid(int x)
{
	printf("Number: %d\n", x);
}

void PrintMoneyVoid(int x)
{
	printf("Money: %d\n", x);
}

int main()
{
	PrintDelegate delegate;
	PrintDelegate_init(&delegate);
	PrintDelegate_add(&delegate, PrintNumber);
	PrintDelegate_add(&delegate, PrintMoney);
	PrintDelegate_add(&delegate, PrintNumber);
	PrintDelegate_add(&delegate, PrintMoney);
	PrintDelegate_remove(&delegate, PrintMoney);
	int x = PrintDelegate_invoke(&delegate,10,20);
	PrintDelegate_free(&delegate);
	printf("x = %d\n", x);
	
	
	PrintDelegateVoid delegate2;
	PrintDelegateVoid_init(&delegate2);
	PrintDelegateVoid_add(&delegate2, PrintNumberVoid);
	PrintDelegateVoid_add(&delegate2, PrintMoneyVoid);
	PrintDelegateVoid_invoke(&delegate2, 69);
	PrintDelegateVoid_free(&delegate2);
	
	return 0;
}