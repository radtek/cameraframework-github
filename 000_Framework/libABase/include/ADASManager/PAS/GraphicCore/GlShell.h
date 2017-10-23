
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GLSHELL_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GLSHELL_H__

#include "ADASManager/PAS/GraphicCore/HeadDefine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <assert.h>

//#undef LM_SUPPORT

#include <wayland-client.h>
#include <wayland-egl.h>
#include <wayland-cursor.h>

#ifdef LM_SUPPORT
#include "ilm/ilm_control.h"
#include "ilm/ilm_client.h"
#endif

struct window;
struct seat;

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
    // struct wl_cursor_theme *cursor_theme;
    // struct wl_cursor *default_cursor;
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

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class GlShell
{
public:
    GlShell();
    ~GlShell();

    bool InitView(int screenWidth, int screenHeight, const char *carBuffer2, int textWidth, int texHeight);
    bool ReadShellConfig(const char* cfgfilepath);
    void InitEnV(int screenWidth, int screenHeight);
    void LoadShaders();
	void GenCarTexture(const char *buffer, int textWidth, int texHeight);
	void GenWarningTexture(int textWidth, int texHeight);

protected:
    GLuint m_uiTexture;
	GLuint m_uiCarTexture;
	GLuint m_uiWarningTexture;
    struct{
        GLuint uiId;
        GLuint uiColor;
        GLuint uiImgSize;
        GLuint uiCarSize;

		// Sampler locations
		GLint uiTxtLoc;
		GLint uiCarLoc;
		GLint uiWarningLoc;

        GLuint uiSourcePosition;
    }m_RenderObj;

    EGLDisplay* dpy_shell;
    EGLSurface* egl_surface_shell;
    struct window* window_shell;

};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GLSHELL_H__