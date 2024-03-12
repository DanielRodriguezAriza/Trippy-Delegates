#include <stdio.h>
#include <stdlib.h>

#define DELEGATE_IMPLEMENTATION
#include "SinglePrintDelegate.h"

void PrintNumber(int num)
{
	printf("The number is : %d\n", num);
}

void PrintMoney(int money)
{
	printf("The money is : %d\n", money);
}

int main()
{
	SinglecastDelegatePrint delegate;
	
	SinglecastDelegatePrint_set(&delegate, PrintNumber);
	SinglecastDelegatePrint_invoke(&delegate, 1);
	
	SinglecastDelegatePrint_set(&delegate, PrintMoney);
	SinglecastDelegatePrint_invoke(&delegate, 2);
	
	return 0;
}
