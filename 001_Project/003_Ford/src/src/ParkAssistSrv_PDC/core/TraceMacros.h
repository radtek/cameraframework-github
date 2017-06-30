
#ifndef TRACEMACROS_HPP_
#define TRACEMACROS_HPP_

#define DLTLOG
#ifdef DLTLOG

#include "../../ParkAssistSrv_Common/CommonCore.hpp"
  

#define PAM_LOG_INFO(B,...)          LOG_INFO(LOG_PDC,B, ## __VA_ARGS__)   
#define PAM_LOG_DEBUG(B,...)         LOG_DEBUG(LOG_PDC,B, ## __VA_ARGS__)
#define PAM_LOG_WARNING(B,...)       LOG_WARNING(LOG_PDC,B, ## __VA_ARGS__)
#define PAM_LOG_ERROR(B,...)         LOG_ERROR(LOG_PDC,B, ## __VA_ARGS__)

#define PDCA_LOG_INFO(B,...)          LOG_INFO(LOG_PDC,B, ## __VA_ARGS__)   
#define PDCL_LOG_INFO(B,...)          LOG_INFO(LOG_PDC,B, ## __VA_ARGS__)   
#define PDCC_LOG_INFO(B,...)          LOG_INFO(LOG_PDC,B, ## __VA_ARGS__)     
#else

 #ifdef  PAM_LOG_INFO
    #undef  PAM_LOG_INFO
 #endif
#ifdef	PAM_LOG_DEBUG
   #undef  PAM_LOG_DEBUG
#endif
#ifdef	PAM_LOG_WARNING
   #undef  PAM_LOG_WARNING
#endif
#ifdef	PAM_LOG_ERROR
   #undef  PAM_LOG_ERROR
#endif
#ifdef	PDCA_LOG_INFO
   #undef  PDCA_LOG_INFO
#endif
#ifdef	PDCL_LOG_INFO
   #undef  PDCL_LOG_INFO
#endif
#ifdef	PDCC_LOG_INFO
   #undef  PDCC_LOG_INFO
#endif


#define PAM_LOG_INFO(B,...)            printf(B, ## __VA_ARGS__)
#define PAM_LOG_DEBUG(B,...)           printf(B, ## __VA_ARGS__)
#define PAM_LOG_WARNING(B,...)         printf(B, ## __VA_ARGS__)
#define PAM_LOG_ERROR(B,...)           printf(B, ## __VA_ARGS__)

#define PDCA_LOG_INFO(B,...)           printf(B, ## __VA_ARGS__)
#define PDCL_LOG_INFO(B,...)           printf(B, ## __VA_ARGS__)
#define PDCC_LOG_INFO(B,...)           printf(B, ## __VA_ARGS__)
#endif  //========

#endif /*IOCTRACEMACROS_HPP_*/

