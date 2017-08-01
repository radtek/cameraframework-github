
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_STATE_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_STATE_H__

#include <string>
#include <iostream>
#include <memory>

#include "TypeDefine.h"
#include "TraceMacros.h"
#include "MessageForQueue.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

class StateMachine;

class State
{
public:
    /**
     * Called when a state is entered.
     */
    virtual VOID Enter() const;

    /**
     * Called when a state is exited.
     */
    virtual VOID Exit() const;

    /**
     * Called when a message is to be processed by the
     * state machine.
     *
     * This routine is never reentered thus no synchronization
     * is needed as only one processMessage method will ever be
     * executing within a state machine at any given time. This
     * does mean that processing by this routine must be completed
     * as expeditiously as possible as no subsequent messages will
     * be processed until this routine returns.
     *
     * @param msg to process
     * @return true if processing has completed and false
     *         if the message wasn't processed.
     */
    virtual BOOLEAN ProcessMessage(UInt32 uiType, UInt32 uiID, const string& pData) const;

    /**
     * Name of State.
     *
     * @return name of state.
     */
    virtual const string& GetStateName() const final;

    virtual ~State() {};

protected:
    State(const string& name, StateMachine* sm)
       : m_strStateName(name)
       , m_pStateMachine(sm)
    {}

protected:
    const string m_strStateName;
    StateMachine* m_pStateMachine;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_STATE_H__