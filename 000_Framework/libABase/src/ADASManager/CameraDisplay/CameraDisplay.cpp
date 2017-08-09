#include "CameraDisplay.h"
#include <platform.h>
#include <EGL/eglext.h>
#include <weston-egl-ext.h>

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
       overlayWindow::getInstance()->draw();
       m_pPaint->draw();
    }

    eglSwapBuffers(eglDisplay, eglSurface);
}

VOID CameraDisplay::stop()
{

}

VOID CameraDisplay::connect()
{
    printf("xiaole---debug CameraDisplay| connect\n");
    if(m_pPaint == NULL) {
        m_pPaint = new PaintImpl();
    }

    m_pPaint->init();
    printf("xiaole---debug overlayWindow init start\n");
    overlayWindow::getInstance()->init();
    printf("xiaole---debug createEGLContext start\n");
    createEGLContext();
    printf("xiaole---debug connect OK\n");
}


BOOLEAN CameraDisplay::createEGLContext ()
{
   EGLint numConfigs;
   EGLint majorVersion;
   EGLint minorVersion;
   EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

  // EGLint attribList[] =
  //  {
  //      EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
  //       EGL_BUFFER_SIZE, 24,
  //       EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
  //       EGL_NONE
  //  };

     EGLint attribList[] =
   {
      EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
      EGL_RED_SIZE, 1,
      EGL_GREEN_SIZE, 1,
      EGL_BLUE_SIZE, 1,
      EGL_ALPHA_SIZE, 1,
      EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
      EGL_NONE
   };



   static const struct {
    char *extension, *entrypoint;
  } swap_damage_ext_to_entrypoint[] = {
    {
      .extension = "EGL_EXT_swap_buffers_with_damage",
      .entrypoint = "eglSwapBuffersWithDamageEXT",
    },
    {
      .extension = "EGL_KHR_swap_buffers_with_damage",
      .entrypoint = "eglSwapBuffersWithDamageKHR",
    },
  };



   // Get Display
   printf("xiaole---debug eglGetDisplay\n");
   eglDisplay = eglGetDisplay((EGLNativeDisplayType)xdisplay);

   if ( eglDisplay == EGL_NO_DISPLAY )
   {
      printf("xiaole---debug eglGetDisplay failed\n");
      return FALSE;
   }

   // Initialize EGL
   if ( !eglInitialize(eglDisplay, &majorVersion, &minorVersion) )
   {
      printf("xiaole---debug eglInitialize failed\n");
      return FALSE;
   }

   eglBindAPI(EGL_OPENGL_ES_API);

   // Get configs
   if ( !eglGetConfigs(eglDisplay, NULL, 0, &numConfigs) )
   {
     printf("xiaole---debug eglGetConfigs failed\n");
     return FALSE;
   }

   // Choose config
   if ( !eglChooseConfig(eglDisplay, attribList, &eglConfig, 1, &numConfigs) )
   {
      printf("xiaole---debug eglChooseConfig failed\n");
      return FALSE;
   }

   // Create a GL context
   eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs );
   if ( eglContext == EGL_NO_CONTEXT )
   {
      printf("xiaole---debug eglCreateContext failed\n");
      return FALSE;
   }


  // display->swap_buffers_with_damage = NULL;
  // extensions = eglQueryString(display->egl.dpy, EGL_EXTENSIONS);
  // if (extensions &&
  //     weston_check_egl_extension(extensions, "EGL_EXT_buffer_age")) {
  //   for (i = 0; i < (int) ARRAY_LENGTH(swap_damage_ext_to_entrypoint); i++) {
  //     if (weston_check_egl_extension(extensions,
  //                  swap_damage_ext_to_entrypoint[i].extension)) {
  //       /* The EXTPROC is identical to the KHR one */
  //       display->swap_buffers_with_damage =
  //         (PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC)
  //         eglGetProcAddress(swap_damage_ext_to_entrypoint[i].entrypoint);
  //       break;
  //     }
  //   }
  // }

  // if (display->swap_buffers_with_damage)
  //   printf("has EGL_EXT_buffer_age and %s\n", swap_damage_ext_to_entrypoint[i].extension);

   overlayWindow::getInstance()->createSurface(m_window);
   printf("xiaole---debug WLSurface OK\n");
   eglSurface = weston_platform_create_egl_surface(eglDisplay, eglConfig,
                                                                        (VOID*)m_window.window,
                                                                        NULL);
   overlayWindow::getInstance()->create_xdg_surface();
   printf("xiaole---debug eglCreateWindowSurface OK\n");
   // Make the context current
   if ( !eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext) )
   {
      printf("xiaole---debug eglCreateContext failed\n");
      return FALSE;
   }

   return TRUE;
}

