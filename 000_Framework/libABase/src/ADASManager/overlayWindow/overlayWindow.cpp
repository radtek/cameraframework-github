/**
 */
#include "overlayWindow.h"

overlayWindow* overlayWindow::m_pInstance = NULL;

overlayWindow::overlayWindow()
{
    memset(&m_wlInfoData, 0, sizeof(wlInfo));
}

overlayWindow::~overlayWindow()
{

}

overlayWindow* overlayWindow::getInstance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new overlayWindow();
    }
    return m_pInstance;
}

void overlayWindow::deInstance()
{
    if(m_pInstance != NULL)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

static void
pointer_handle_enter(void *data, struct wl_pointer *pointer,
             uint32_t serial, struct wl_surface *surface,
             wl_fixed_t sx, wl_fixed_t sy)
{
    overlayWindow::wlInfo *d = (overlayWindow::wlInfo *)data;
    struct wl_buffer *buffer;
    struct wl_cursor *cursor = d->default_cursor;
    struct wl_cursor_image *image;

    if (d->window->fullscreen)
        wl_pointer_set_cursor(pointer, serial, NULL, 0, 0);
    else if (cursor) {
        image = d->default_cursor->images[0];
        buffer = wl_cursor_image_get_buffer(image);
        if (!buffer)
            return;
        wl_pointer_set_cursor(pointer, serial,
                      d->cursor_surface,
                      image->hotspot_x,
                      image->hotspot_y);
        wl_surface_attach(d->cursor_surface, buffer, 0, 0);
        wl_surface_damage(d->cursor_surface, 0, 0,
                  image->width, image->height);
        wl_surface_commit(d->cursor_surface);
    }
}

static void
pointer_handle_leave(void *data, struct wl_pointer *pointer,
             uint32_t serial, struct wl_surface *surface)
{
}

static void
pointer_handle_motion(void *data, struct wl_pointer *pointer,
              uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
}

static void
pointer_handle_button(void *data, struct wl_pointer *wl_pointer,
              uint32_t serial, uint32_t time, uint32_t button,
              uint32_t state)
{
    //struct display *display = data;
    overlayWindow::wlInfo *display = (overlayWindow::wlInfo *)data;

    if (!display->window->xdg_toplevel)
        return;

    // if (button == BTN_LEFT && state == WL_POINTER_BUTTON_STATE_PRESSED)
    //     zxdg_toplevel_v6_move(display->window->xdg_toplevel,
    //                   display->seat, serial);
}

static void
pointer_handle_axis(void *data, struct wl_pointer *wl_pointer,
            uint32_t time, uint32_t axis, wl_fixed_t value)
{
}

static const struct wl_pointer_listener pointer_listener = {
    pointer_handle_enter,
    pointer_handle_leave,
    pointer_handle_motion,
    pointer_handle_button,
    pointer_handle_axis,
};

static void
keyboard_handle_keymap(void *data, struct wl_keyboard *keyboard,
               uint32_t format, int fd, uint32_t size)
{
}

static void
keyboard_handle_enter(void *data, struct wl_keyboard *keyboard,
              uint32_t serial, struct wl_surface *surface,
              struct wl_array *keys)
{
}

static void
keyboard_handle_leave(void *data, struct wl_keyboard *keyboard,
              uint32_t serial, struct wl_surface *surface)
{
}

static void
keyboard_handle_key(void *data, struct wl_keyboard *keyboard,
            uint32_t serial, uint32_t time, uint32_t key,
            uint32_t state)
{
    //struct display *d = data;
    overlayWindow::wlInfo *d = (overlayWindow::wlInfo *)data;

    if (!d->shell)
        return;

    // if (key == KEY_F11 && state) {
    //     if (d->window->fullscreen)
    //         zxdg_toplevel_v6_unset_fullscreen(d->window->xdg_toplevel);
    //     else
    //         zxdg_toplevel_v6_set_fullscreen(d->window->xdg_toplevel,
    //                         NULL);
    // } else if (key == KEY_ESC && state)
    //     running = 0;
}

static void
keyboard_handle_modifiers(void *data, struct wl_keyboard *keyboard,
              uint32_t serial, uint32_t mods_depressed,
              uint32_t mods_latched, uint32_t mods_locked,
              uint32_t group)
{
}

static const struct wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_key,
    keyboard_handle_modifiers,
};

static void
touch_handle_down(void *data, struct wl_touch *wl_touch,
          uint32_t serial, uint32_t time, struct wl_surface *surface,
          int32_t id, wl_fixed_t x_w, wl_fixed_t y_w)
{
    overlayWindow::wlInfo *d = (overlayWindow::wlInfo *)data;

    if (!d->shell)
        return;

    zxdg_toplevel_v6_move(d->window->xdg_toplevel, d->seat, serial);
}

