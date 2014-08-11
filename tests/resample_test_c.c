#ifdef _WIN32
#define STBR_ASSERT(x) \
	if (!(x)) \
		__debugbreak();
#endif

#define STB_RESAMPLE_IMPLEMENTATION
#define STB_RESAMPLE_STATIC
#include "stb_resample.h"

// Just to make sure it will build properly with a c compiler
