#include "global.h"
#include "Castable.h"

#define DECLARE_GET_INSTANCE(Class)\
		EXTERN_C DLL_EXPORT Castable*  __get__plugin__instance(){\
			return new Class();\
		}

#define DECLARE_PLUGIN(Class)\
	DECLARE_GET_INSTANCE(Class)\
	EXTERN_C DLL_EXPORT int	 __get__plugin__version(){\
		return 0;\
	}
