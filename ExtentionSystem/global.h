#include <Windows.h>

#define DLL_EXPORT	__declspec(dllexport)
#define EXTERN_C	extern "C"
#define DISABLE_COPY(Class) \
	Class(const Class &); \
	Class &operator=(const Class &);

#ifdef EXTENTIONSYSTEM_EXPORTS
#define ExtentionSystem_DLL_API		__declspec(dllexport)
#else
#define ExtentionSystem_DLL_API		__declspec(dllimport)
#endif