#ifndef  SURFACEIMP_H
#define SURFACEIMP_H
#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include "TypeDefine.h"
#include "wayland-client.h"
#include "wayland-egl.h"
#include "wayland-cursor.h"
#include <xdg-shell-unstable-v6-client-protocol.h>
#include <ivi-application-client-protocol.h>

class overlayWindow
{
public:
    typedef struct
    {
        struct wl_egl_window *window;
        viewInfo*  view;
        struct zxdg_surface_v6 *xdg_surface;
        struct zxdg_toplevel_v6 *xdg_toplevel;
        struct ivi_surface *ivi_surface;
        int fullscreen, opaque, buffer_size, frame_sync, delay;
        bool wait_for_configure;
    } windowInfo;

    typedef struct
    {
        struct wl_display *display;
        struct wl_registry *registry;
        struct wl_compositor *compositor;
        struct wl_egl_window *native;
        struct wl_surface *surface;
        struct wl_seat *seat;
        struct wl_pointer *pointer;
        struct wl_touch *touch;
        struct wl_keyboard *keyboard;
        struct wl_shm *shm;
        struct wl_cursor_theme *cursor_theme;
        struct wl_cursor *default_cursor;
        struct wl_surface *cursor_surface;
        struct zxdg_shell_v6 *shell;
        struct ivi_application *ivi_application;
        windowInfo* window;
    } wlInfo;

public:
   static overlayWindow* getInstance();
   static void deInstance();
   virtual ~overlayWindow();

    VOID init();
    VOID createSurface(windowInfo& info);
    VOID distroySurface(windowInfo& info);
    VOID create_xdg_surface();
    VOID draw();

private:
    overlayWindow();

    static overlayWindow* m_pInstance;
    wlInfo m_wlInfoData;


private:
};

#endif  //  SURFACEIMP_H
/* EOF */
