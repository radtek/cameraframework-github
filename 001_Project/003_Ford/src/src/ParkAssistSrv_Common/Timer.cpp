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

#include "Timer.hpp"
/**
* @brief CTimer::stopTimer
* @return
*/
using namespace std;

/**
* @brief CTimer::~CTimer
*/
CTimer::~CTimer()
{
    stopTimer();
}

void CTimer::startTimer(std::chrono::milliseconds const & interval,
                                        std::function<void(void)> const & callback)
{   
    stopTimer();
    
    auto locked = std::unique_lock<std::mutex>(mutex);    
    stop = false;
    LOG_INFO(LOG_RVC, "CTimer::startTimer() Called");
    thread = std::thread([=]()
    {
        auto locked = std::unique_lock<std::mutex>(mutex);    
        if(! stop) // We hold the mutex that protects stop
        {
            auto result = terminate.wait_for(locked, interval);

            if (result == std::cv_status::timeout)
            {
                callback();
            }
        }
    });
}

void CTimer::stopTimer()
{  

    // Set the predicate
    auto locked = std::unique_lock<std::mutex>(mutex);
    stop = true;

    LOG_INFO(LOG_RVC, "CTimer::stopTimer() Called");
    // Tell the thread the predicate has changed
    terminate.notify_one();

    if(thread.joinable())
    {
        thread.join();
    }
}




/**
* @brief CTimer::startTimerDetachable
* @param p_TimeInterval
* @param cbfunc
* @return
*/
ETimerReturn CTimer::startTimerDetachable(int p_TimeInterval, function<void(void)> cbfunc)
{           
    m_bFlagExecute = true;
    m_eTimerReturn = eTimer_INVALID_RETURN;
     std::thread([this, p_TimeInterval, cbfunc]()
    {
        if(m_bFlagExecute) 
        {
            m_eTimerReturn = eTimer_START_TIMER_SUCCESS;
            std::this_thread::sleep_for(
            std::chrono::seconds(p_TimeInterval));
            if(m_bFlagExecute)
            {
                cbfunc();
            }  
        }
    }).detach();

   return m_eTimerReturn;

}

/**
* @brief CTimer::startTimerCyclic
* @param p_TimeInterval
* @param cbfunc
* @return
*/
ETimerReturn CTimer::startTimerCyclic(int p_TimeInterval, function<void(void)> cbfunc)
{
    ////LOG_INFO(Log::e_LOG_CONTEXT_CLOCK_SVC,"Log::e_LOG_CONTEXT_CLOCK_SVC...");
    m_bFlagExecute = true;
    m_eTimerReturn = eTimer_INVALID_RETURN;
  //  cout << "data in TImer before thread is ::" << m_pobjContextTimer->m_stContextHMIClockData.getM_TimeWithoutSec() << "\n";
    m_ThrdVar = std::thread([this, p_TimeInterval, cbfunc]()
    {       
        //m_eTimerReturn = eTimer_START_TIMER_SUCCESS;
        cbfunc();
        this->m_eTimerReturn = eTimer_START_TIMER_SUCCESS;
        while(m_bFlagExecute) 
        {                   
            std::this_thread::sleep_for(
            std::chrono::seconds(p_TimeInterval));
           if(m_bFlagExecute)
            {
             //   cout << "Firing from Timer...\n";
                cbfunc();
            }
            else
            {
              //  cout << "Dont fire the callback...\n";
            }
        }
    });

    return m_eTimerReturn;
    
}
/**
* @brief CTimer::startTimerCyclicDetachable
* @param p_TimeInterval
* @param cbfunc
* @return
*/
ETimerReturn CTimer::startTimerCyclicDetachable(int p_TimeInterval, function<void(void)> cbfunc)
{
    m_bFlagExecute = true;
    m_eTimerReturn = eTimer_INVALID_RETURN;
    std::thread([this, p_TimeInterval, cbfunc]()
    {
        m_eTimerReturn = eTimer_START_TIMER_SUCCESS;
        cbfunc();
        while(m_bFlagExecute) 
        {                   
            std::this_thread::sleep_for(
            std::chrono::seconds(p_TimeInterval));
            cbfunc();
        }
    }).detach();

    return m_eTimerReturn;
}
/**
* @brief CTimer::is_running
* @return
*/
bool CTimer::is_running() const noexcept 
{
    return (m_bFlagExecute && 
     m_ThrdVar.joinable() );
}
