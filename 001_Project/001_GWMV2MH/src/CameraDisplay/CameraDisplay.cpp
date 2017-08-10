#include "CameraDisplay.h"

struct wl_display *xdisplay;

CameraDisplay::CameraDisplay(viewInfo& info)
    :m_pPaint(NULL)
{
    memset(&m_window, 0, sizeof(overlayWindow::windowInfo));
    m_window.view = &info;
}

CameraDisplay::~CameraDisplay()
{
     if(m_pPaint != NULL) {
        delete m_pPaint;
        m_pPaint = NULL;
    }
}

VOID CameraDisplay::update(cameraDisplayInfo* info)
{
    if(info != NULL && m_pPaint != NULL) {
       m_pPaint->update(info->frameWidth, info->frameHeight, info->databuffer);
    }
}

VOID CameraDisplay::start()
{
    if(m_pPaint != NULL) {
       m_pPaint->draw();
    }

    eglSwapBuffers(eglDisplay, eglSurface);
}

VOID CameraDisplay::stop()
{

}

VOID CameraDisplay::connect()
{
    if(m_pPaint == NULL) {
        m_pPaint = new PaintImpl();
    }

    m_pPaint->init();
    overlayWindow::getInstance()->init();
    createEGLContext();
}


BOOLEAN CameraDisplay::createEGLContext ()
{
   EGLint numConfigs;
   EGLint majorVersion;
   EGLint minorVersion;
   EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

  EGLint attribList[] =
   {
       EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BUFFER_SIZE, 24,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
   };

   // Get Display
   eglDisplay = eglGetDisplay((EGLNativeDisplayType)xdisplay);

   if ( eglDisplay == EGL_NO_DISPLAY )
   {
      return FALSE;
   }

   // Initialize EGL
   if ( !eglInitialize(eglDisplay, &majorVersion, &minorVersion) )
   {
      return FALSE;
   }

   eglBindAPI(EGL_OPENGL_ES_API);

   // Get configs
   if ( !eglGetConfigs(eglDisplay, NULL, 0, &numConfigs) )
   {
      return FALSE;
   }

   // Choose config
   if ( !eglChooseConfig(eglDisplay, attribList, &eglConfig, 1, &numConfigs) )
   {
      return FALSE;
   }

   // Create a GL context
   eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs );
   if ( eglContext == EGL_NO_CONTEXT )
   {
      return FALSE;
   }   

   overlayWindow::getInstance()->createSurface(m_window);

   eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig,
                                                                        (EGLNativeWindowType)m_window.window, 
                                                                        NULL);

   // Make the context current
   if ( !eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext) )
   {
      return FALSE;
   }
   
   return TRUE;
}

