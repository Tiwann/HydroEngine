#pragma once

namespace Hydro
{
	#if !defined(HYDRO_ASSERT)
		#if defined(HYDRO_DEBUG)
			#include <cassert>
			#define HYDRO_ASSERT(condition, message) assert((condition) && (message))
		#else
			#define HYDRO_ASSERT
		#endif
	#endif
}