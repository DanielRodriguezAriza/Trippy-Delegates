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

#ifndef RETURN_TYPE
#define RETURN_TYPE void
#error "\"RETURN_TYPE\" must be defined."
#endif

#ifndef ARGUMENTS
#define ARGUMENTS (void)
#error "\"ARGUMENTS\" must be defined."
#endif

#ifndef NAME
#define NAME undefined_delegate
#error "\"NAME\" must be defined."
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

typedef RETURN_TYPE (*FUNCTION_POINTER_TYPE) ARGUMENTS;

typedef struct {
	FUNCTION_POINTER_TYPE *function_list;
	size_t function_count;
} DELEGATE_TYPE;

LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_init) (DELEGATE_TYPE *delegate);
LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_free) (DELEGATE_TYPE *delegate);

LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_add) (DELEGATE_TYPE *delegate, FUNCTION_POINTER_TYPE function);
LINKAGE void DRA_CAT_2(DELEGATE_TYPE,_remove) (DELEGATE_TYPE *delegate, FUNCTION_POINTER_TYPE function);

LINKAGE RETURN_TYPE DRA_CAT_2(DELEGATE_TYPE,_invoke) ARGUMENTS;

#undef RETURN_TYPEa
#undef ARGUMENTS
#undef NAME
#undef DELEGATE_TYPE
#undef FUNCTION_POINTER_TYPE
