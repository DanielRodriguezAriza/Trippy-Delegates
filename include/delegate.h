#ifndef DRA_DELEGATE_H
#define DRA_DELEGATE_H

#ifdef __cplusplus
extern "C" {
#endif

//C delegate code goes here lol

#ifdef __cplusplus
}
#endif

//C++ delegate code goes here lmao

#include <vector>


template<typename T, typename ...Args>
class DelegateExecutor
{
public:
	T invokeFunctions(std::vector<T (*) (Args...)> &functions, Args ...args)
	{
		T ans;
		for(auto fn : functions)
			ans = fn(args...);
		return ans;
	}
};

template<typename ...Args>
class DelegateExecutor<void, Args...>
{
public:
	void invokeFunctions(std::vector<void (*) (Args...)> &functions, Args ...args)
	{
		for(auto fn : functions)
			fn(args...);
	}
};


template<typename Ret, typename ...Args>
class Delegate
{
public:
	
	Delegate()
	:functions{}
	{}
	
	Delegate(Ret (*fn) (Args...))
	{
		functions.clear();
		functions.push_back(fn);
	}
	
	~Delegate()
	{}
	
	Delegate &operator=(Ret (*fn) (Args...))
	{
		functions.clear();
		functions.push_back(fn);
		return *this;
	}
	
	Ret operator()(Args ... args)
	{
		DelegateExecutor<Ret, Args...> ex;
		return ex.invokeFunctions(functions, args...);
	}
	
	Delegate &operator+=(Ret (*fn) (Args...))
	{
		functions.push_back(fn);
		return *this;
	}
	
	Delegate &operator-=(Ret (*fn) (Args...))
	{
		/*
		for(int i = 0; i < functions.size(); ++i)
		{
			if(functions[i] == fn)
			{
				functions[i] = functions[functions.size()-1];
				functions.pop_back();
			}
		}
		*/
		RemoveFunction(fn);
		return *this;
	}

private:
	/*
	void AddFunction(Ret (*fn) (Args...))
	{
		this.functions.push_back(fn);
	}
	*/
	
	void RemoveFunction(Ret (*fn) (Args...))
	{
		size_t i;
		for(i = 0; i < functions.size(); ++i)
		{
			if(functions[i] == fn)
			{
				while(i < functions.size() - 1)
				{
					functions[i] = functions[i+1];
					++i;
				}
				functions.pop_back();
				break;
			}
		}
	}
private:
	
	std::vector<Ret (*) (Args...)> functions;
	
};


#endif
