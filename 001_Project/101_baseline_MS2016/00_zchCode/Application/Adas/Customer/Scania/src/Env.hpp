#ifndef _ENV_HPP
#define _ENV_HPP
#include "svs.h"
class Env
{
public: // enum
	enum ETarget
	{
		SCANIA  = 0,
        MAN     = 1,
	};

public:
	static BOOLEAN initialize();

	static BOOLEAN isMANTarget()	{ return (s_eTarget == MAN);		}
	static BOOLEAN isScaniaTarget()	{ return s_eTarget == SCANIA;	}
	static BOOLEAN isUseCmdLine()	{ return s_bUseCmdLine;			}

	//static void		activate();
	//static void 	deactivate();

private:
	static ETarget 	s_eTarget;
	static BOOLEAN	s_bUseCmdLine;
};

#endif
