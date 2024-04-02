#pragma once
#include "Macros.h"
#include "MulticastDelegate.h"
#include "SharedPointer.h"

#define HYDRO_POPUPMESSAGE_SIGNATURE const std::string& Title, const std::string& Message, PopupMessageResponse Response, PopupMessageIcon Icon

namespace Hydro
{
    using PopupMessageResponse = enum class PopupMessageResponse
    {
        None,
        OK,
        OKCancel,
        YesNoCancel,
        YesNo,
        RetryCancel,
        CancelTryContinue,
        AbortRetryIgnore
    };

    using PopupMessageResult = enum class PopupMessageResult
    {
        None,
        OK,
        Cancel,
        Yes,
        No,
        Retry,
        Try,
        Continue,
        Abort,
        Ignore
    };

    using PopupMessageIcon = enum class PopupMessageIcon
    {
        Error,
        Question,
        Warning,
        Info
    };

    
    
    class PopupMessage
    {
        using PopupMessageAction = MulticastDelegate<>;
    public:
        HYDRO_NO_COPYABLE_NO_MOVABLE(PopupMessage);
        PopupMessage(HYDRO_POPUPMESSAGE_SIGNATURE);
        virtual ~PopupMessage() = default;
        
        std::string Title;
        std::string Message;
        PopupMessageResponse Response;
        PopupMessageIcon Icon;
        PopupMessageAction OnPopupMessageOpened;
        PopupMessageAction OnPopupMessageClosed;
        
        virtual PopupMessageResult Show() = 0;

        static Ref<PopupMessage> Create(HYDRO_POPUPMESSAGE_SIGNATURE);
    };
}
