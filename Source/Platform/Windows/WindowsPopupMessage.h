#pragma once
#include <unordered_map>

#include "Core/PopupMessage.h"

namespace Hydro
{
    class WindowsPopupMessage : public PopupMessage
    {
    public:
        WindowsPopupMessage(HYDRO_POPUPMESSAGE_SIGNATURE);
        PopupMessageResult Show() override;
        
        using ResponseConvertor = std::unordered_map<PopupMessageResponse, int32>;
        using ResultConvertor = std::unordered_map<int32, PopupMessageResult>;
        using IconConvertor = std::unordered_map<PopupMessageIcon, int32>;
    private:
        static ResponseConvertor s_ResponseConvertor;
        static ResultConvertor s_ResultConvertor;
        static IconConvertor s_IconConvertor;
    };
}
