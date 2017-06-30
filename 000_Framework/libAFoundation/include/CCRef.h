#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CCREF_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CCREF_H__

#include "TypeDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

class Ref
{
public:

    VOID retain();


    VOID release();


    Ref* autorelease();


    UInt32 getReferenceCount() const;

protected:
    Ref();
    virtual ~Ref();

protected:

    UInt32  _referenceCount;
};

}//AFoundation
}//AFramework
}//Adas
}//Harman


#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CCREF_H__
