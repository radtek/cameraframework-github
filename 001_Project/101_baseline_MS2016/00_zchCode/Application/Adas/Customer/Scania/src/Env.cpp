#include "Env.hpp"
#include <unistd.h>


Env::ETarget Env::s_eTarget = Env::SCANIA;
BOOLEAN	Env::s_bUseCmdLine = FALSE;

TRC_SCOPE_DEF(ADAS, Env, initialize);
BOOLEAN Env::initialize()
{
    TRC_SCOPE(ADAS, Env, initialize);
    s_eTarget =(Env::ETarget) CCommandLineParser::getInstance()->getItemUInt("-iVariant");

	if( CCommandLineParser::getInstance()->getItemBool("useCmdEOL") )
	{
		s_bUseCmdLine = TRUE;
	}

	return TRUE;
}
