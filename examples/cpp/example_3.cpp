#include <iostream>
#include <vector>

#include "../../include/delegate.hpp"

typedef Delegate<void(int)> Print;

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
	Print d1, d2;
	
	d1 += PrintNumber;
	d1 += PrintMoney;
	d1 += PrintThing;
	
	d2 = d1;
	
	d2 -= PrintNumber;
	
	d1.Invoke(1);
	d2.Invoke(2);
	
	return 0;
}
