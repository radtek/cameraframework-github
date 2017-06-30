/*
 * OGLES2Interface.h
 *
 *  Created on: 2012-4-27
 *      Author: QiLiu
 */

#ifndef OGLES2INTERFACE_H_
#define OGLES2INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "RVSDefine.h"

int OGLES2Init(void* eglDisplay);
void OGLES2Draw();//Calculate&Render Overlays & Draw Text

#ifdef __cplusplus
}
#endif

#endif /* OGLES2INTERFACE_H_ */
