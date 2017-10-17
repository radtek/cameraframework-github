
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PDCSTATE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PDCSTATE_H__

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class PDCState {
public:
    virtual void vShow() = 0;
    virtual void vHide() = 0;
    virtual void vError() = 0;
    virtual void vPause() = 0;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PDCSTATE_H__