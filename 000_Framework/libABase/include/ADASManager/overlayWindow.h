#ifndef  SURFACEIMP_H
#define SURFACEIMP_H
#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include "TypeDefine.h"
#include "wayland-client.h"
#include "wayland-egl.h"
#include "wayland-cursor.h"

class overlayWindow
{
public:
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
    } wlInfo;

    typedef struct
    {
        struct wl_egl_window *window;
        viewInfo*  view;
    } windowInfo;

public:
   static overlayWindow* getInstance();
   static void deInstance();
   virtual ~overlayWindow();

    VOID init();
    VOID createSurface(windowInfo& info);
    VOID distroySurface(windowInfo& info);

    VOID draw();

private:
    overlayWindow();    

    static overlayWindow* m_pInstance;   
    wlInfo m_wlInfoData;


private:
};

#endif  //  SURFACEIMP_H
/* EOF */
