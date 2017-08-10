#ifndef ADAS_CAMERA_DISPLAY_H
#define ADAS_CAMERA_DISPLAY_H
#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include "PaintImpl.h"
#include "CameraDisplayTypeDefine.h"
#include "overlayWindow.h"

#define ESCALLBACK

class CameraDisplay
{
public:
    typedef struct
    {
        VOID* databuffer;

        Int32 frameWidth;

        Int32 frameHeight;

    }cameraDisplayInfo;


    CameraDisplay(viewInfo& info);
    ~CameraDisplay();

public:
    /**
        call connect for cameradisplay depedency initialize first
    **/
    VOID connect();

    /**
        update camera frame info in your thread loop
        struct cameraDisplayInfo please refer to CameraDisplayTypeDefine.h
     **/
    VOID update(cameraDisplayInfo *info);

    /**
        call start  after updating your camerainfo in your thread loop  
        start  to draw frame when you capture completed
    **/
    VOID start();

    /**
        stop to display camera view when you suspend or exit
    **/
    VOID stop();

private:
    BOOLEAN createEGLContext ();

private:
    EGLNativeWindowType  hWnd;
    /// EGL cameraDisplay
    EGLDisplay  eglDisplay;   
    // EGL context
    EGLContext  eglContext;
    /// EGL surface
    EGLSurface  eglSurface;

    EGLConfig    eglConfig;

private:
    PaintImpl* m_pPaint;
    overlayWindow::windowInfo m_window;
};


#endif