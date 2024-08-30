#pragma once

#define HYDRO_VERSION_MAJ 1
#define HYDRO_VERSION_MIN 0
#define HYDRO_VERSION ((HYDRO_VERSION_MAJ << 8 & 0xFF00) | (HYDRO_VERSION_MIN & 0xFF))

#if !defined(HYDRO_RHI_NAME)
#if defined(HYDRO_PLATFORM_DIRECTX)
#define HYDRO_RHI_NAME "DirectX"
#elif defined(HYDRO_PLATFORM_VULKAN)
#define HYDRO_RHI_NAME "Vulkan"
#elif defined(HYDRO_PLATFORM_OPENGL)
#define HYDRO_RHI_NAME "OpenGL"
#endif
#endif

#if !defined(HYDRO_OS_NAME)
    #if defined(HYDRO_PLATFORM_WINDOWS)
        #define HYDRO_OS_NAME "Windows"
    #elif defined(HYDRO_PLATFORM_UNIX)
        #define HYDRO_OS_NAME "Linux"
    #endif
#endif
 

#if !defined(HYDRO_CONFIG_NAME)
#if defined(HYDRO_DEBUG)
#define HYDRO_CONFIG_NAME "Debug"
#else
#define HYDRO_CONFIG_NAME "Release"
#endif
#endif


#define HYDRO_VOID __noop
#define HYDRO_NODISCARD [[nodiscard]]


#if !defined(HYDRO_FILENAME_MAX_LENGTH)
#define HYDRO_FILENAME_MAX_LENGTH MAX_PATH
#endif

#define HYDRO_NOT_COPYABLE_NOT_MOVABLE(ClassType) \
    ClassType(const ClassType&) = delete; \
    ClassType(ClassType&&) = delete; \
    ClassType& operator=(const ClassType&) = delete; \
    ClassType& operator=(ClassType&&) = delete


#if defined(HYDRO_PLATFORM_OPENGL)
#define HYDRO_RHI_PLATFORM_RETURN(ClassName, ...) return CreateRef<OpenGL##ClassName>(__VA_ARGS__)
#elif defined(HYDRO_PLATFORM_VULKAN)
#define HYDRO_RHI_PLATFORM_RETURN(ClassName, ...) return CreateRef<Vulkan##ClassName>(__VA_ARGS__)
#elif defined(HYDRO_PLATFORM_DIRECTX)
#define HYDRO_RHI_PLATFORM_RETURN(ClassName, ...) return CreateRef<DirectX##ClassName>(__VA_ARGS__)
#endif

#if defined(HYDRO_PLATFORM_WINDOWS)
#define HYDRO_OS_PLATFORM_RETURN(ClassName, ...) return CreateRef<Windows##ClassName>(__VA_ARGS__)
#elif defined(HYDRO_PLATFORM_UNIX)
#define HYDRO_OS_PLATFORM_RETURN(ClassName, ...) return CreateRef<Linux##ClassName>(__VA_ARGS__)
#endif


#define HYDRO_ARRAY_COUNT(Array) (sizeof((Array)) / sizeof(*(Array)))

#define HYDRO_NAME_MAX_SIZE 128

#define HYDRO_UNINITIALIZED         0xCD
#define HYDRO_DEFAULT_MAX_RESOURCE  256
#define HYDRO_MAX_TEXTURES          128
#define HYDRO_MAX_SHADERS           64
#define HYDRO_MAX_SOUNDS            256

