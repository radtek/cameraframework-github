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

static const struct wl_seat_listener seat_listener = {
};

struct handler_info {
    struct wl_seat *seat;
    uint32_t bind_version;
    bool use_unversioned;
};

static void registry_handle_global(void *data, struct wl_registry *registry,
               uint32_t id, const char *intf, uint32_t ver)
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
    struct handler_info *hi = data;

    /* This is only for the proxy version test */
    if (hi->bind_version)
        ver = hi->bind_version;

    if (strcmp(intf, "wl_seat") == 0) {
        if (hi->use_unversioned)
            hi->seat = old_registry_bind(registry, id,
                             &wl_seat_interface, ver);
        else
            hi->seat = wl_registry_bind(registry, id,
                            &wl_seat_interface, ver);
        assert(hi->seat);
    }

}


static void registry_handle_global_remove(void *data, struct wl_registry *registry,
                  uint32_t name)
{

};

static const struct wl_registry_listener registry_listener = 
{
    registry_handle_global,
    NULL
};


VOID overlayWindow::init()
{
    m_wlInfoData.display = wl_display_connect(NULL);
    m_wlInfoData.registry = wl_display_get_registry(m_wlInfoData.display);

    wl_registry_add_listener(m_wlInfoData.registry, &registry_listener, 
                                                &m_wlInfoData);

    wl_display_dispatch(m_wlInfoData.display);  
}

VOID overlayWindow::createSurface(windowInfo& info)
{
    m_wlInfoData.surface = wl_compositor_create_surface(m_wlInfoData.compositor);
    m_wlInfoData.native =wl_egl_window_create(m_wlInfoData.surface,
                                                                                     info.view->width,
                                                                                     info.view->height);
    info.window = m_wlInfoData.native;
}

VOID overlayWindow::distroySurface(windowInfo& info)
{

}