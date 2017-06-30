#ifndef _ADAS_MACRO_H
#define _ADAS_MACRO_H

#define NS_ADAS_BEGIN	{
//#define NS_ADAS_BEGIN	namespace ADAS{
#define NS_ADAS_END		}

#ifdef NULL
#undef	NULL
#endif
#define	NULL	0

#ifdef TRUE
#undef	TRUE
#endif

#ifdef FALSE
#undef	FALSE
#endif

#define TRUE	true
#define FALSE	false

#define ADAS_DBG_MSG(x)		DBG_MSG((x))
#define ADAS_DBG_ERROR(x)	DBG_ERROR((x))
#define ADAS_DBG_WARNING(x)	DBG_WARNING((x))

//typedef char			BYTE;
#define OS_QNX
#define TRACE_CLIENT
#endif
