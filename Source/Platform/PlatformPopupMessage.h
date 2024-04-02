#pragma once
#if defined(HYDRO_PLATFORM_WINDOWS)
#include "Windows/WindowsPopupMessage.h"
#elif defined(HYDRO_PLATFORM_UNIX)
#include "Unix/UnixPopupMessage.h"
#endif