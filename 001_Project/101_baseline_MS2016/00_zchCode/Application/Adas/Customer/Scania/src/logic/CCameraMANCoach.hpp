#ifndef _CADAS_CTRL_CAMAERASTATE_MANCOACH_HPP_
#define _CADAS_CTRL_CAMAERASTATE_MANCOACH_HPP_

#include "CCamera.hpp"
#include "CCameraMANTruck.hpp"
//as cusotmer request no differece between MAN truck and coach variant 
class CReverseCameraMC: public CReverseCameraMT
{
public:
	CReverseCameraMC(EPos ePos);
	virtual ~CReverseCameraMC();
};

class CGeneralCameraMC : public CGeneralCameraMT
{
public:
	CGeneralCameraMC(EPos ePos);
	virtual ~CGeneralCameraMC();
};

#endif  

