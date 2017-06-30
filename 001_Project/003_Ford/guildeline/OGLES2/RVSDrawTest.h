#ifndef RVSDRAWTEST_H_
#define RVSDRAWTEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "RVSDefine.h"

int OGLES2Init(void* eglDisplay,rvs_ctx_t* ctx);
void OGLES2Draw(rvs_ctx_t* ctx);//Calculate&Render Overlays & Draw Text
void OGLES2TouchEvent(int x, int y,int eventType);



#ifdef __cplusplus
}
#endif

#endif /* OGLES2INTERFACE_H_ */