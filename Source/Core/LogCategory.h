#pragma once

namespace Hydro
{
    #define HYDRO_DECLARE_LOG_CATEGORY_STATIC(ClassName, CategoryName) \
        struct ClassName##LogCategory \
        {\
            static inline std::string s_CategoryName = CategoryName;\
        };
}
