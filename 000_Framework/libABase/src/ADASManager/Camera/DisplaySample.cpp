
#include "ADASManager/Camera/DisplaySample.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

char* DisplaySample::vert_shader_text =
    "uniform mat4 rotation;\n"
    "attribute vec4 pos;\n"
    "attribute vec4 color;\n"
    "varying vec4 v_color;\n"
    "void main() {\n"
    "  gl_Position = rotation * pos;\n"
    "  v_color = color;\n"
    "}\n";

char* DisplaySample::frag_shader_text =
    "precision mediump float;\n"
    "varying vec4 v_color;\n"
    "void main() {\n"
    "  gl_FragColor = v_color;\n"
    "}\n";

int DisplaySample::running = 1;

struct wl_registry_listener DisplaySample::registry_listener = {
    registry_handle_global,
    registry_handle_global_remove
};

struct zxdg_shell_v6_listener DisplaySample::xdg_shell_listener = {
    xdg_shell_ping,
};

struct wl_seat_listener DisplaySample::seat_listener = {
    seat_handle_capabilities,
};

struct wl_keyboard_listener DisplaySample::keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_key,
    keyboard_handle_modifiers,
};

struct wl_touch_listener DisplaySample::touch_listener = {
    touch_handle_down,
    touch_handle_up,
    touch_handle_motion,
    touch_handle_frame,
    touch_handle_cancel,
};

struct wl_pointer_listener DisplaySample::pointer_listener = {
    pointer_handle_enter,
    pointer_handle_leave,
    pointer_handle_motion,
    pointer_handle_button,
    pointer_handle_axis,
};

struct ivi_surface_listener DisplaySample::ivi_surface_listener = {
    handle_ivi_surface_configure,
};

struct zxdg_toplevel_v6_listener DisplaySample::xdg_toplevel_listener = {
    handle_toplevel_configure,
    handle_toplevel_close,
};

struct zxdg_surface_v6_listener DisplaySample::xdg_surface_listener = {
    handle_surface_configure
};

struct display DisplaySample::m_Display = { 0 };
struct window  DisplaySample::m_Window  = { 0 };

DisplaySample::DisplaySample()
{
    struct sigaction sigint;

    m_Window.display = &m_Display;
    m_Display.window = &m_Window;
    m_Window.geometry.width  = 640;
    m_Window.geometry.height = 480;
    //  m_Window.geometry.width  = 250;
    // m_Window.geometry.height = 250;
    m_Window.window_size = m_Window.geometry;
    m_Window.buffer_size = 32;
    m_Window.frame_sync = 1;
    m_Window.delay = 0;

    // for (i = 1; i < argc; i++) {
    //     if (strcmp("-d", argv[i]) == 0 && i+1 < argc)
    //         window.delay = atoi(argv[++i]);
    //     else if (strcmp("-f", argv[i]) == 0)
    //         window.fullscreen = 1;
    //     else if (strcmp("-o", argv[i]) == 0)
    //         window.opaque = 1;
    //     else if (strcmp("-s", argv[i]) == 0)
    //         window.buffer_size = 16;
    //     else if (strcmp("-b", argv[i]) == 0)
    //         window.frame_sync = 0;
    //     else if (strcmp("-h", argv[i]) == 0)
    //         usage(EXIT_SUCCESS);
    //     else
    //         usage(EXIT_FAILURE);
    // }

    m_Display.display = wl_display_connect(NULL);
    assert(m_Display.display);

    m_Display.registry = wl_display_get_registry(m_Display.display);
    wl_registry_add_listener(m_Display.registry,
                 &registry_listener, &m_Display);

    wl_display_roundtrip(m_Display.display);

    // init_egl(&m_Display, &m_Window);
    // create_surface(&m_Window);
    //init_gl(&m_Window);

    // m_Display.cursor_surface =
    //     wl_compositor_create_surface(m_Display.compositor);

    sigint.sa_handler = signal_int;
    sigemptyset(&sigint.sa_mask);
    sigint.sa_flags = SA_RESETHAND;
    sigaction(SIGINT, &sigint, NULL);
}

DisplaySample::~DisplaySample()
{
    fprintf(stderr, "simple-egl exiting\n");

    destroy_surface(&m_Window);
    fini_egl(&m_Display);

    //wl_surface_destroy(m_Display.cursor_surface);
    if (m_Display.cursor_theme) {
        wl_cursor_theme_destroy(m_Display.cursor_theme);
    }

    if (m_Display.shell) {
        zxdg_shell_v6_destroy(m_Display.shell);
    }

    if (m_Display.ivi_application) {
        ivi_application_destroy(m_Display.ivi_application);
    }

    if (m_Display.compositor) {
        wl_compositor_destroy(m_Display.compositor);
    }

    wl_registry_destroy(m_Display.registry);
    wl_display_flush(m_Display.display);
    wl_display_disconnect(m_Display.display);
    fprintf(stderr, "simple-egl exiting OK\n");
}

void DisplaySample::Init()
{
    init_egl(&m_Display, &m_Window);
    create_surface(&m_Window);
    init_gl(&m_Window);
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
        fprintf(stderr, "did not find config with buffer size %d\n",
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
        printf("has EGL_EXT_buffer_age and %s\n", swap_damage_ext_to_entrypoint[i].extension);

}

void DisplaySample::fini_egl(struct display *display)
{
    eglTerminate(display->egl.dpy);
    eglReleaseThread();
}

GLuint DisplaySample::create_shader(struct window *window, const char *source, GLenum shader_type)
{
    GLuint shader;
    GLint status;

    shader = glCreateShader(shader_type);
    assert(shader != 0);

    glShaderSource(shader, 1, (const char **) &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char log[1000];
        GLsizei len;
        glGetShaderInfoLog(shader, 1000, &len, log);
        fprintf(stderr, "Error: compiling %s: %*s\n",
            shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment",
            len, log);
        exit(1);
    }

    return shader;
}

void DisplaySample::init_gl(struct window *window)
{
    printf("=======================================\n");
    // GLuint frag, vert;
    // GLuint program;
    // GLint status;

    // frag = create_shader(window, frag_shader_text, GL_FRAGMENT_SHADER);
    // vert = create_shader(window, vert_shader_text, GL_VERTEX_SHADER);

    // program = glCreateProgram();
    // glAttachShader(program, frag);
    // glAttachShader(program, vert);
    // glLinkProgram(program);

    // glGetProgramiv(program, GL_LINK_STATUS, &status);
    // if (!status) {
    //     char log[1000];
    //     GLsizei len;
    //     glGetProgramInfoLog(program, 1000, &len, log);
    //     fprintf(stderr, "Error: linking:\n%*s\n", len, log);
    //     exit(1);
    // }

    // glUseProgram(program);

    // window->gl.pos = 0;
    // window->gl.col = 1;

    // glBindAttribLocation(program, window->gl.pos, "pos");
    // glBindAttribLocation(program, window->gl.col, "color");
    // glLinkProgram(program);

    // window->gl.rotation_uniform =
    //     glGetUniformLocation(program, "rotation");
}

void DisplaySample::handle_surface_configure(void *data, struct zxdg_surface_v6 *surface,
             uint32_t serial)
{
    struct window *window = (struct window *)data;

    zxdg_surface_v6_ack_configure(surface, serial);

    window->wait_for_configure = false;
}

void DisplaySample::handle_toplevel_configure(void *data, struct zxdg_toplevel_v6 *toplevel,
              int32_t width, int32_t height,
              struct wl_array *states)
{
    struct window *window = (struct window *)data;
    uint32_t *p;

    window->fullscreen = 0;

    // #define wl_array_for_each(pos, array)              
    // for (pos = (array)->data; (const char *) pos < ((const char *) (array)->data + (array)->size); (pos)++)
   

    // wl_array_for_each(p, states) {
    //     uint32_t state = *p;
    //     switch (state) {
    //     case ZXDG_TOPLEVEL_V6_STATE_FULLSCREEN:
    //         window->fullscreen = 1;
    //         break;
    //     }
    // }

    if (width > 0 && height > 0) {
        if (!window->fullscreen) {
            window->window_size.width = width;
            window->window_size.height = height;
        }
        window->geometry.width = width;
        window->geometry.height = height;
    } else if (!window->fullscreen) {
        window->geometry = window->window_size;
    }

    if (window->native)
        wl_egl_window_resize(window->native,
                     window->geometry.width,
                     window->geometry.height, 0, 0);
}

void DisplaySample::handle_toplevel_close(void *data, struct zxdg_toplevel_v6 *xdg_toplevel)
{
    running = 0;
}

void DisplaySample::handle_ivi_surface_configure(void *data, struct ivi_surface *ivi_surface,
                             int32_t width, int32_t height)
{
    struct window *window = (struct window *)data;

    wl_egl_window_resize(window->native, width, height, 0, 0);

    window->geometry.width = width;
    window->geometry.height = height;

    if (!window->fullscreen)
        window->window_size = window->geometry;
}

void DisplaySample::create_xdg_surface(struct window *window, struct display *display)
{
    window->xdg_surface = zxdg_shell_v6_get_xdg_surface(display->shell,
                                window->surface);
    zxdg_surface_v6_add_listener(window->xdg_surface,
                     &xdg_surface_listener, window);

    window->xdg_toplevel =
        zxdg_surface_v6_get_toplevel(window->xdg_surface);
    zxdg_toplevel_v6_add_listener(window->xdg_toplevel,
                      &xdg_toplevel_listener, window);

    zxdg_toplevel_v6_set_title(window->xdg_toplevel, "simple-egl");

    window->wait_for_configure = true;
    wl_surface_commit(window->surface);
}

void DisplaySample::create_ivi_surface(struct window *window, struct display *display)
{
    uint32_t id_ivisurf = IVI_SURFACE_ID + (uint32_t)getpid();
    window->ivi_surface =
        ivi_application_surface_create(display->ivi_application,
                           id_ivisurf, window->surface);

    if (window->ivi_surface == NULL) {
        fprintf(stderr, "Failed to create ivi_client_surface\n");
        abort();
    }

    ivi_surface_add_listener(window->ivi_surface,
                 &ivi_surface_listener, window);
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


    if (display->shell) {
        create_xdg_surface(window, display);
    } else if (display->ivi_application ) {
        create_ivi_surface(window, display);
    } else {
        assert(0);
    }

    ret = eglMakeCurrent(window->display->egl.dpy, window->egl_surface,
                 window->egl_surface, window->display->egl.ctx);
    assert(ret == EGL_TRUE);

    if (!window->frame_sync)
        eglSwapInterval(display->egl.dpy, 0);

    if (!display->shell)
        return;

    if (window->fullscreen)
        zxdg_toplevel_v6_set_fullscreen(window->xdg_toplevel, NULL);
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

    if (window->xdg_toplevel)
        zxdg_toplevel_v6_destroy(window->xdg_toplevel);
    if (window->xdg_surface)
        zxdg_surface_v6_destroy(window->xdg_surface);
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
    // static const GLfloat verts[3][2] = {
    //     { -0.5, -0.5 },
    //     {  0.5, -0.5 },
    //     {  0,    0.5 }
    // };
    // static const GLfloat colors[3][3] = {
    //     { 1, 0, 0 },
    //     { 0, 1, 0 },
    //     { 0, 0, 1 }
    // };
    // GLfloat angle;
    // GLfloat rotation[4][4] = {
    //     { 1, 0, 0, 0 },
    //     { 0, 1, 0, 0 },
    //     { 0, 0, 1, 0 },
    //     { 0, 0, 0, 1 }
    // };
    // static const uint32_t speed_div = 5, benchmark_interval = 5;
    // struct wl_region *region;
    // EGLint rect[4];
    // EGLint buffer_age = 0;
    // struct timeval tv;

    // assert(window->callback == callback);
    // window->callback = NULL;

    // if (callback)
    //     wl_callback_destroy(callback);

    // gettimeofday(&tv, NULL);
    // time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    // if (window->frames == 0)
    //     window->benchmark_time = time;
    // if (time - window->benchmark_time > (benchmark_interval * 1000)) {
    //     printf("%d frames in %d seconds: %f fps\n",
    //            window->frames,
    //            benchmark_interval,
    //            (float) window->frames / benchmark_interval);
    //     window->benchmark_time = time;
    //     window->frames = 0;
    // }

    // angle = (time / speed_div) % 360 * M_PI / 180.0;
    // rotation[0][0] =  cos(angle);
    // rotation[0][2] =  sin(angle);
    // rotation[2][0] = -sin(angle);
    // rotation[2][2] =  cos(angle);

    // if (display->swap_buffers_with_damage)
    //     eglQuerySurface(display->egl.dpy, window->egl_surface,
    //             EGL_BUFFER_AGE_EXT, &buffer_age);

    // glViewport(0, 0, window->geometry.width, window->geometry.height);

    // glUniformMatrix4fv(window->gl.rotation_uniform, 1, GL_FALSE,
    //            (GLfloat *) rotation);

    // glClearColor(0.0, 0.0, 0.0, 0.5);
    // glClear(GL_COLOR_BUFFER_BIT);

    // glVertexAttribPointer(window->gl.pos, 2, GL_FLOAT, GL_FALSE, 0, verts);
    // glVertexAttribPointer(window->gl.col, 3, GL_FLOAT, GL_FALSE, 0, colors);
    // glEnableVertexAttribArray(window->gl.pos);
    // glEnableVertexAttribArray(window->gl.col);

    // glDrawArrays(GL_TRIANGLES, 0, 3);

    // glDisableVertexAttribArray(window->gl.pos);
    // glDisableVertexAttribArray(window->gl.col);

    // usleep(window->delay);

    // if (window->opaque || window->fullscreen) {
    //     region = wl_compositor_create_region(window->display->compositor);
    //     wl_region_add(region, 0, 0,
    //               window->geometry.width,
    //               window->geometry.height);
    //     wl_surface_set_opaque_region(window->surface, region);
    //     wl_region_destroy(region);
    // } else {
    //     wl_surface_set_opaque_region(window->surface, NULL);
    // }

    // if (display->swap_buffers_with_damage && buffer_age > 0) {
    //     rect[0] = window->geometry.width / 4 - 1;
    //     rect[1] = window->geometry.height / 4 - 1;
    //     rect[2] = window->geometry.width / 2 + 2;
    //     rect[3] = window->geometry.height / 2 + 2;
    //     display->swap_buffers_with_damage(display->egl.dpy,
    //                       window->egl_surface,
    //                       rect, 1);
    // } else {
    //     eglSwapBuffers(display->egl.dpy, window->egl_surface);
    // }
    // window->frames++;

    eglSwapBuffers(display->egl.dpy, window->egl_surface);
    //glutSwapBuffers();
}

void DisplaySample::pointer_handle_enter(void *data, struct wl_pointer *pointer,
             uint32_t serial, struct wl_surface *surface,
             wl_fixed_t sx, wl_fixed_t sy)
{
    struct display *display = (struct display *)data;
    struct wl_buffer *buffer;
    struct wl_cursor *cursor = display->default_cursor;
    struct wl_cursor_image *image;

    if (display->window->fullscreen)
        wl_pointer_set_cursor(pointer, serial, NULL, 0, 0);
    else if (cursor) {
        image = display->default_cursor->images[0];
        buffer = wl_cursor_image_get_buffer(image);
        if (!buffer)
            return;
        wl_pointer_set_cursor(pointer, serial,
                      display->cursor_surface,
                      image->hotspot_x,
                      image->hotspot_y);
        wl_surface_attach(display->cursor_surface, buffer, 0, 0);
        wl_surface_damage(display->cursor_surface, 0, 0,
                  image->width, image->height);
        wl_surface_commit(display->cursor_surface);
    }
}

void DisplaySample::pointer_handle_leave(void *data, struct wl_pointer *pointer,
             uint32_t serial, struct wl_surface *surface)
{
}

void DisplaySample::pointer_handle_motion(void *data, struct wl_pointer *pointer,
              uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
}

void DisplaySample::pointer_handle_button(void *data, struct wl_pointer *wl_pointer,
              uint32_t serial, uint32_t time, uint32_t button,
              uint32_t state)
{
    struct display *display = (struct display *)data;

    if (!display->window->xdg_toplevel)
        return;

    if (button == BTN_LEFT && state == WL_POINTER_BUTTON_STATE_PRESSED)
        zxdg_toplevel_v6_move(display->window->xdg_toplevel,
                      display->seat, serial);
}

void DisplaySample::pointer_handle_axis(void *data, struct wl_pointer *wl_pointer,
            uint32_t time, uint32_t axis, wl_fixed_t value)
{
}

void DisplaySample::touch_handle_down(void *data, struct wl_touch *wl_touch,
          uint32_t serial, uint32_t time, struct wl_surface *surface,
          int32_t id, wl_fixed_t x_w, wl_fixed_t y_w)
{
    struct display *d = (struct display*)data;

    if (!d->shell)
        return;

    zxdg_toplevel_v6_move(d->window->xdg_toplevel, d->seat, serial);
}

void DisplaySample::touch_handle_up(void *data, struct wl_touch *wl_touch,
        uint32_t serial, uint32_t time, int32_t id)
{
}

void DisplaySample::touch_handle_motion(void *data, struct wl_touch *wl_touch,
            uint32_t time, int32_t id, wl_fixed_t x_w, wl_fixed_t y_w)
{
}

void DisplaySample::touch_handle_frame(void *data, struct wl_touch *wl_touch)
{
}

void DisplaySample::touch_handle_cancel(void *data, struct wl_touch *wl_touch)
{
}

void DisplaySample::keyboard_handle_keymap(void *data, struct wl_keyboard *keyboard,
               uint32_t format, int fd, uint32_t size)
{
}

void DisplaySample::keyboard_handle_enter(void *data, struct wl_keyboard *keyboard,
              uint32_t serial, struct wl_surface *surface,
              struct wl_array *keys)
{
}

void DisplaySample::keyboard_handle_leave(void *data, struct wl_keyboard *keyboard,
              uint32_t serial, struct wl_surface *surface)
{
}

void DisplaySample::keyboard_handle_key(void *data, struct wl_keyboard *keyboard,
            uint32_t serial, uint32_t time, uint32_t key,
            uint32_t state)
{
    struct display *d = (struct display *)data;

    if (!d->shell)
        return;

    if (key == KEY_F11 && state) {
        if (d->window->fullscreen)
            zxdg_toplevel_v6_unset_fullscreen(d->window->xdg_toplevel);
        else
            zxdg_toplevel_v6_set_fullscreen(d->window->xdg_toplevel,
                            NULL);
    } else if (key == KEY_ESC && state)
        running = 0;
}

void DisplaySample::keyboard_handle_modifiers(void *data, struct wl_keyboard *keyboard,
              uint32_t serial, uint32_t mods_depressed,
              uint32_t mods_latched, uint32_t mods_locked,
              uint32_t group)
{
}

void DisplaySample::seat_handle_capabilities(void *data, struct wl_seat *seat,
            /*enum wl_seat_capability*/ uint32_t caps)
{
    struct display *d = (struct display *)data;

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

void DisplaySample::xdg_shell_ping(void *data, struct zxdg_shell_v6 *shell, uint32_t serial)
{
    zxdg_shell_v6_pong(shell, serial);
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
}

void DisplaySample::registry_handle_global_remove(void *data, struct wl_registry *registry,
                  uint32_t name)
{
}

void DisplaySample::signal_int(int signum)
{
    running = 0;
}

void DisplaySample::usage(int error_code)
{
    fprintf(stderr, "Usage: simple-egl [OPTIONS]\n\n"
        "  -d <us>\tBuffer swap delay in microseconds\n"
        "  -f\tRun in fullscreen mode\n"
        "  -o\tCreate an opaque surface\n"
        "  -s\tUse a 16 bpp EGL config\n"
        "  -b\tDon't sync to compositor redraw (eglSwapInterval 0)\n"
        "  -h\tThis help text\n\n");

    exit(error_code);
}


} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman