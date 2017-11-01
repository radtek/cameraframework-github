
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_EVENT_DEFINE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_EVENT_DEFINE_H__

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

//name of AVM state
#define AVMDEFAULTSTATE	"AvmDefaultState"
#define AVMONSTATE		"AvmOnState"
#define AVMOFFSTATE		"AvmOffState"

/*
 * state
 */
typedef enum _AVM_State{
    e_AVM_State_ON	= 0x0,
    e_AVM_State_OFF	= 0x1,
    e_AVM_State_Invalid	= 0xFF
} Enum_AVMState;


/*
 * ERROR CODE
 */
static const ECode NO_ERROR                          = 0;
static const ECode E_IOCTL_VIDIOC_REQBUFS_EXCEPTION  = 1;

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_AVM_EVENT_DEFINE_H__