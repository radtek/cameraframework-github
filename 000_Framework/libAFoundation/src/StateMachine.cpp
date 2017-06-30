
#ifdef LINUX_OS
#include "../include/StateMachine.h"
#else
#include "..\include\StateMachine.h"
#endif

#include <stdio.h>
#include <string.h>

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

VOID StateMachine::StateMachineHandler::_handle(UInt32 uiType, UInt32 uiID, const string& pData)
{
    ALOGI("StateMachine begine handl message : uiID = %d \n", uiID);

    if (m_bIsConstructionCompleted) {
        /** Normal path */
        ALOGI("begin ProcessMsg !!!\n");
        ProcessMsg(uiType, uiID, pData);
        ALOGI("end ProcessMsg !!!\n");
    } else if (!m_bIsConstructionCompleted && (uiID == eMessageType_SM_INIT_COMPLETE)) {
        /** Initial one time path. */
        m_bIsConstructionCompleted = TRUE;
        InvokeEnterMethods(0);
        ALOGI("init statemachine complete !!!\n");
    } else {
        ALOGE("error path !!!!!! \n");
    }

    PerformTransitions();
    ALOGI("stateStack synchronized complete !!!\n");
}

shared_ptr<State> StateMachine::StateMachineHandler::GetCurrentState()// const
{
    shared_ptr<State> cstate = m_vStateStack[m_iStateStackTopIndex]->m_pState;
    return cstate;
}

shared_ptr<StateMachine::StateMachineHandler::StateInfo> StateMachine::StateMachineHandler::AddState(shared_ptr<State> state, shared_ptr<State> parent)
{
    ALOGI("AddState : state = %s \n", state->GetStateName().c_str());
    shared_ptr<StateInfo> parentStateInfo;
    if (parent != nullptr) {
        auto it = m_mapStateInfo.find(parent);
        if (it != m_mapStateInfo.end()) {
            parentStateInfo = it->second;
        }
        if (parentStateInfo == NULL) {
            shared_ptr<StateInfo> tmp = AddState(parent, nullptr);
        }
    }

    shared_ptr<StateInfo> stateInfo;
    auto it = m_mapStateInfo.find(state);
    if (it != m_mapStateInfo.end()) {
        stateInfo = it->second;
    }
    if (stateInfo == nullptr) {
        shared_ptr<StateInfo> tmp(new StateInfo());
        stateInfo = tmp;
        m_mapStateInfo[state] = stateInfo;
    }

    if ((stateInfo->m_pParentStateInfo != nullptr) &&
            (stateInfo->m_pParentStateInfo != parentStateInfo)) {
        ALOGE("error : state already added !!!!!! \n");
        return nullptr;
    }
    stateInfo->m_pState = state;
    stateInfo->m_pParentStateInfo = parentStateInfo;
    stateInfo->m_bActive = FALSE;

    return stateInfo;
}

VOID StateMachine::StateMachineHandler::SetInitialState(shared_ptr<State> initialState)
{
    m_pInitialState = initialState;
}

VOID StateMachine::StateMachineHandler::TransitionTo(shared_ptr<State> destState)
{
    m_pDestState = destState;
}

VOID StateMachine::StateMachineHandler::CompleteConstruction()
{
    /**
     * Determine the maximum depth of the state hierarchy
     * so we can allocate the state stacks.
     */
    Int32 maxDepth = 0;
    for (auto it = m_mapStateInfo.begin(); it != m_mapStateInfo.end(); ++it) {
        shared_ptr<StateInfo> si = it->second;
        Int32 depth = 0;
        for (shared_ptr<StateInfo> i = si; i != nullptr; depth++) {
            i = i->m_pParentStateInfo;
        }
        if (maxDepth < depth) {
            maxDepth = depth;
        }
    }

    //PAM_LOG_DEBUG("\n StateMachine::StateMachineHandler::TransitionTo : maxDepth = %d \n", maxDepth);

    m_vStateStack.reserve(maxDepth);
    m_vStateStack.resize(0);
    m_vTempStateStack.reserve(maxDepth);
    m_vTempStateStack.resize(0);

    SetupInitialStateStack();

    /** Sending SM_INIT_COMPLETE message to invoke enter methods asynchronously */
    m_pStateMachine->SendMessage(new MessageForQueue(0/*no used*/, eMessageType_SM_INIT_COMPLETE/*no used*/, "SM_INIT_COMPLETE"));
}

