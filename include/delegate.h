#ifndef DRA_DELEGATE_H
#define DRA_DELEGATE_H

/* C Delegates */
#ifdef __cplusplus
extern "C" {
#endif

// Code goes here lol

#ifdef __cplusplus
}
#endif

/* C++ Delegates */
#ifdef __cplusplus

#include <vector>

//#define DRA_INTERNAL_EXTRACT_ARGS(...) __VA_ARGS__
//#define DRA_MAKE_DELEGATE(ret, args, name) typedef Delegate<ret, DRA_INTERNAL_EXTRACT_ARGS args > name

template<typename Ret, typename ...Args>
class InvokeList
{
public:
	
	InvokeList()
	:functions{}
	{}
	
	~InvokeList()
	{}
	
	inline std::vector<Ret (*) (Args ...)> &GetList()
	{
		return this->functions;
	}
	
	inline void AddFunction(Ret (*fn) (Args...))
	{
		functions.push_back(fn);
	}
	
	inline void RemoveFunction(Ret (*fn) (Args...))
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
	
	inline void RemoveFunctions()
	{
		functions.clear();
	}
	
private:
	
	std::vector<Ret (*) (Args...)> functions;
	
};

template<typename T, typename ...Args>
class DelegateExecutor
{
public:
	T invokeFunctions(InvokeList<T, Args...> &functions, Args ...args)
	{
		T ans;
		auto &list = functions.GetList();
		for(auto fn : list)
			ans = fn(args...);
		return ans;
	}
};

template<typename ...Args>
class DelegateExecutor<void, Args...>
{
public:
	void invokeFunctions(InvokeList<void, Args...> &functions, Args ...args)
	{
		auto &list = functions.GetList();
		for(auto fn : list)
			fn(args...);
	}
};


template<typename Signature>
class Delegate;

template<typename Ret, typename ...Args>
class Delegate<Ret(Args...)>
{
public:
	
	Delegate()
	:functions{}
	{}
	
	Delegate(Ret fn (Args...))
	:functions{}
	{
		functions.RemoveFunctions();
		functions.AddFunction(fn);
	}
	
	~Delegate()
	{}
	
	Delegate &operator=(Ret fn (Args...))
	{
		functions.RemoveFunctions();
		functions.AddFunction(fn);
		return *this;
	}
	
	Ret Invoke(Args ...args)
	{
		DelegateExecutor<Ret, Args...> ex;
		return ex.invokeFunctions(functions, args...);
	}
	
	Ret operator()(Args ... args)
	{
		return this->Invoke(args...);
	}
	
	Delegate &operator+=(Ret fn (Args...))
	{
		functions.AddFunction(fn);
		return *this;
	}
	
	Delegate &operator-=(Ret fn (Args...))
	{
		functions.RemoveFunction(fn);
		return *this;
	}

private:
	
	InvokeList<Ret, Args...> functions;
	
};
#endif /* __cplusplus */

#endif /* DRA_DELEGATE_H */
