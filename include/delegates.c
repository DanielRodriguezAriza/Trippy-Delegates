#include <stdio.h>
#include <stdlib.h>

#define DELEGATE_IMPLEMENTATION
#include "PrintDelegate.h"

int PrintNumber(int x, int y)
{
	printf("x = %d, y = %d\n", x,y);
}

int PrintMoney(int x, int y)
{
	printf("DINERO! x = %d, y = %d\n", x*2,y*3);
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
	PrintDelegate_invoke(&delegate,10,20);
	//PrintDelegate_invoke(&delegate,30,40);
	PrintDelegate_free(&delegate);
	return 0;
}