#include "VertexArray.h"

#include "Macros.h"
#include "Platform/PlatformVertexArray.h"

namespace Hydro
{
    Ref<VertexArray> VertexArray::Create()
    {
        HYDRO_RHI_PLATFORM_RETURN(VertexArray);
    }
}
