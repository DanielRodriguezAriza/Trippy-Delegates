#include <iostream>
/*
template<typename T, typename ...Args>
T fn(Args ...args)
{
	std::cout<<"Using T\n";
	return T {};
}

template<typename ...Args>
void fn<void, Args...>(Args ...args)
{
	std::cout<<"Using void\n";
}
*/

template<typename T, typename ...Args>
class Thing
{
public:
	void fn()
	{
		std::cout<<"Using T\n";
	}
};

template<typename ...Args>
class Thing<void, Args...>
{
public:
	void fn()
	{
		std::cout<<"Using void\n";
	}
};

template<typename T, typename ...Args>
class Other
{
public:
	void fn()
	{
		Thing<T, Args...> t;
		t.fn();
	}
};

int main()
{
	//fn<void,int>(10);
	Other<void,int,int> t;
	t.fn();
	return 0;
}