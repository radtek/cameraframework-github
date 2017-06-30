#ifndef __BASE_CCREF_H__
#define __BASE_CCREF_H__

#include "ADASMarco.h"

//NS_ADAS_BEGIN



class Ref;


class Ref
{
public:

    void retain();


    void release();


    Ref* autorelease();


    unsigned int getReferenceCount() const;

protected:
    Ref();
    virtual ~Ref();

protected:

    unsigned int _referenceCount;

    friend class AutoreleasePool;
};


//NS_ADAS_END

#endif // __BASE_CCREF_H__
