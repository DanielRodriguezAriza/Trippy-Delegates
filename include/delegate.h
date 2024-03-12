#ifndef DRA_CAT_DEFINES

#define DRA_CAT_INTERNAL(x,y) x##y
#define DRA_CAT(x,y) DRA_CAT_INTERNAL(x,y)
#define DRA_CAT_2(x1,x2)             DRA_CAT(x1,x2)
#define DRA_CAT_3(x1,x2,x3)          DRA_CAT(x1,DRA_CAT_2(x2,x3))
#define DRA_CAT_4(x1,x2,x3,x4)       DRA_CAT(x1,DRA_CAT_3(x2,x3,x4))
#define DRA_CAT_5(x1,x2,x3,x4,x5)    DRA_CAT(x1,DRA_CAT_4(x2,x3,x4,x5))
#define DRA_CAT_6(x1,x2,x3,x4,x5,x6) DRA_CAT(x1,DRA_CAT_5(x2,x3,x4,x5,x6))

#define DRA_CAT_DEFINES

#endif



#ifndef FREE_FUNCTION
#define FREE_FUNCTION free
#endif

#ifndef ALLOC_FUNCTION
#define ALLOC_FUNCTION malloc
#endif

#ifndef REALLOC_FUNCTION
#define REALLOC_FUNCTION realloc
#endif




#ifndef RETURN_TYPE
#define RETURN_TYPE void
#error "RETURN_TYPE must be defined as a data type."
#endif

#ifndef RETURN_TYPE_IS_VOID
#define RETURN_TYPE_IS_VOID 1
#error "RETURN_TYPE_IS_VOID must be defined as 0 or 1"
#endif

#ifndef ARGUMENTS
#define ARGUMENTS int i
#error "ARGUMENTS must be defined as a comma separated list of data types and arguments named as arg1, arg2, ..., argN."
#endif

#ifndef ARGUMENTS_NAMES
#define ARGUMENTS_NAMES i
#error "ARGUMENTS_NAMES must be defined as a comma separated list of argument names."
#endif

#ifndef NAME
#define NAME undefined_delegate
#error "NAME must be defined."
#endif

#ifndef DELEGATE_IS_MULTICAST
#define DELEGATE_IS_MULTICAST
#error "DELEGATE_IS_MULTICAST must be defined as 0 or 1."
#endif

#ifndef LINKAGE
#define LINKAGE static inline
#endif

#ifndef DELEGATE_TYPE
#define DELEGATE_TYPE NAME
#endif

#ifndef FUNCTION_POINTER_TYPE
#define FUNCTION_POINTER_TYPE DRA_CAT_2(NAME, _function_ptr)
#endif

typedef RETURN_TYPE (*FUNCTION_POINTER_TYPE) (ARGUMENTS);

typedef struct {
#if DELEGATE_IS_MULTICAST
	FUNCTION_POINTER_TYPE *function_list;
	size_t function_count;
	size_t function_capacity;
#else
	FUNCTION_POINTER_TYPE function;
#endif
} DELEGATE_TYPE;


#if DELEGATE_IS_MULTICAST
LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_init) (DELEGATE_TYPE *delegate);
LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_free) (DELEGATE_TYPE *delegate);

LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_add) (DELEGATE_TYPE *delegate, FUNCTION_POINTER_TYPE function);
LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_remove) (DELEGATE_TYPE *delegate, FUNCTION_POINTER_TYPE function);
LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_remove_all) (DELEGATE_TYPE *delegate);

LINKAGE int DRA_CAT_2(DELEGATE_TYPE,_maybe_realloc) (DELEGATE_TYPE *delegate);
LINKAGE size_t DRA_CAT_2(DELEGATE_TYPE,_get_count) (DELEGATE_TYPE *delegate);
LINKAGE FUNCTION_POINTER_TYPE *DRA_CAT_2(DELEGATE_TYPE,_get_invocation_list) (DELEGATE_TYPE *delegate);
#else
LINKAGE FUNCTION_POINTER_TYPE DRA_CAT_2(DELEGATE_TYPE,_get_function_pointer) (DELEGATE_TYPE *delegate);
#endif /* DELEGATE_IS_MULTICAST */

LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_set) (DELEGATE_TYPE *delegate, FUNCTION_POINTER_TYPE function);
LINKAGE RETURN_TYPE DRA_CAT_2(DELEGATE_TYPE,_invoke) (DELEGATE_TYPE *delegate, ARGUMENTS);

