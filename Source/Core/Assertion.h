#pragma once
#include "Macros.h"

namespace Hydro
{
	#if !defined(HYDRO_ASSERT)
		#if defined(HYDRO_DEBUG)
			#include <cassert>
			#define HYDRO_ASSERT(condition, message) assert((condition) && (message))
			#if defined HYDRO_PLATFORM_WINDOWS
			#define HYDRO_BREAK()					 __debugbreak()
			#endif
		#else
			#define HYDRO_ASSERT HYDRO_VOID
			#define HYDRO_BREAK  HYDRO_VOID
		#endif
	#endif
	
}