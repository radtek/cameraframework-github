
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AREA_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AREA_H__

#include "TypeDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class Area
{
public:
    Area();

    virtual ~Area()
    {
        // if(nullptr != m_pHasCompoundedArea){
        //     free(m_pHasCompoundedArea);
        //     m_pHasCompoundedArea = nullptr;
        // }
    }

    virtual void CompoundArea() = 0;

    virtual void DeCompoundArea() = 0;

public:
    static BYTE* m_pHasCompoundedArea;
};

class DecoratorArea : public Area
{
public:
    DecoratorArea(Area* area);

public:
    Area* m_pArea = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AREA_H__