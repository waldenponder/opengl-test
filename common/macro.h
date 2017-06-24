#ifdef EXPORT_COMMON
#define COMMON_API _declspec(dllexport)
#else 
#define COMMON_API _declspec(dllimport)
#endif