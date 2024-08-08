#include "HydroPCH.h"
#include "PopupMessage.h"
#include "Platform\PlatformPopupMessage.h"

namespace Hydro
{
    PopupMessage::PopupMessage(HYDRO_POPUPMESSAGE_SIGNATURE)
        : Title(Title), Message(Message), Response(Response), Icon(Icon)
    {
        
    }

    PopupMessage::~PopupMessage()
    {
        OnPopupMessageClosed.ClearAll();
        OnPopupMessageOpened.ClearAll();
    }

    Ref<PopupMessage> PopupMessage::Create(HYDRO_POPUPMESSAGE_SIGNATURE)
    {
        HYDRO_OS_PLATFORM_RETURN(PopupMessage, Title, Message, Response, Icon);
    }
}
