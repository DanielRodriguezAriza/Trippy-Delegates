#include <iostream>
#include <vector>

template<typename Ret, typename ...Args>
class Delegate
{
public:
	
	Delegate()
	{}
	
	Delegate(Ret (*fn) (Args...))
	{
		functions.clear();
		functions.push_back(fn);
	}
	
	Delegate &operator=(Ret (*fn) (Args...))
	{
		functions.clear();
		functions.push_back(fn);
		return *this;
	}
	
	void operator()(Args ... args)
	{
		for(auto fn : functions)
		{
			fn(args ...);
		}
	}
	
	Delegate &operator+=(Ret (*fn) (Args...))
	{
		functions.push_back(fn);
		return *this;
	}
	
	Delegate &operator-=(Ret (*fn) (Args...))
	{
		for(int i = 0; i < functions.size(); ++i)
		{
			if(functions[i] == fn)
			{
				functions[i] = functions[functions.size()-1];
				functions.pop_back();
			}
		}
		return *this;
	}
	
private:
	
	std::vector<Ret (*) (Args...)> functions;
	
};


typedef Delegate<void, int> Print;

void PrintNumber(int num)
{
	printf("Number: %d\n", num);
}

void PrintMoney(int money)
{
	printf("Money: %d\n", money);
}



typedef Delegate<void, int, int> Print2;

void PrintNumber2(int a, int b)
{
	printf("Numbers: %d, %d\n", a, b);
}

void PrintMoney2(int a, int b)
{
	printf("Money Money Money~ : %d, %d\n", a, b);
}


int main()
{
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
	
	Print2 printDelegate2 = PrintNumber2;
	printDelegate2(10, 20);
	
	printDelegate2 += PrintMoney2;
	printDelegate2(30,40);
	
	printDelegate2 -= PrintMoney2;
	printDelegate2(69, 420);
	
	printDelegate2 -= PrintNumber2;
	printDelegate2(10,10);
	
	printf("\n\nMe he fumado 4 porros\n");
	
	return 0;
}