static void
touch_handle_up(void *data, struct wl_touch *wl_touch,
        uint32_t serial, uint32_t time, int32_t id)
{
}

static void
touch_handle_motion(void *data, struct wl_touch *wl_touch,
            uint32_t time, int32_t id, wl_fixed_t x_w, wl_fixed_t y_w)
{
}

static void
touch_handle_frame(void *data, struct wl_touch *wl_touch)
{
}

static void
touch_handle_cancel(void *data, struct wl_touch *wl_touch)
{
}

static const struct wl_touch_listener touch_listener = {
    touch_handle_down,
    touch_handle_up,
    touch_handle_motion,
    touch_handle_frame,
    touch_handle_cancel,
};

static void
seat_handle_capabilities(void *data, struct wl_seat *seat,
             /*enum*/ uint32_t caps)
{
    overlayWindow::wlInfo *d = (overlayWindow::wlInfo *)data;

    if ((caps & WL_SEAT_CAPABILITY_POINTER) && !d->pointer) {
        d->pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(d->pointer, &pointer_listener, d);
    } else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && d->pointer) {
        wl_pointer_destroy(d->pointer);
        d->pointer = NULL;
    }

    if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && !d->keyboard) {
        d->keyboard = wl_seat_get_keyboard(seat);
        wl_keyboard_add_listener(d->keyboard, &keyboard_listener, d);
    } else if (!(caps & WL_SEAT_CAPABILITY_KEYBOARD) && d->keyboard) {
        wl_keyboard_destroy(d->keyboard);
        d->keyboard = NULL;
    }

    if ((caps & WL_SEAT_CAPABILITY_TOUCH) && !d->touch) {
        d->touch = wl_seat_get_touch(seat);
        wl_touch_set_user_data(d->touch, d);
        wl_touch_add_listener(d->touch, &touch_listener, d);
    } else if (!(caps & WL_SEAT_CAPABILITY_TOUCH) && d->touch) {
        wl_touch_destroy(d->touch);
        d->touch = NULL;
    }
}

static const struct wl_seat_listener seat_listener = {
    seat_handle_capabilities,
};

static void
xdg_shell_ping(void *data, struct zxdg_shell_v6 *shell, uint32_t serial)
{
    zxdg_shell_v6_pong(shell, serial);
}

static const struct zxdg_shell_v6_listener xdg_shell_listener = {
    xdg_shell_ping,
};

static void registry_handle_global(void *data, struct wl_registry *registry,
               uint32_t name, const char *interface, uint32_t version)
{
#if 0
    overlayWindow::wlInfo *d = (overlayWindow::wlInfo *)data;

    if (strcmp(interface, "wl_compositor") == 0)
    {
        d->compositor =(wl_compositor *)(wl_registry_bind(registry, name,
                                                                    &wl_compositor_interface, 1));

    }
    else if (strcmp(interface, "wl_seat") == 0)
    {
        d->seat = (wl_seat*)(wl_registry_bind(registry, name,
                                            &wl_seat_interface, 1));

        wl_seat_add_listener(d->seat, &seat_listener, d);
    }
    else if (strcmp(interface, "wl_shm") == 0)
    {
        d->shm = (wl_shm*)(wl_registry_bind(registry, name,
                                                                         &wl_shm_interface, 1));

        d->cursor_theme = wl_cursor_theme_load(NULL, 32, d->shm);

        if (!d->cursor_theme)
        {
            fprintf(stderr, "unable to load default theme\n");
            return;
        }

        d->default_cursor = wl_cursor_theme_get_cursor(d->cursor_theme, "left_ptr");

        if (!d->default_cursor)
        {
            fprintf(stderr, "unable to load default left pointer\n");
        }
    }
#endif
    overlayWindow::wlInfo *d = (overlayWindow::wlInfo *)data;
#if 1
    if (strcmp(interface, "wl_compositor") == 0) {
        d->compositor =
            (wl_compositor*)wl_registry_bind(registry, name,
                     &wl_compositor_interface,
                     version>4 ? 4 : version
                     );
    } else if (strcmp(interface, "zxdg_shell_v6") == 0) {
        d->shell = (zxdg_shell_v6*)wl_registry_bind(registry, name,
                        &zxdg_shell_v6_interface, 1);
        zxdg_shell_v6_add_listener(d->shell, &xdg_shell_listener, d);
    } else if (strcmp(interface, "wl_seat") == 0) {
        d->seat = (wl_seat*)wl_registry_bind(registry, name,
                       &wl_seat_interface, 1);
        wl_seat_add_listener(d->seat, &seat_listener, d);
    } else if (strcmp(interface, "wl_shm") == 0) {
        d->shm = (wl_shm*)wl_registry_bind(registry, name,
                      &wl_shm_interface, 1);
        d->cursor_theme = wl_cursor_theme_load(NULL, 32, d->shm);
        if (!d->cursor_theme) {
            fprintf(stderr, "unable to load default theme\n");
            return;
        }
        d->default_cursor =
            wl_cursor_theme_get_cursor(d->cursor_theme, "left_ptr");
        if (!d->default_cursor) {
            fprintf(stderr, "unable to load default left pointer\n");
            // TODO: abort ?
        }
    } else if (strcmp(interface, "ivi_application") == 0) {
        d->ivi_application =
            (ivi_application*)wl_registry_bind(registry, name,
                     &ivi_application_interface, 1);
    }

#endif
}


