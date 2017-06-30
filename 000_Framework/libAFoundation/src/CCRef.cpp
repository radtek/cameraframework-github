
#include "CCRef.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

Ref::Ref()
: _referenceCount(1) // when the Ref is created, the reference count of it is 1
{

}

Ref::~Ref()
{

}

VOID Ref::retain()
{
    //CCASSERT(_referenceCount > 0, "reference count should greater than 0");
    ++_referenceCount;
}

VOID Ref::release()
{
   // CCASSERT(_referenceCount > 0, "reference count should greater than 0");
    --_referenceCount;

    if (_referenceCount == 0)
    {
        delete this;
    }
}

Ref* Ref::autorelease()
{
    return this;
}


UInt32 Ref::getReferenceCount() const
{
    return _referenceCount;
}

}
}
}
}

