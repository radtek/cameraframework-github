
#if !defined(_GlShell_H_)
#define _GlShell_H_
#include "..\..\..\..\001_Project\libappcore\platformdef.h"
#include "HeadDefine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <assert.h>

struct window;
struct seat;

#ifdef LINUX_OS

#define  LM_SUPPORT 1 
#include <wayland-client.h>
#include <wayland-egl.h>
#include <wayland-cursor.h>

#ifdef LM_SUPPORT
#include "ilm/ilm_control.h"
#include "ilm/ilm_client.h"
#endif

struct display {
    struct wl_display *display;
    struct wl_registry *registry;
    struct wl_compositor *compositor;
#ifdef SHELL_SUPPORT
    struct xdg_shell *shell;
#endif 
    struct wl_seat *seat;
    struct wl_pointer *pointer;
    struct wl_touch *touch;
    struct wl_keyboard *keyboard;
    struct wl_shm *shm;
    struct wl_cursor_theme *cursor_theme;
    struct wl_cursor *default_cursor;
    struct wl_surface *cursor_surface;
    struct {
        EGLDisplay dpy;
        EGLContext ctx;
        EGLConfig conf;
    } egl;
    struct window *window;
#ifdef SHELL_SUPPORT
    struct ivi_application *ivi_application;
    PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC swap_buffers_with_damage;
#endif

    
};

struct geometry {
    int width, height;
};

struct window {
    struct display *display;
    struct geometry geometry, window_size;
    struct {
        GLuint rotation_uniform;
        GLuint pos;
        GLuint col;
    } gl;

    uint32_t benchmark_time, frames;
    struct wl_egl_window *native;
    struct wl_surface *surface;
#ifdef SHELL_SUPPORT
    struct xdg_surface *xdg_surface;
    struct ivi_surface *ivi_surface;
#endif
    EGLSurface egl_surface;
    struct wl_callback *callback;
    int fullscreen, opaque, buffer_size, frame_sync;
};
#endif

#ifdef WIN_OS

struct display {
    //struct wl_display *display;
    //struct wl_registry *registry;
   // struct wl_compositor *compositor;
   // struct wl_surface *cursor_surface;
    struct {
        EGLDisplay dpy;
        EGLContext ctx;
        EGLConfig conf;
    } egl;
    struct window *window;
#ifdef SHELL_SUPPORT
    struct ivi_application *ivi_application;
    PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC swap_buffers_with_damage;
#endif

    
};

struct geometry {
    int width, height;
};

struct window {
    struct display *display;
    struct geometry geometry, window_size;
    struct {
        GLuint rotation_uniform;
        GLuint pos;
        GLuint col;
    } gl;

    //uint32_t benchmark_time, frames;
    struct wl_egl_window *native;
    struct wl_surface *surface;

    EGLSurface egl_surface;
    //struct wl_callback *callback;
    int fullscreen, opaque, buffer_size, frame_sync;
};

#endif

class GlShell
{
public:
    GlShell();
    ~GlShell();
    
    bool InitView(int screenWidth, int screenHeight);
    bool ReadShellConfig(const char* cfgfilepath);
    void InitEnV(int screenWidth, int screenHeight);
    void LoadShaders();

protected:
    GLuint m_uiTexture;
    struct{
        GLuint uiId;
        GLuint uiColor;
        GLuint uiImgSize;
        GLuint uiSourcePosition;
    }m_RenderObj;

    EGLDisplay* dpy_shell;
    EGLSurface* egl_surface_shell;
    struct window* window_shell;
    
};

#endif
