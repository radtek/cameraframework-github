
#include "ADASManager/Camera/Display/DisplaySample.h"
#include "ADASManager/Camera/Display/CameraDisplayTypeDefine.h"
#include "TraceMacros.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

int DisplaySample::running = 1;

struct wl_registry_listener DisplaySample::registry_listener = {
    registry_handle_global,
    registry_handle_global_remove
};

struct display DisplaySample::m_Display = { 0 };
struct window  DisplaySample::m_Window  = { 0 };

DisplaySample::DisplaySample()
{
    m_Window.display = &m_Display;
    m_Display.window = &m_Window;
    m_Window.geometry.width  = screenWidth;
    m_Window.geometry.height = screenHight;
    //  m_Window.geometry.width  = 250;
    // m_Window.geometry.height = 250;
    m_Window.window_size = m_Window.geometry;
    m_Window.buffer_size = 32;
    m_Window.frame_sync = 1;
    m_Window.delay = 0;

    m_Display.display = wl_display_connect(NULL);
    assert(m_Display.display);

    m_Display.registry = wl_display_get_registry(m_Display.display);
    wl_registry_add_listener(m_Display.registry,
                 &registry_listener, &m_Display);

    wl_display_roundtrip(m_Display.display);
}

DisplaySample::~DisplaySample()
{
    ALOGD("rvc exiting\n");

    destroy_surface(&m_Window);
    fini_egl(&m_Display);

    if (m_Display.ivi_application) {
        ivi_application_destroy(m_Display.ivi_application);
    }

    if (m_Display.compositor) {
        wl_compositor_destroy(m_Display.compositor);
    }

    wl_registry_destroy(m_Display.registry);
    wl_display_flush(m_Display.display);
    wl_display_disconnect(m_Display.display);
    ALOGD("DisplaySample exiting OK\n");
}

void DisplaySample::Init()
{
    init_egl(&m_Display, &m_Window);
    create_surface(&m_Window);
}

int DisplaySample::Start()
{
    /* The mainloop here is a little subtle.  Redrawing will cause
     * EGL to read events so we can just call
     * wl_display_dispatch_pending() to handle any events that got
     * queued up as a side effect. */
    //while (running /*&& ret != -1*/) {
    if (m_Window.wait_for_configure) {
        wl_display_dispatch(m_Display.display);
    } else {
        wl_display_dispatch_pending(m_Display.display);
        redraw(&m_Window, NULL, 0);
    }
    //}
}

void DisplaySample::init_egl(struct display *display, struct window *window)
{
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

    static const EGLint context_attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    const char *extensions;

    EGLint config_attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 1,
        EGL_GREEN_SIZE, 1,
        EGL_BLUE_SIZE, 1,
        EGL_ALPHA_SIZE, 1,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    EGLint major, minor, n, count, i, size;
    EGLConfig *configs;
    EGLBoolean ret;

    if (window->opaque || window->buffer_size == 16)
        config_attribs[9] = 0;

    display->egl.dpy =
        weston_platform_get_egl_display(EGL_PLATFORM_WAYLAND_KHR,
                        display->display, NULL);
    assert(display->egl.dpy);

    ret = eglInitialize(display->egl.dpy, &major, &minor);
    assert(ret == EGL_TRUE);
    ret = eglBindAPI(EGL_OPENGL_ES_API);
    assert(ret == EGL_TRUE);

    if (!eglGetConfigs(display->egl.dpy, NULL, 0, &count) || count < 1)
        assert(0);

    configs = (EGLConfig *)calloc(count, sizeof *configs);
    assert(configs);

    ret = eglChooseConfig(display->egl.dpy, config_attribs,
                  configs, count, &n);
    assert(ret && n >= 1);

    for (i = 0; i < n; i++) {
        eglGetConfigAttrib(display->egl.dpy,
                   configs[i], EGL_BUFFER_SIZE, &size);
        if (window->buffer_size == size) {
            display->egl.conf = configs[i];
            break;
        }
    }
    free(configs);
    if (display->egl.conf == NULL) {
        ALOGE("did not find config with buffer size %d\n",
            window->buffer_size);
        exit(EXIT_FAILURE);
    }

    display->egl.ctx = eglCreateContext(display->egl.dpy,
                        display->egl.conf,
                        EGL_NO_CONTEXT, context_attribs);
    assert(display->egl.ctx);

    display->swap_buffers_with_damage = NULL;
    extensions = eglQueryString(display->egl.dpy, EGL_EXTENSIONS);
    if (extensions &&
        weston_check_egl_extension(extensions, "EGL_EXT_buffer_age")) {
        for (i = 0; i < (int) ARRAY_LENGTH(swap_damage_ext_to_entrypoint); i++) {
            if (weston_check_egl_extension(extensions,
                               swap_damage_ext_to_entrypoint[i].extension)) {
                /* The EXTPROC is identical to the KHR one */
                display->swap_buffers_with_damage =
                    (PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC)
                    eglGetProcAddress(swap_damage_ext_to_entrypoint[i].entrypoint);
                break;
            }
        }
    }

    if (display->swap_buffers_with_damage)
        ALOGD("has EGL_EXT_buffer_age and %s\n", swap_damage_ext_to_entrypoint[i].extension);
}

