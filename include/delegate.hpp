#ifndef DRA_DELEGATE_HPP
#define DRA_DELEGATE_HPP

#include <vector>

#define DelegateType typedef Delegate

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
	
	inline void Add(Ret (*fn) (Args...))
	{
		functions.push_back(fn);
	}
	
	inline void Remove(Ret (*fn) (Args...))
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
	
	inline void RemoveAll()
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
		this->Set(fn);
	}
	
	~Delegate()
	{}
	
	Delegate &operator=(Ret fn (Args...))
	{
		this->Set(fn);
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
		this->Add(fn);
		return *this;
	}
	
	Delegate &operator-=(Ret fn (Args...))
	{
		this->Remove(fn);
		return *this;
	}
	
	inline void Add(Ret fn(Args...))
	{
		this->functions.Add(fn);
	}
	
	inline void Remove(Ret fn(Args...))
	{
		this->functions.Remove(fn);
	}
	
	inline void RemoveAll()
	{
		this->functions.RemoveAll();
	}
	
	inline std::vector<Ret(Args ...)> &GetInvocationList()
	{
		return this->functions.GetList();
	}
	
	inline void Set(Ret fn(Args...))
	{
		this->RemoveAll();
		this->Add(fn);
	}

private:
	
	InvokeList<Ret, Args...> functions;
	
};


template<typename T, typename ...Args>
class SinglecastDelegateExecutor
{
public:
	T invokeFunction(T (*fn)(Args...), Args ...args)
	{
		if(fn == NULL)
			return T{};
		return fn(args...);
	}
};

template<typename ...Args>
class SinglecastDelegateExecutor<void, Args...>
{
public:
	void invokeFunction(void (*fn)(Args...), Args ...args)
	{
		if(fn == NULL)
			return;
		fn(args...);
	}
};


template<typename Signature>
class SinglecastDelegate;

template<typename Ret, typename ...Args>
class SinglecastDelegate<Ret(Args...)>
{
public:
	
	SinglecastDelegate()
	:function{NULL}
	{}
	
	SinglecastDelegate(Ret fn (Args...))
	:function{NULL}
	{
		this->Set(fn);
	}
	
	~SinglecastDelegate()
	{}
	
	SinglecastDelegate &operator=(Ret fn (Args...))
	{
		this->Set(fn);
		return *this;
	}
	
	Ret Invoke(Args ...args)
	{
		SinglecastDelegateExecutor<Ret,Args...> ex;
		return ex.invokeFunction(function, args...);
	}
	
	Ret operator()(Args ... args)
	{
		return this->Invoke(args...);
	}
	
	inline void Set(Ret fn(Args...))
	{
		this->function = fn;
	}
	
	inline Ret(*Get())(Args...)
	{
		return function;
	}

private:
	
	Ret (*function)(Args...);
	
};

#endif /* DRA_DELEGATE_H */
