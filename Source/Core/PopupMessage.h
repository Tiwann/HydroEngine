#pragma once
#include "Macros.h"
#include "MulticastDelegate.h"
#include "SharedPointer.h"

#define HYDRO_POPUPMESSAGE_SIGNATURE const std::string& Title, const std::string& Message, PopupMessageResponse Response, PopupMessageIcon Icon

namespace Hydro
{
    enum class PopupMessageResponse
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

    enum class PopupMessageResult
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

    enum class PopupMessageIcon
    {
        Error,
        Question,
        Warning,
        Info
    };

    
    
    class PopupMessage
    {
        using PopupMessageAction = MulticastDelegate<void()>;
    public:
        HYDRO_NOT_COPYABLE_NOT_MOVABLE(PopupMessage);
        PopupMessage(HYDRO_POPUPMESSAGE_SIGNATURE);
        virtual ~PopupMessage();
        
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
