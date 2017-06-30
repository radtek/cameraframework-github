
/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            Timer.cpp
* @ingroup         Park-Asist
* @author          Atita Halemani and Ashwini Shamaprasad (Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           Provide the timer functionality to PAM
*				   
*/
#ifndef TIMER_SERVICE_HPP
#define TIMER_SERVICE_HPP

/***
This class is responsible for setting timer as well as callbacks and 
the apis provided are self explanatory and the methods take secs unit as time interval
***/
#include <functional>
#include <chrono>
#include <future>
#include <cstdio>
#include <iostream>
#include <thread>
using namespace std;
#include "ParkAssistSrv_Common/CommonCore.hpp"

 
typedef enum _ETimerReturn
{
    eTimer_INVALID_RETURN,
    eTimer_START_TIMER_SUCCESS,
    eTimer_START_TIMER_FAILURE,
    eTimer_STOP_TIMER_SUCCESS,
    eTimer_STOP_TIMER_FAILURE
}ETimerReturn;
/**
* @brief The CTimer class
*/
class CTimer
{
    public:
        CTimer()
        :m_bFlagExecute(false)
        {
            m_eTimerReturn = eTimer_INVALID_RETURN;
        }
        ~CTimer();
        void startTimer(std::chrono::milliseconds const & interval,
                                                std::function<void(void)> const & callback);
        void stopTimer();
        ETimerReturn startTimerDetachable(int p_eTimeInterval, function<void(void)> func);
        ETimerReturn startTimerCyclic(int p_TimeInterval, function<void(void)> cbfunc);
        ETimerReturn startTimerCyclicDetachable(int p_eTimeInterval, function<void(void)> func);
        bool is_running() const noexcept;
        bool m_bFlagExecute;

        
    private:
        std::thread  m_ThrdVar;
        ETimerReturn m_eTimerReturn;
        bool stop; // This is the thing the thread is waiting for
        std::thread thread;
        std::mutex mutex;
        std::condition_variable terminate;
};


#endif
