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

private:
	
	inline void Set(Ret fn(Args...)) //this should maybe be in the public interface, after all, it really does the same as operator= and the constructor so yeah.
	{
		this->RemoveAll();
		this->Add(fn);
	}

private:
	
	InvokeList<Ret, Args...> functions;
	
};

#endif /* DRA_DELEGATE_H */
