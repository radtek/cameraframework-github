/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            PAMPresctrl_utlis.h
* @ingroup         Park-Asist
* @author          Atita Halemani and Ashwini Shamaprasad (Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           Provide the mem copy and strcpy utlis to PAM
*				   
*/
#ifndef _BT_UTILS_H_
#define _BT_UTILS_H_
#include <string.h>


///////////////////////////////////////////////////////////////////////////////
/// \brief A wrapper for memcpy() which takes both source size and destination 
/// \n size and uses the smallest of the two.
///
/// \param [in] : DP
/// \n Destination pointer 
/// \param [in] : DS
/// \n Destination buffer size (in bytes)
/// \param [in] : SP
/// \n Source pointer 
/// \param [in] : SS
/// \n Source buffer size (in bytes)     
/// \retval Same as memcpy   
#define MEMCPY_S(DP, DS, SP, SS) memcpy(DP, SP, (DS > SS)? SS:DS);

///////////////////////////////////////////////////////////////////////////////
/// \brief A wrapper for strlcpy() which takes both source size and destination 
/// \n size and uses the smallest of the two.
///
/// \param [in] : DP
/// \n Destination pointer 
/// \param [in] : DS
/// \n Destination buffer size (in bytes, including space for '\0')
/// \param [in] : SP
/// \n Source pointer 
/// \param [in] : SS
/// \n Source string size size (in bytes, including '\0')    
/// \n Eg. dest[12], src[10], "hello" -> STRLCPY_S(dest,12,src, 10 or 6)
/// \retval Same as strlcpy
#define STRLCPY_S(DP, DS, SP, SS) strlcpy(DP, SP, (DS > SS)? SS:DS);

#endif