#ifdef DELEGATE_IMPLEMENTATION

#if DELEGATE_IS_MULTICAST
LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_init) (DELEGATE_TYPE *delegate)
{
	delegate->function_list = NULL;
	delegate->function_count = 0;
	delegate->function_capacity = 0;
}

LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_free) (DELEGATE_TYPE *delegate)
{
	FREE_FUNCTION(delegate->function_list);
	delegate->function_count = 0;
	delegate->function_capacity = 0;
}

LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_add) (DELEGATE_TYPE *delegate, FUNCTION_POINTER_TYPE function)
{
	DRA_CAT_2(DELEGATE_TYPE,_maybe_realloc)(delegate);
	delegate->function_list[delegate->function_count] = function;
	delegate->function_count += 1;
}

LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_remove) (DELEGATE_TYPE *delegate, FUNCTION_POINTER_TYPE function)
{
	for(size_t i = 0; i < delegate->function_count; ++i)
	{
		if((delegate->function_list)[i] == function)
		{
			while(i < delegate->function_count - 1)
			{
				(delegate->function_list)[i] = (delegate->function_list)[i+1];
				++i;
			}
			delegate->function_count -= 1;
			break;
		}
	}
}

LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_remove_all) (DELEGATE_TYPE *delegate)
{
	delegate->function_count = 0;
}

LINKAGE int DRA_CAT_2(DELEGATE_TYPE,_maybe_realloc) (DELEGATE_TYPE *delegate)
{
	if(delegate->function_count >= delegate->function_capacity)
	{
		size_t new_capacity = delegate->function_capacity == 0 ? 8 : delegate->function_capacity * 2;
		void *ptr = realloc(delegate->function_list, sizeof(FUNCTION_POINTER_TYPE) * new_capacity);
		
		if(ptr == NULL)
			return 1;
		
		delegate->function_list = ptr;
		delegate->function_capacity = new_capacity;
	}
	return 0;
}

LINKAGE size_t DRA_CAT_2(DELEGATE_TYPE,_get_count) (DELEGATE_TYPE *delegate)
{
	return delegate->function_count;
}

LINKAGE FUNCTION_POINTER_TYPE *DRA_CAT_2(DELEGATE_TYPE,_get_invocation_list) (DELEGATE_TYPE *delegate)
{
	return delegate->function_list;
}

#else
LINKAGE FUNCTION_POINTER_TYPE DRA_CAT_2(DELEGATE_TYPE,_get_function_pointer) (DELEGATE_TYPE *delegate)
{
	return delegate->function;
}
#endif /* DELEGATE_IS_MULTICAST */

LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_set) (DELEGATE_TYPE *delegate, FUNCTION_POINTER_TYPE function)
{
	#if DELEGATE_IS_MULTICAST
	DRA_CAT_2(DELEGATE_TYPE,_remove_all)(delegate);
	DRA_CAT_2(DELEGATE_TYPE,_add)(delegate, function);
	#else
	delegate->function = function;
	#endif
}

//TODO: Actually add some safety checks in case the function pointer is null before calling it! Same goes for cpp code...
LINKAGE RETURN_TYPE DRA_CAT_2(DELEGATE_TYPE,_invoke) (DELEGATE_TYPE *delegate, ARGUMENTS)
{
	#if DELEGATE_IS_MULTICAST
		#if RETURN_TYPE_IS_VOID
		for(size_t i = 0; i < delegate->function_count; ++i)
			(delegate->function_list)[i](ARGUMENTS_NAMES);
		#else
		RETURN_TYPE ans;
		for(size_t i = 0; i < delegate->function_count; ++i)
			ans = (delegate->function_list)[i](ARGUMENTS_NAMES);
		return ans;
		#endif
	#else
		return delegate->function(ARGUMENTS_NAMES);
	#endif
}

#undef DELEGATE_IMPLEMENTATION
#endif /* DELEGATE_IMPLEMENTATION */


#undef RETURN_TYPE
#undef RETURN_TYPE_IS_VOID
#undef ARGUMENTS
#undef ARGUMENTS_NAMES
#undef NAME
#undef DELEGATE_TYPE
#undef FUNCTION_POINTER_TYPE


#undef FREE_FUNCTION
#undef ALLOC_FUNCTION
#undef REALLOC_FUNCTION