void DisplaySample::fini_egl(struct display *display)
{
    eglTerminate(display->egl.dpy);
    eglReleaseThread();
}


void DisplaySample::create_ivi_surface(struct window *window, struct display *display)
{
    window->ivi_surface =
        ivi_application_surface_create(display->ivi_application,
                           RVC_SURFACE_ID, window->surface);

    if (window->ivi_surface == NULL) {
        ALOGE("Failed to create ivi_client_surface\n");
        abort();
    }
}

void DisplaySample::create_surface(struct window *window)
{
    struct display *display = window->display;
    EGLBoolean ret;

    window->surface = wl_compositor_create_surface(display->compositor);

    window->native =
        wl_egl_window_create(window->surface,
                     window->geometry.width,
                     window->geometry.height);

    window->egl_surface =
        weston_platform_create_egl_surface(display->egl.dpy,
                           display->egl.conf,
                           window->native, NULL);

    create_ivi_surface(window, display);

    ret = eglMakeCurrent(window->display->egl.dpy, window->egl_surface,
                 window->egl_surface, window->display->egl.ctx);
    assert(ret == EGL_TRUE);

    if (!window->frame_sync)
        eglSwapInterval(display->egl.dpy, 0);


    wl_egl_window_resize(window->native,
                     window->geometry.width,
                     window->geometry.height, 0, 0);
}

void DisplaySample::destroy_surface(struct window *window)
{
    /* Required, otherwise segfault in egl_dri2.c: dri2_make_current()
     * on eglReleaseThread(). */
    eglMakeCurrent(window->display->egl.dpy, EGL_NO_SURFACE, EGL_NO_SURFACE,
               EGL_NO_CONTEXT);

    weston_platform_destroy_egl_surface(window->display->egl.dpy,
                        window->egl_surface);
    wl_egl_window_destroy(window->native);


    if (window->display->ivi_application)
        ivi_surface_destroy(window->ivi_surface);
    wl_surface_destroy(window->surface);

    if (window->callback)
        wl_callback_destroy(window->callback);
}

void DisplaySample::redraw(void *data, struct wl_callback *callback, uint32_t time)
{
    struct window *window = (struct window*)data;
    struct display *display = window->display;


    eglSwapBuffers(display->egl.dpy, window->egl_surface);
}

void DisplaySample::registry_handle_global(void *data, struct wl_registry *registry,
               uint32_t name, const char *interface, uint32_t version)
{
    struct display *d = (struct display *)data;

    if (strcmp(interface, "wl_compositor") == 0) {
        d->compositor =
            (wl_compositor*)wl_registry_bind(registry, name,
                     &wl_compositor_interface,
                     MIN(version, 4));
    }
    else if (strcmp(interface, "ivi_application") == 0) {
        d->ivi_application =
            (ivi_application*)wl_registry_bind(registry, name,
                     &ivi_application_interface, 1);
    }
}

void DisplaySample::registry_handle_global_remove(void *data, struct wl_registry *registry,
                  uint32_t name)
{
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman