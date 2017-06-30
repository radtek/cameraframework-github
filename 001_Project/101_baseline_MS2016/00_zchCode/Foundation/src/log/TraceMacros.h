#ifndef TRACEMACROS_HPP_
#define TRACEMACROS_HPP_

#ifdef TRACE_CLIENT

#include "api/sys/tracesrv/pf/trace/src/private/HBTraceMacros.hpp"
#include "api/sys/tracesrv/pf/trace/src/CTraceThread.hpp"
#include "api/sys/tracesrv/pf/trace/src/CHBNullTracePersistence.hpp"

#else

 #ifdef  DBG_MSG
    #undef  DBG_MSG
 #endif


 #define DBG_MSG(x)    		printf x
 #define DBG_ERROR(x)  		printf x
 #define DBG_WARNING(x)    	printf x

 #define TRC_SCOPE_DEF(x, y, z)
 #define TRC_SCOPE(x, y, z)



#endif  //========

#endif /*IOCTRACEMACROS_HPP_*/

