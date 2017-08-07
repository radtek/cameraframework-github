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

static void registry_handle_global(void *data, struct wl_registry *registry,
               uint32_t name, const char *interface, uint32_t version)
{
#if 1
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
    wl_display_dispatch(m_wlInfoData.display);  
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

VOID overlayWindow::distroySurface(windowInfo& info)
{

}

VOID overlayWindow::draw()
{
    wl_display_dispatch(m_wlInfoData.display);
}