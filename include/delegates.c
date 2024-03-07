#include <stdio.h>

//this is like C#'s public delgate void Print(int value);
#define MAKE_DELEGATE(ret, args, name) typedef ret (*name) args

#define MAKE_DELEGATE_LIST(type) type *lst;

void delegate_add_function(delegate *d, void *fn)
void delegate_remove_function(delegate *d, void *fn)
size_t delegate_get_length(delegate *d)
#define delegate_invoke(delegate, args) (for(size_t i = 0; i < delegate_get_length(delegate) - 1; ++i) delegate[i] args , delegate[delegate_get_length(delegate) - 1] args)

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