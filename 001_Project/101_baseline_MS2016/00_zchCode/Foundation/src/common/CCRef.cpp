

#include "CCRef.h"
//#include "CCAutoreleasePool.h"



Ref::Ref()
: _referenceCount(1) // when the Ref is created, the reference count of it is 1
{

}

Ref::~Ref()
{

}

void Ref::retain()
{
    //CCASSERT(_referenceCount > 0, "reference count should greater than 0");
    ++_referenceCount;
}

void Ref::release()
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
    //PoolManager::getInstance()->getCurrentPool()->addObject(this);
    return this;
}

unsigned int Ref::getReferenceCount() const
{
    return _referenceCount;
}



