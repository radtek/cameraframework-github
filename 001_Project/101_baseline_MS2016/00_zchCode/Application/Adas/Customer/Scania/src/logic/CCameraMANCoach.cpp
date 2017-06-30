#include "CCamera.hpp"
#include "CCameraMANCoach.hpp"

TRC_SCOPE_DEF(ADAS, CReverseCameraMC, CReverseCameraMC);
CReverseCameraMC::CReverseCameraMC(CCamera::EPos ePos)
: CReverseCameraMT(ePos)
{
    TRC_SCOPE(ADAS, CReverseCameraMC, CReverseCameraMC);
    DBG_MSG(("*********CReverseCameraMC created on pos %d!**********\n",ePos));
}

CReverseCameraMC::~CReverseCameraMC()
{
}

TRC_SCOPE_DEF(ADAS, CGeneralCameraMC, CGeneralCameraMC);
CGeneralCameraMC::CGeneralCameraMC(CCamera::EPos ePos)
: CGeneralCameraMT(ePos)
{
    TRC_SCOPE(ADAS, CGeneralCameraMC, CGeneralCameraMC);
    DBG_MSG(("*********CGeneralCameraMC created on pos %d!*********\n",ePos));
}

CGeneralCameraMC::~CGeneralCameraMC()
{

}