VOID StateMachine::StateMachineHandler::SetupInitialStateStack()
{
    shared_ptr<StateInfo> curStateInfo;
    auto it = m_mapStateInfo.find(m_pInitialState);
    if (it != m_mapStateInfo.end()) {
        curStateInfo = it->second;
    }

    m_iTempStateStackCount = 0;
    m_vTempStateStack.resize(m_iTempStateStackCount);
    for(; curStateInfo != nullptr; m_iTempStateStackCount++) {
        m_vTempStateStack.push_back(curStateInfo);
        curStateInfo = curStateInfo->m_pParentStateInfo;
        //cout << "setupInitialStateStack: E m_vTempStateStack.size() = " << m_vTempStateStack.size() << " m_vTempStateStack.capacity() = "<< m_vTempStateStack.capacity() << endl;
    }

    // Empty the StateStack
    m_iStateStackTopIndex = -1;

    MoveTempStateStackToStateStack();
}

Int32 StateMachine::StateMachineHandler::MoveTempStateStackToStateStack()
{
    Int32 startingIndex = m_iStateStackTopIndex + 1;
    Int32 i = m_iTempStateStackCount - 1;
    Int32 j = startingIndex;

    m_vStateStack.resize(j);

    while (i >= 0) {
        //cout << "moveTempStackToStateStack: i=" << i << ",j=" << j << endl;
        m_vStateStack.push_back(m_vTempStateStack.at(i));
        j += 1;
        i -= 1;
    }

    m_iStateStackTopIndex = j - 1;
    //cout << "moveTempStackToStateStack: X mStateStackTop=" << m_iStateStackTopIndex << ",startingIndex=" << startingIndex << ",Top=" << m_vStateStack[m_iStateStackTopIndex]->m_pState->GetStateName() << endl;

    return startingIndex;
}

Int32 StateMachine::StateMachineHandler::StateToInt(shared_ptr<StateInfo> commonStateInfo)
{
    //cout << "===in fun : StateToInt" << endl;
    return m_pStateMachine->m_mapStateMapInt[commonStateInfo->m_pState->GetStateName()];
}

VOID StateMachine::StateMachineHandler::InvokeEnterMethods(const Int32 stateStackEnteringIndex)
{
    for (Int32 i = stateStackEnteringIndex; i <= m_iStateStackTopIndex; i++) {
        //cout << "invokeEnterMethods:  " << m_vStateStack[i]->m_pState->GetStateName() << endl;
        m_vStateStack[i]->m_pState->Enter();
        m_vStateStack[i]->m_bActive = TRUE;
    }

    shared_ptr<StateInfo> curStateInfo = m_vStateStack.at(m_iStateStackTopIndex);
    if(m_pStateMachine->m_pOwner != nullptr){
        ALOGI("Subject : %s begin to call Notify !!!!!! \n", m_pStateMachine->m_pOwner->GetSubjectName().c_str());
        m_pStateMachine->m_pOwner->Notify(StateToInt(curStateInfo));
    } else {
        ALOGW("m_pStateMachine->m_pOwner = nullptr !!!!!! \n");
    }
}

shared_ptr<StateMachine::StateMachineHandler::StateInfo> StateMachine::StateMachineHandler::SetupTempStateStackWithStatesToEnter(shared_ptr<State> destState)
{
    m_iTempStateStackCount = 0;
    shared_ptr<StateInfo> curStateInfo = m_mapStateInfo[destState];

    m_vTempStateStack.resize(m_iTempStateStackCount);
    do {
        m_vTempStateStack.push_back(curStateInfo);
        m_iTempStateStackCount++;
        curStateInfo = curStateInfo->m_pParentStateInfo;
    } while ((curStateInfo != nullptr) && !curStateInfo->m_bActive);

    return curStateInfo;
}

VOID StateMachine::StateMachineHandler::InvokeExitMethods(shared_ptr<StateInfo> commonStateInfo)
{
    while ((m_iStateStackTopIndex >= 0) && (m_vStateStack[m_iStateStackTopIndex] != commonStateInfo)) {
        shared_ptr<State> curState = m_vStateStack[m_iStateStackTopIndex]->m_pState;
        curState->Exit();
        m_vStateStack[m_iStateStackTopIndex]->m_bActive = FALSE;
        m_iStateStackTopIndex -= 1;
    }
}

