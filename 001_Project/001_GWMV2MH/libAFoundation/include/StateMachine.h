
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_STATEMACHINE_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_STATEMACHINE_H__

#include <memory>
#include <vector>
#include <map>

#include "platformdef.h"
#include "TraceMacros.h"
#include "State.h"
#include "Subject.h"
#include "CMessageHandler.h"
#include "CMQRunnableService.h"
#include "MessageForQueue.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

class StateMachine
{
private:
    /*
     * class StateMachineHandler : send and dispatch massage
     */
    class StateMachineHandler : public CMessageHandler
    {
        friend class StateMachine;
    private:
        /*
         * class StateMachineLooper is a Thread, and  contains a MassageQueue
         */
        class StateMachineLooper : public CMQRunnableService
        {
        public:
            StateMachineLooper(const string& name, CMessageQueue* msg)
                : CMQRunnableService(name + "_MQRunnableService", msg)
            {
                //start Thread
                start();
            }

            ~StateMachineLooper()
            {
                //quit Thread
                quit();
            }

            virtual BOOLEAN initialize(string sServiceName){};
        };

        /**
         * Information about a state.
         * Used to maintain the hierarchy.
         */
        class StateInfo
        {
        public:
            StateInfo()
                : m_bActive(FALSE)
            {}

        public:
            /** The state */
            shared_ptr<State> m_pState;
            /** The parent of this state, null if there is no parent */
            shared_ptr<StateInfo> m_pParentStateInfo;
            /** True when the state has been entered and on the stack */
            BOOLEAN m_bActive;
        };

    public:
        StateMachineHandler(StateMachine* sm)
            : m_pStateMachine(sm)
        {
            m_pMessageQueue = new CMessageQueue(m_pStateMachine->m_strStateMachineName + "_MessageQueue", 300, this);
            m_pStateMachineLooper = make_shared<StateMachineLooper>(m_pStateMachine->m_strStateMachineName, m_pMessageQueue);
        }

        Int32 StateToInt(shared_ptr<StateInfo> commonStateInfo);

    protected:
        VOID _handle(UInt32 uiType, UInt32 uiID, const string& pData);

    private:
        /** @see StateMachine#GetCurrentState() */
        shared_ptr<State> GetCurrentState();// const;

        /** @see StateMachine#AddState(shared_ptr<State> , shared_ptr<State>) */
        shared_ptr<StateInfo> AddState(shared_ptr<State> state, shared_ptr<State> parent);

        /** @see StateMachine#SetInitialState(shared_ptr<State>) */
        VOID SetInitialState(shared_ptr<State> initialState);

        /** @see StateMachine#TransitionTo(shared_ptr<State>) */
        VOID TransitionTo(shared_ptr<State> destState);

        /**
         * Complete the construction of the state machine.
         */
        VOID CompleteConstruction();

        /**
         * Initialize StateStack to mInitialState.
         */
        VOID SetupInitialStateStack();

        /**
         * Move the contents of the temporary stack to the state stack
         * reversing the order of the items on the temporary stack as
         * they are moved.
         *
         * @return index into mStateStack where entering needs to start
         */
        Int32 MoveTempStateStackToStateStack();

        /**
         * Invoke the enter method starting at the entering index to top of state stack
         */
        VOID InvokeEnterMethods(const Int32 stateStackEnteringIndex, BOOLEAN isNotFirst);

        /**
         * Do any transitions
         */
        VOID PerformTransitions();

        /**
         * Setup the mTempStateStack with the states we are going to enter.
         *
         * This is found by searching up the destState's ancestors for a
         * state that is already active i.e. StateInfo.active == true.
         * The destStae and all of its inactive parents will be on the
         * TempStateStack as the list of states to enter.
         *
         * @return StateInfo of the common ancestor for the destState and
         * current state or null if there is no common parent.
         */
        shared_ptr<StateInfo> SetupTempStateStackWithStatesToEnter(shared_ptr<State> destState);

        /**
         * Call the exit method for each state from the top of stack
         * up to the common ancestor state.
         */
        VOID InvokeExitMethods(shared_ptr<StateInfo> commonStateInfo);

        /**
         * Process the message. If the current state doesn't handle
         * it, call the states parent and so on. If it is never handled then
         * call the state machines unhandledMessage method.
         */
        VOID ProcessMsg(UInt32 uiType, UInt32 uiID, const string& pData);

    private:
        enum {
            eMessageType_SM_INIT_COMPLETE = 0x0,
        };

        /** Top of mStateStack */
        Int32 m_iStateStackTopIndex = -1;

        /** Stack used to manage the current hierarchy of states */
        vector<shared_ptr<StateInfo>> m_vStateStack;

        /** The top of the mTempStateStack */
        Int32 m_iTempStateStackCount = 0;

        /** A temporary stack used to manage the state stack */
        vector<shared_ptr<StateInfo>> m_vTempStateStack;

        /** The map of all of the states in the state machine */
        map<shared_ptr<State>, shared_ptr<StateInfo>> m_mapStateInfo;

        /** The initial state that will process the first message */
        shared_ptr<State> m_pInitialState;

        /** The destination state when transitionTo has been invoked */
        shared_ptr<State> m_pDestState;

        StateMachine* m_pStateMachine = nullptr;

        /** true if construction of the state machine has not been completed */
        BOOLEAN m_bIsConstructionCompleted = FALSE;

        shared_ptr<StateMachineLooper> m_pStateMachineLooper;

        CMessageQueue* m_pMessageQueue = nullptr;
    };

public:
    virtual ~StateMachine();

    /**
     * Start the state machine.
     */
    VOID Start() const;

    /**
     * Add a new state to the state machine, parent will be null
     * @param state to add
     */
    VOID AddState(shared_ptr<State> state) const;

    /**
     * Add a new state to the state machine. Bottom up addition
     * of states is allowed but the same state may only exist
     * in one hierarchy.
     *
     * @param state the state to add
     * @param parent the parent of state
     * @return stateInfo for this state
     */
    VOID AddState(shared_ptr<State> state, shared_ptr<State> parent) const;

    /**
     * Set the initial state. This must be invoked before
     * and messages are sent to the state machine.
     *
     * @param initialState is the state which will receive the first message.
     */
    VOID SetInitialState(shared_ptr<State> initialState) const;

    /**
     * @return current state
     */
    shared_ptr<State> GetCurrentState() const;

    /**
     * transition to destination state. Upon returning
     * from processMessage the current state's exit will
     * be executed and upon the next message arriving
     * destState.enter will be invoked.
     *
     * this function can also be called inside the enter function of the
     * previous transition target, but the behavior is undefined when it is
     * called mid-way through a previous transition (for example, calling this
     * in the enter() routine of a intermediate node when the current transition
     * target is one of the nodes descendants).
     *
     * @param destState will be the state that receives the next message.
     */
    VOID TransitionTo(shared_ptr<State> destState) const;

    /**
     * Enqueue a message to this state machine.
     */
    VOID SendMessage(MessageForQueue* msg) const;


    Int32 CurrentStateToInt();

    VOID SetOwner(Subject* owner) { m_pOwner = owner; }

protected:
    /**
     * Constructor creates a StateMachine.
     *
     * @param name of the state machine
     */
    StateMachine(const string& name);

private:
    VOID Init();

protected:
    map<string, Int32> m_mapStateMapInt;

private:
    /**
     * name of the state StateMachine
     */
    const string m_strStateMachineName;

    shared_ptr<StateMachineHandler> m_pStateMachineHandler;

    Subject* m_pOwner = nullptr;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_STATEMACHINE_H__