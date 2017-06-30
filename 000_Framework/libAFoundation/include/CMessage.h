
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CMESSAGE_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CMESSAGE_H__

#include "TypeDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

struct tagBaseMessage
{

    tagBaseMessage(UInt32 uiType,UInt32 uiID, CHAR* pData)
        : _uiType(uiType)//modulename
        , _uiID(uiID)//cameraID
        , _pData(pData)//camera status
    {}

    tagBaseMessage()
        : _uiType(0)
        , _uiID(0)
        , _pData(0)
    {}

    UInt32  _uiType;
    UInt32  _uiID;
    CHAR* _pData;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CMESSAGE_H__