VOID StateMachine::StateMachineHandler::PerformTransitions()
{
    shared_ptr<State> destState;
    while (m_pDestState != nullptr) {
        /**
         * Save m_pDestState locally and set to null
         * to know if enter/exit use transitionTo.
         */
        destState = m_pDestState;
        m_pDestState = nullptr;
        /**
         * Determine the states to exit and enter and return the
         * common ancestor state of the enter/exit states. Then
         * invoke the exit methods then the enter methods.
         */
        shared_ptr<StateInfo> commonStateInfo = SetupTempStateStackWithStatesToEnter(destState);
        InvokeExitMethods(commonStateInfo);
        Int32 stateStackEnteringIndex = MoveTempStateStackToStateStack();
        InvokeEnterMethods(stateStackEnteringIndex);

//        /**
//         * Since we have transitioned to a new state we need to have
//         * any deferred messages moved to the front of the message queue
//         * so they will be processed before any other messages in the
//         * message queue.
//         */
//        MoveDeferredMessageAtFrontOfQueue();
    }
//    /**
//     * After processing all transitions check and
//     * see if the last transition was to quit or halt.
//     */
//    if (destState != null) {
//        if (destState == mQuittingState) {
//            /**
//             * Call onQuitting to let subclasses cleanup.
//             */
//            mSm.onQuitting();
//            cleanupAfterQuitting();
//        } else if (destState == mHaltingState) {
//            /**
//             * Call onHalting() if we've transitioned to the halting
//             * state. All subsequent messages will be processed in
//             * in the halting state which invokes haltedProcessMessage(msg);
//             */
//            mSm.onHalting();
//        }
//    }
}

VOID StateMachine::StateMachineHandler::ProcessMsg(UInt32 uiType, UInt32 uiID, const string& pData)
{
    shared_ptr<StateInfo> curStateInfo = m_vStateStack.at(m_iStateStackTopIndex);

    /*if (isQuit(msg)) {
        transitionTo(mQuittingState);
    } else*/ {
        while (!curStateInfo->m_pState->ProcessMessage(uiType, uiID, pData)) {
            /**
             * Not processed
             */
            curStateInfo = curStateInfo->m_pParentStateInfo;
            if (curStateInfo == nullptr) {
                /**
                 * No parents left so it's not handled
                 */
                //mSm.unhandledMessage(msg);
                ALOGE("no body deal whith massage !!!!!! \n");
                break;
            }
        }
    }
}

StateMachine::StateMachine(const string& name)
    : m_strStateMachineName(name)
{
    m_pStateMachineHandler = make_shared<StateMachineHandler>(this);
}

StateMachine::~StateMachine()
{
}

VOID StateMachine::Start() const
{
    if (m_pStateMachineHandler == nullptr) return;
    m_pStateMachineHandler->CompleteConstruction();
}

VOID StateMachine::AddState(shared_ptr<State> state) const
{
    shared_ptr<StateMachineHandler::StateInfo> sinfo = m_pStateMachineHandler->AddState(state, nullptr);
}

VOID StateMachine::AddState(shared_ptr<State> state, shared_ptr<State> parent) const
{
    shared_ptr<StateMachineHandler::StateInfo> sinfo = m_pStateMachineHandler->AddState(state, parent);
}

VOID StateMachine::SetInitialState(shared_ptr<State> initialState) const
{
    m_pStateMachineHandler->SetInitialState(initialState);
}

shared_ptr<State> StateMachine::GetCurrentState() const
{
    return m_pStateMachineHandler->GetCurrentState();
}

Int32 StateMachine::CurrentStateToInt()
{
    return m_mapStateMapInt[GetCurrentState()->GetStateName()];
}

VOID StateMachine::TransitionTo(shared_ptr<State> destState) const
{
    //asynchronization change state,  the real state change is : deal with vector<shared_ptr<StateInfo>> m_vStateStack in the next moment;
    m_pStateMachineHandler->TransitionTo(destState);
}

VOID StateMachine::SendMessage(MessageForQueue* msg) const
{
    if (nullptr == m_pStateMachineHandler)  {
        ALOGE("m_pStateMachineHandler is null, can not SendMessage !!!!!! \n");
        return;
    }

    //the only way to send message to statemachine.  for debugging easily.
    ALOGI("msg->m_uiMeaasgeID = %d, msg->m_strArgs = %s \n", msg->m_uiMeaasgeID, (msg->m_strArgs).c_str());
    m_pStateMachineHandler->m_pStateMachineLooper->pushMessage(msg);
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman