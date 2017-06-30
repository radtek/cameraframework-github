/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            CPresCoreHandler.hpp
* @ingroup         Park-Asist
* @author          Atita Halemani and Ashwini Shamaprasad (Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           AMBConsumerHandler Consumes events from AMB and routes to required module(RVC,APA and VPA)
*                  based on the events it received.
*                  
*/

#ifndef CPRESCORE_HANDLER_HPP
#define CPRESCORE_HANDLER_HPP

#include "ParkAssistSrv_Common/CommonCore.hpp"

class CPresCoreHandler 
{
    public:
        CPresCoreHandler();

        ~CPresCoreHandler();
        static CPresCoreHandler *m_pobjCPresCoreHandler;
        static CPresCoreHandler* getInstance();

        void addRequestToPresCore(EParkAssistReqId p_peParkAssistReqId);
		std::shared_ptr<RequestBase> l_PtrReqBase ;
    private:
        RequestBase* CreateRequest(EParkAssistReqId p_peParkAssistReqId);

};

#endif
