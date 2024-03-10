#include <iostream>
#include <vector>

#include "../../include/delegate.hpp"

typedef SinglecastDelegate<void(int)> Print;

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


int main()
{
	Print delegate;
	delegate.Set(PrintNumber);
	delegate.Invoke(69);
	
	return 0;
}