static void registry_handle_global_remove(void *data, struct wl_registry *registry,
                  uint32_t name)
{

};

static const struct wl_registry_listener registry_listener =
{
    registry_handle_global,
    registry_handle_global_remove
};


VOID overlayWindow::init()
{
    printf("xiaole---debug init | wl_display_connect\n");
    m_wlInfoData.display = wl_display_connect(NULL);
    printf("xiaole---debug init | wl_display_get_registry\n");
    m_wlInfoData.registry = wl_display_get_registry(m_wlInfoData.display);
    printf("xiaole---debug init | wl_display_get_registry\n");
    wl_registry_add_listener(m_wlInfoData.registry, &registry_listener,
                                                &m_wlInfoData);
    printf("xiaole---debug init | wl_display_dispatch\n");
    wl_display_roundtrip(m_wlInfoData.display);
}

VOID overlayWindow::createSurface(windowInfo& info)
{
    printf("xiaole---debug createSurface\n");
    m_wlInfoData.surface = wl_compositor_create_surface(m_wlInfoData.compositor);
    printf("xiaole---debug wl_compositor_create_surface\n");
    m_wlInfoData.native =wl_egl_window_create(m_wlInfoData.surface,
                                              info.view->width,
                                              info.view->height);
     printf("xiaole---debug wl_egl_window_create\n");
    info.window = m_wlInfoData.native;
}

static void
handle_surface_configure(void *data, struct zxdg_surface_v6 *surface,
             uint32_t serial)
{
    overlayWindow::wlInfo *window = (overlayWindow::wlInfo *)data;

    zxdg_surface_v6_ack_configure(surface, serial);

    window->window->wait_for_configure = false;
}

static const struct zxdg_surface_v6_listener xdg_surface_listener = {
    handle_surface_configure
};


static void
handle_toplevel_configure(void *data, struct zxdg_toplevel_v6 *toplevel,
              int32_t width, int32_t height,
              struct wl_array *states)
{
    //struct window *window = data;
    overlayWindow::wlInfo *window = (overlayWindow::wlInfo *)data;
    uint32_t *p;

    // window->window->fullscreen = 0;
    // wl_array_for_each(p, states) {
    //     uint32_t state = *(uint32_t*)p;
    //     switch (state) {
    //     case ZXDG_TOPLEVEL_V6_STATE_FULLSCREEN:
    //         window->window->fullscreen = 1;
    //         break;
    //     }
    // }

    if (width > 0 && height > 0) {
        if (!window->window->fullscreen) {
            window->window->view->width = width;
            window->window->view->height = height;
        }
         window->window->view->width = width;
         window->window->view->height = height;
    } else if (!window->window->fullscreen) {
         window->window->view->width = width;
         window->window->view->height = height;
    }

    if (window->native)
        wl_egl_window_resize(window->native,
                     window->window->view->width,
                     window->window->view->height, 0, 0);
}

static void
handle_toplevel_close(void *data, struct zxdg_toplevel_v6 *xdg_toplevel)
{
    //running = 0;
}

static const struct zxdg_toplevel_v6_listener xdg_toplevel_listener = {
    handle_toplevel_configure,
    handle_toplevel_close,
};

VOID overlayWindow::create_xdg_surface()
{
    m_wlInfoData.window->xdg_surface = zxdg_shell_v6_get_xdg_surface(m_wlInfoData.shell,
                                m_wlInfoData.surface);
    zxdg_surface_v6_add_listener(m_wlInfoData.window->xdg_surface,
                     &xdg_surface_listener, &m_wlInfoData);

    m_wlInfoData.window->xdg_toplevel =
        zxdg_surface_v6_get_toplevel(m_wlInfoData.window->xdg_surface);
    zxdg_toplevel_v6_add_listener(m_wlInfoData.window->xdg_toplevel,
                      &xdg_toplevel_listener, &m_wlInfoData);

    zxdg_toplevel_v6_set_title(m_wlInfoData.window->xdg_toplevel, "camera display");

    m_wlInfoData.window->wait_for_configure = true;
    wl_surface_commit(m_wlInfoData.surface);
}

VOID overlayWindow::distroySurface(windowInfo& info)
{

}

VOID overlayWindow::draw()
{
    wl_display_dispatch(m_wlInfoData.display);
}