#include "GlShell.h"

//#define  FRAME_CALLBACK_SUPPROT 1 //enable  throttling to callback
#define  LM_SUPPORT 1 //enable this line for layer manager

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <signal.h>

#include <linux/input.h>

#include <wayland-client.h>
#include <wayland-egl.h>
#include <wayland-cursor.h>

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <sys/types.h>
#include <unistd.h>

#ifdef LM_SUPPORT
#include "ilm/ilm_control.h"
#include "ilm/ilm_client.h"
#endif

int           width = 800;
int           height = 480;
#ifdef LM_SUPPORT
t_ilm_layer   ilmLayerId = 1000;
t_ilm_surface ilmSurfaceId = 10;
#endif  

#ifdef SHELL_SUPPORT
#include "xdg-shell-client-protocol.h"

#include "protocol/ivi-application-client-protocol.h"
#define IVI_SURFACE_ID 9000
#include "shared/platform.h"

#ifndef EGL_EXT_swap_buffers_with_damage
#define EGL_EXT_swap_buffers_with_damage 1
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC)(EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#endif

#ifndef EGL_EXT_buffer_age
#define EGL_EXT_buffer_age 1
#define EGL_BUFFER_AGE_EXT          0x313D
#endif
#endif //SHELL_SUPPORT

static void surfaceCallbackFunction(t_ilm_uint surface_id, struct ilmSurfaceProperties* sp, t_ilm_notification_mask m)
{
    ilmErrorTypes rtnv = (ilmErrorTypes)0; 

    if ((unsigned)m & ILM_NOTIFICATION_CONFIGURED)
    {
        rtnv = ilm_surfaceSetDestinationRectangle(surface_id, 0, 0, sp->origSourceWidth, sp->origSourceHeight);
        if(rtnv != ILM_SUCCESS)
        {
            printf("surfaceSetDestinationRectangle Failed (%d)\n", rtnv);
            //return 1;
        }
        printf("surfaceCallbackFunction DestinationRectangle\n");

        
        rtnv = ilm_surfaceSetSourceRectangle(surface_id, 0, 0, sp->origSourceWidth, sp->origSourceHeight);
        if(rtnv != ILM_SUCCESS)
        {
            printf("surfaceSetSourceRectangle Failed (%d)\n", rtnv);
            //return 1;
        }
        printf("surfaceCallbackFunction SourceRectangle\n");

        rtnv = ilm_surfaceSetVisibility(surface_id, ILM_TRUE);
        if(rtnv != ILM_SUCCESS)
        {
            printf("surfaceSetVisibility Failed (%d)\n", rtnv);
            //return 1;
        }
        printf("surfaceCallbackFunction Visibility\n");

        rtnv = ilm_surfaceSetOpacity(surface_id, 1.0f);
        if(rtnv != ILM_SUCCESS)
        {
            printf("surfaceSetOpacity Failed (%d)\n", rtnv);
            //return 1;
        }
    
        rtnv =  ilm_layerAddSurface(ilmLayerId, surface_id);
        if(rtnv != ILM_SUCCESS)
        {
            printf("layerAddSurface Failed (%d)\n", rtnv);
            //return 1;
        }
    
        rtnv = ilm_commitChanges();
        if(rtnv != ILM_SUCCESS)
        {
            printf("commitChanges Failed in callback (%d)\n", rtnv);
            //return 1;
        }
    }
    printf("surfaceCallbackFunction---------------surfaceCallbackFunction Done\n");
}

static int create_ilm_surface(struct display *display)
{   
    ilmErrorTypes rtnv =  (ilmErrorTypes)0;
    
    ilmClient_init((t_ilm_nativedisplay)display->display);
    if(rtnv != ILM_SUCCESS)
    {
        printf("ilmClient_init Failed (%d)\n", rtnv);
        return 1;
    }
    
    // Creates surfce
    rtnv = ilm_surfaceCreate((t_ilm_nativehandle)display->window->surface,
                             width, height,
                             ILM_PIXELFORMAT_RGBA_8888, &ilmSurfaceId);
    if (rtnv != ILM_SUCCESS)
    {
        printf("surfaceCreate Failed (%d)\n", rtnv);
        return 1;
    }
    
    //wl_display_flush(display->display); //only requiredwhen ilm_init used
    
    ilm_initWithNativedisplay((t_ilm_nativedisplay)display->display);
    //ilm_init();
    if(rtnv != ILM_SUCCESS)
    {
        printf("ilm_init Failed (%d)\n", rtnv);
        return 1;
    }
    
    rtnv = ilm_surfaceAddNotification(ilmSurfaceId,&surfaceCallbackFunction);
    if(rtnv != ILM_SUCCESS)
    {
        printf("ilm_surfaceAddNotification Failed (%d)\n", rtnv);
        //return 1;
    }
    rtnv = ilm_commitChanges();
    if(rtnv != ILM_SUCCESS)
    {
        printf("ilm_commitChanges 1 Failed\n");
    }

    printf("create_ilm_surface finished test2\n");
    return rtnv;
}

static void init_egl(struct display *display, struct window *window)
{
    static const EGLint context_attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    //const char *extensions;

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

#ifdef SHELL_SUPPORT
    display->egl.dpy =
        weston_platform_get_egl_display(EGL_PLATFORM_WAYLAND_KHR,
                        display->display, NULL);
    assert(display->egl.dpy);
#else
    display->egl.dpy = eglGetDisplay((EGLNativeDisplayType)display->display);
#endif 

    ret = eglInitialize(display->egl.dpy, &major, &minor);
    assert(ret == EGL_TRUE);
    ret = eglBindAPI(EGL_OPENGL_ES_API);
    assert(ret == EGL_TRUE);

    if (!eglGetConfigs(display->egl.dpy, NULL, 0, &count) || count < 1)
        assert(0);

    configs = (EGLConfig *)calloc(count, sizeof (EGLConfig));
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

}

static void fini_egl(struct display *display)
{
    eglTerminate(display->egl.dpy);
    eglReleaseThread();
}

static void create_surface(struct window *window)
{
    struct display *display = window->display;
    struct wl_region *region = NULL;
    //printf("------> display = %x\n",display);
    EGLBoolean ret;

    window->surface = wl_compositor_create_surface(display->compositor);

    // Remove input event consumption from the window surface
    region = wl_compositor_create_region(display->compositor);
    wl_region_subtract(region, 0, 0, window->geometry.width, window->geometry.height);
    wl_surface_set_input_region(window->surface, region);
    wl_region_destroy(region);

    //printf("------> surface = %x\n", window->surface);
    window->native =
        wl_egl_window_create(window->surface,
                     window->geometry.width,
                     window->geometry.height);
    //printf("------> native = %x\n",window->native);
    window->egl_surface = eglCreateWindowSurface(display->egl.dpy, display->egl.conf,
                    window->native, NULL);

    //printf("------> dpy = %x\n",window->display->egl.dpy);
    //printf("------> egl_surface = %x\n",window->egl_surface);
    ret = eglMakeCurrent(window->display->egl.dpy, window->egl_surface,
                 window->egl_surface, window->display->egl.ctx);

    assert(ret == EGL_TRUE);

    if (!window->frame_sync)
        eglSwapInterval(display->egl.dpy, 0);
        
}

static void destroy_surface(struct window *window)
{
    /* Required, otherwise segfault in egl_dri2.c: dri2_make_current()
     * on eglReleaseThread(). */
    eglMakeCurrent(window->display->egl.dpy, EGL_NO_SURFACE, EGL_NO_SURFACE,
               EGL_NO_CONTEXT);

    eglDestroySurface(window->display->egl.dpy, window->egl_surface);
    wl_egl_window_destroy(window->native);
    wl_surface_destroy(window->surface);

    if (window->callback)
        wl_callback_destroy(window->callback);
}

static void pointer_handle_enter(void *data, struct wl_pointer *pointer,
             uint32_t serial, struct wl_surface *surface,
             wl_fixed_t sx, wl_fixed_t sy)
{
    struct display *display = (struct display *)data;
    struct wl_buffer *buffer;
    struct wl_cursor *cursor = display->default_cursor;
    struct wl_cursor_image *image;
    
    printf("Pointer entered surface %p at %d %d\n", surface, sx, sy);

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

static void
pointer_handle_leave(void *data, struct wl_pointer *pointer,
             uint32_t serial, struct wl_surface *surface)
{
    printf("Pointer left surface %p\n", surface);
}

static void
pointer_handle_motion(void *data, struct wl_pointer *pointer,
              uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    printf("Pointer moved at %d %d\n", sx, sy);
}

static void
pointer_handle_button(void *data, struct wl_pointer *wl_pointer,
              uint32_t serial, uint32_t time, uint32_t button,
              uint32_t state)
{
    //struct display *display = (struct display *)data;
    printf("Pointer button\n");
}

static void
pointer_handle_axis(void *data, struct wl_pointer *wl_pointer,
            uint32_t time, uint32_t axis, wl_fixed_t value)
{   
    printf("Pointer handle axis axis = %d value = %d\n", axis, value);
}

static const struct wl_pointer_listener pointer_listener = {
    pointer_handle_enter,
    pointer_handle_leave,
    pointer_handle_motion,
    pointer_handle_button,
    pointer_handle_axis,
};

static void
touch_handle_down(void *data, struct wl_touch *wl_touch,
          uint32_t serial, uint32_t time, struct wl_surface *surface,
          int32_t id, wl_fixed_t x_w, wl_fixed_t y_w)
{
    //struct display *d = (struct display *)data;
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
keyboard_handle_keymap(void *data, struct wl_keyboard *keyboard,
               uint32_t format, int fd, uint32_t size)
{
    printf("keymap: keyboard keymap\n");
}

static void
keyboard_handle_enter(void *data, struct wl_keyboard *keyboard,
              uint32_t serial, struct wl_surface *surface,
              struct wl_array *keys)
{
    printf("enter: Keyboard gained focus\n");
}

static void
keyboard_handle_leave(void *data, struct wl_keyboard *keyboard,
              uint32_t serial, struct wl_surface *surface)
{
    printf("leave: Keyboard lost focus\n");
}

static void
keyboard_handle_key(void *data, struct wl_keyboard *keyboard,
            uint32_t serial, uint32_t time, uint32_t key,
            uint32_t state)
{
    //struct display *d = (struct display *)data;
    
    printf("key: Keyboard key\n");
    printf("Key is %d state is %d\n", key, state);
    
    if (key == KEY_HOME && state)
    {
        printf("----> KEY_HMOE detected \n");
    } 
    else if (key == KEY_CHAT && state)
    {
        printf("----> KEY_CHAT detected \n");
    }
    else if (key == KEY_MUTE && state)
    {
        printf("----> KEY_MUTE detected \n");
    }
}

static void
keyboard_handle_modifiers(void *data, struct wl_keyboard *keyboard,
              uint32_t serial, uint32_t mods_depressed,
              uint32_t mods_latched, uint32_t mods_locked,
              uint32_t group)
{
    printf("Modifiers depressed %d, latched %d, locked %d, group %d\n",
        mods_depressed, mods_latched, mods_locked, group);
}

static const struct wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_key,
    keyboard_handle_modifiers,
};

static void seat_handle_capabilities(void *data, struct wl_seat *seat,
             enum wl_seat_capability caps)
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
static void dummy(void *data,
                     struct wl_seat *wl_seat,
                     const char *name)
{

}
static void dummy1(void *data, struct wl_seat *seat,
             unsigned int caps)
{
     enum wl_seat_capability l_eWl_Seat = (wl_seat_capability)caps;
    seat_handle_capabilities(data, seat, l_eWl_Seat);
}

//static const struct wl_seat_listener seat_listener = {
//    seat_handle_capabilities,
//};
static const struct wl_seat_listener seat_listener = {
    dummy1, dummy

};


static void registry_handle_global(void *data, struct wl_registry *registry,
               uint32_t name, const char *interface, uint32_t version)
{
    printf("registry_handle_global ----------------------%s\n",interface);
    #if 1
    struct display *d = (struct display *)data;

    if (strcmp(interface, "wl_compositor") == 0) {
        d->compositor =
            (wl_compositor *)(wl_registry_bind(registry, name,
                     &wl_compositor_interface, 1));

    } 
    else if (strcmp(interface, "wl_seat") == 0) {
        d->seat = (wl_seat*)(wl_registry_bind(registry, name,
                       &wl_seat_interface, 1));

        wl_seat_add_listener(d->seat, &seat_listener, d);
    } else if (strcmp(interface, "wl_shm") == 0) {
        d->shm = (wl_shm*)(wl_registry_bind(registry, name,
                      &wl_shm_interface, 1));

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
    }
    #endif
}

static void
registry_handle_global_remove(void *data, struct wl_registry *registry,
                  uint32_t name)
{
}

static const struct wl_registry_listener registry_listener = {
    registry_handle_global,
    registry_handle_global_remove
};
#if 0
static void
usage(int error_code)
{
    fprintf(stderr, "Usage: simple-egl [OPTIONS]\n\n"
        "  -f\tRun in fullscreen mode\n"
        "  -o\tCreate an opaque surface\n"
        "  -s\tUse a 16 bpp EGL config\n"
        "  -b\tDon't sync to compositor redraw (eglSwapInterval 0)\n"
        "  -h\tThis help text\n\n");

    exit(error_code);
}
#endif
struct display display = { 0 };
struct window  window  = { 0 };

GlShell::GlShell()
{
window_shell=&window;
}


GlShell::~GlShell()
{

  fprintf(stderr, "simple-egl exiting\n");
    
#ifdef LM_SUPPORT
    ilm_surfaceRemoveNotification(ilmSurfaceId);
    ilm_commitChanges();
    
    if (ilmSurfaceId > 0)
        ilm_surfaceRemove(ilmSurfaceId);
    
    //if(ilmLayerId > 0)
        //ilm_layerRemove(ilmLayerId);
    
    ilmClient_destroy(); //disable for ILM 1.4.0
    ilm_destroy();
#endif 

    destroy_surface(&window);
    fini_egl(&display);

    wl_surface_destroy(display.cursor_surface);
    if (display.cursor_theme)
        wl_cursor_theme_destroy(display.cursor_theme);
    if (display.compositor)
        wl_compositor_destroy(display.compositor);

    wl_registry_destroy(display.registry);
    wl_display_flush(display.display);
    wl_display_disconnect(display.display);

}

bool GlShell::InitView(int screenWidth, int screenHeight, const char *carBuffer2, int textWidth, int texHeight)
{
    if(ReadShellConfig(CFG_PATH))
    {
	    InitEnV(screenWidth,screenHeight);
	    LoadShaders();
	    glGenTextures(1, &m_uiTexture);
	    glBindTexture(GL_TEXTURE_2D, m_uiTexture);
		GenCarTexture(carBuffer2, textWidth, texHeight);
		GenWarningTexture(textWidth, texHeight);
	    glViewport(0, 0,screenWidth, screenHeight);
	    //to make surface working??
	    eglSwapBuffers(display.egl.dpy, window.egl_surface);
	    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	    glDisable(GL_DEPTH_TEST);
	    //printf("------> eglSwapBuffers Finish %x %x\n",display.egl.dpy, window.egl_surface);
	    return false;
    } 
	else
    {   
        printf("InitView is Failed\n");
        return true;
    }
}

void GlShell::InitEnV(int screenWidth, int screenHeight)
{
    window.display = &display;
    display.window = &window;
    window.geometry.width  = screenWidth;
    window.geometry.height = screenHeight;
    window.window_size = window.geometry;
    window.buffer_size = 32;
    window.frame_sync = 1;



    display.display = wl_display_connect(NULL);
    //printf("display.display[%x]\n",display.display);
    assert(display.display);

    display.registry = wl_display_get_registry(display.display);
    //printf("display.registry[%x]\n",display.registry);
    wl_registry_add_listener(display.registry,
                 &registry_listener, &display);

    wl_display_dispatch(display.display);

    init_egl(&display, &window);
    create_surface(&window);
    //init_gl(&window);
    //printf("------> init_gl Finish \n");
    display.cursor_surface =
        wl_compositor_create_surface(display.compositor);
    //printf("display.cursor_surface[%x]\n",display.cursor_surface);

    
#ifdef LM_SUPPORT
    create_ilm_surface(&display);
#endif

}

const char* pAntiAliasedLineVertShader2 = "\
                                         attribute mediump vec4 myVert;\
                                         attribute mediump vec4 myUV;\
                                         uniform mediump vec2 imgSize;\
                                         varying mediump vec2 texCoord;\
                                         void main()\
                                         {\
                                         float x = 2.0*myVert.x/imgSize.x-1.0;\
                                         float y = 2.0 * myVert.y/imgSize.y - 1.0;\
                                         gl_Position = vec4(x,y,0.0,1.0);\
                                         texCoord = myUV.st;\
                                         }";

const char* pAntiAliasedLineFragShader2 = "\
                                         uniform lowp sampler2D tex;\
                                         uniform lowp sampler2D car;\
                                         uniform lowp sampler2D warning;\
                                         varying mediump vec2 texCoord;\
                                         void main()\
                                         {\
										 vec4 baseColor;\
										 vec4 lightColor;\
										 vec4 warningColor;\
										 baseColor = texture2D(car, texCoord);\
										 lightColor = texture2D(tex, texCoord);\
										 warningColor = texture2D(warning, texCoord);\
										 gl_FragColor = lightColor * (1.0 - baseColor.a) + baseColor;\
										 gl_FragColor = gl_FragColor * (1.0 - warningColor.a) + warningColor;\
                                         }";
										 //gl_FragColor = texture2D(tex, texCoord) + texture2D(car, texCoord);\

void GlShell::LoadShaders()
{
    GLuint pid = glCreateProgram();
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glAttachShader(pid, vertex_shader);
    glShaderSource(vertex_shader, 1, (const char**)&pAntiAliasedLineVertShader2, NULL);
    glCompileShader(vertex_shader);
    glDeleteShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glAttachShader(pid, fragment_shader);
    glShaderSource(fragment_shader, 1, (const char**)&pAntiAliasedLineFragShader2, NULL);
    glCompileShader(fragment_shader);
    glDeleteShader(fragment_shader);
    glBindAttribLocation(pid, 0, "myVert");
    glBindAttribLocation(pid, 1, "myUV");

    glLinkProgram(pid);
    glUseProgram(pid);
    m_RenderObj.uiId = pid;
    m_RenderObj.uiImgSize = glGetUniformLocation(m_RenderObj.uiId,"imgSize");
	//m_RenderObj.uiCarSize = glGetUniformLocation(m_RenderObj.uiId,"imgSize");
    //glUniform1i(glGetUniformLocation(m_RenderObj.uiId,"tex"),0);
	m_RenderObj.uiTxtLoc = glGetUniformLocation(m_RenderObj.uiId, "tex");
	m_RenderObj.uiCarLoc = glGetUniformLocation(m_RenderObj.uiId, "car");
	m_RenderObj.uiWarningLoc = glGetUniformLocation(m_RenderObj.uiId, "warning");
}

void GlShell::GenCarTexture(const char *buffer, int textWidth, int texHeight)
{
	glGenTextures(1, &m_uiCarTexture);
	glBindTexture(GL_TEXTURE_2D, m_uiCarTexture);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void GlShell::GenWarningTexture(int textWidth, int texHeight)
{
	glGenTextures(1, &m_uiWarningTexture);
	glBindTexture(GL_TEXTURE_2D, m_uiWarningTexture);
}

bool GlShell:: ReadShellConfig(const char* cfgfilepath)
{
    cout<<"Read Shell Config File!"<<endl;
    fstream cfgFile;
    cfgFile.open(cfgfilepath, std::fstream::in);//OpenFiles
    if( ! cfgFile.is_open())
    {
        cout<<"can not open cfg file!"<<endl;
        return false;
    }
	PDCL_LOG_INFO("GlShell : ReadShellConfig File open is success\n");
    char tmp[1000];
    int lineNum = 0;
    size_t notePos,assignmentPos;

    while(!cfgFile.eof())//read line
    {
        cfgFile.getline(tmp,200);

        string line(tmp);
        //cout<< lineNum<<endl;
        lineNum++;
        // fine note line and blank line
        notePos = line.find('#');

        if(notePos==string::npos ) {
            assignmentPos = line.find('=');//find '='
            if ( assignmentPos==string::npos)
            {
                ;
            } else
            {
                string tmpKey = line.substr(0,assignmentPos-1);
                string value;
               
                if(tmpKey == "ilmLayerId")
                {
                    value = line.substr(assignmentPos+2);//
                    ilmLayerId = (t_ilm_layer)atoi(value.c_str());
                    cout<< "ilmLayerId is______________"<<ilmLayerId<<endl;
                }
                else if(tmpKey == "ilmSurfaceId")
                {
                    value = line.substr(assignmentPos+2);//
                    ilmSurfaceId = (t_ilm_surface)atoi(value.c_str());
                    cout<< "ilmSurfaceId is _____________"<<ilmSurfaceId<<endl;
                }

            }

        } else
        {
            //cout<< "note line"<<endl;
        }
    }
	if(cfgFile.is_open())
    {
		PDCL_LOG_INFO("GlShell ReadShellConfig File Close is success\n");
        cfgFile.close();
    }
    return true;

}

