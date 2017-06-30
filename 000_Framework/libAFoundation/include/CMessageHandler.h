
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CMESSAGE_HANDLER_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CMESSAGE_HANDLER_H__

#include "platformdef.h"
#include "MessageForQueue.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

// #define BEGIN_DISPATCH(CLASSNAME)    \
// VOID CLASSNAME::dispatchEvent(UInt32 uiEventID, VOID* pData)    \
// {\
//     switch(uiEventID)    \
//     {

// #define DISPATCH_EVENT(uiEventID, Function)    \
//         case (uiEventID):    \
//         {    \
//             Function(pData);\
//         }    \
//         break;

// #define DISPATCH_EVENT_NOPARAM(uiEventID, Function)    \
//         case (uiEventID):    \
//         {    \
//             Function();\
//         }    \
//         break;

// #define END_DISPATCH    \
//         default:    \
//             break;    \
//     }    \
//     return;    \
// }

// #define DECLARE_DISPATCH    \
//     virtual VOID dispatchEvent(UInt32 uiEventID, VOID* pData);

class CMessageHandler
{
public:
    //CMessageHandler();
    //virtual ~CMessageHandler();

    VOID handle(MessageForQueue* pMsg);

protected:
    /*switch( uiType )
        {
        case eMsgType_CAN:
            xxSubHandler::getInstance()->dispatchEvent(uiID, pData);
            break;
        case eMsgType_HMI:
            xxSubHandler::getInstance()->dispatchEvent(uiID, pData);
            break;
        case eMsgType_ScaniaOnOff:
            xxSubHandler::getInstance()->dispatchEvent(uiID, pData);
            break;
        case eMsgType_Diagnostic:
            xxSubHandler::getInstance()->dispatchEvent(uiID, pData);
            break;
        }
     */
    virtual VOID _handle(UInt32 uiType, UInt32 uiEventID, const string& pData) = 0;

};

class CMessageSubHandler
{
public:
    virtual VOID dispatchEvent(UInt32 uiEventID, const string& pData) = 0;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CMESSAGE_HANDLER_H__