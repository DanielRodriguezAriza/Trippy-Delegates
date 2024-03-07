#include <iostream>

template<typename Signature>
class Test;

template<typename Ret, typename ...Args>
class Test<Ret(Args...)>
{
public:
	Test(Ret(Args...))
	{}
};

void thing(int i)
{}

int main()
{
	Test<void(int)> t {thing};
	return 0;
}