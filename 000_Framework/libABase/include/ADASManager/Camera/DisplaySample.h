

#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_DISPLAYSAMPLE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_DISPLAYSAMPLE_H__

#include "config.h"

#include <stdint.h>
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

#include "xdg-shell-unstable-v6-client-protocol.h"
#include <sys/types.h>
#include <unistd.h>
#include "ivi-application-client-protocol.h"
#define IVI_SURFACE_ID 9000

#include "shared/helpers.h"
#include "shared/platform.h"
#include "weston-egl-ext.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

struct window;
struct seat;

struct display {
	struct wl_display *display;
	struct wl_registry *registry;
	struct wl_compositor *compositor;
	struct zxdg_shell_v6 *shell;
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
	struct ivi_application *ivi_application;

	PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC swap_buffers_with_damage;
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
	struct zxdg_surface_v6 *xdg_surface;
	struct zxdg_toplevel_v6 *xdg_toplevel;
	struct ivi_surface *ivi_surface;
	EGLSurface egl_surface;
	struct wl_callback *callback;
	int fullscreen, opaque, buffer_size, frame_sync, delay;
	bool wait_for_configure;
};

class DisplaySample
{
public:
    DisplaySample();

    static int Start();

    ~DisplaySample();

    static void init_egl(struct display *display, struct window *window);

	static void fini_egl(struct display *display);

	static GLuint create_shader(struct window *window, const char *source, GLenum shader_type);

	static void init_gl(struct window *window);

	static void handle_surface_configure(void *data, struct zxdg_surface_v6 *surface, uint32_t serial);

	static void handle_toplevel_configure(void *data, struct zxdg_toplevel_v6 *toplevel, int32_t width, int32_t height, struct wl_array *states);

	static void handle_toplevel_close(void *data, struct zxdg_toplevel_v6 *xdg_toplevel);

	static void handle_ivi_surface_configure(void *data, struct ivi_surface *ivi_surface, int32_t width, int32_t height);

	static void create_xdg_surface(struct window *window, struct display *display);

	static void create_ivi_surface(struct window *window, struct display *display);

	static void create_surface(struct window *window);

	static void destroy_surface(struct window *window);

	static void redraw(void *data, struct wl_callback *callback, uint32_t time);

	static void pointer_handle_enter(void *data, struct wl_pointer *pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t sx, wl_fixed_t sy);

	static void pointer_handle_leave(void *data, struct wl_pointer *pointer, uint32_t serial, struct wl_surface *surface);

	static void pointer_handle_motion(void *data, struct wl_pointer *pointer, uint32_t time, wl_fixed_t sx, wl_fixed_t sy);

	static void pointer_handle_button(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state);

	static void pointer_handle_axis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value);

	static void touch_handle_down(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, struct wl_surface *surface, int32_t id, wl_fixed_t x_w, wl_fixed_t y_w);

	static void touch_handle_up(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, int32_t id);

	static void touch_handle_motion(void *data, struct wl_touch *wl_touch, uint32_t time, int32_t id, wl_fixed_t x_w, wl_fixed_t y_w);

	static void touch_handle_frame(void *data, struct wl_touch *wl_touch);

	static void touch_handle_cancel(void *data, struct wl_touch *wl_touch);

	static void keyboard_handle_keymap(void *data, struct wl_keyboard *keyboard, uint32_t format, int fd, uint32_t size);

	static void keyboard_handle_enter(void *data, struct wl_keyboard *keyboard, uint32_t serial, struct wl_surface *surface, struct wl_array *keys);

	static void keyboard_handle_leave(void *data, struct wl_keyboard *keyboard, uint32_t serial, struct wl_surface *surface);

	static void keyboard_handle_key(void *data, struct wl_keyboard *keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);

	static void keyboard_handle_modifiers(void *data, struct wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);

	static void seat_handle_capabilities(void *data, struct wl_seat *seat, /*enum wl_seat_capability*/ uint32_t caps);

	static void xdg_shell_ping(void *data, struct zxdg_shell_v6 *shell, uint32_t serial);

	static void registry_handle_global(void *data, struct wl_registry *registry, uint32_t name, const char *interface, uint32_t version);

	static void registry_handle_global_remove(void *data, struct wl_registry *registry, uint32_t name);

	static void signal_int(int signum);

	static void usage(int error_code);


private:
	static char *vert_shader_text;

	static char *frag_shader_text;

	static int running;

	static struct wl_registry_listener registry_listener;

	static struct zxdg_shell_v6_listener xdg_shell_listener;

	static struct wl_seat_listener seat_listener;

	static struct wl_keyboard_listener keyboard_listener;

	static struct wl_touch_listener touch_listener;

	static struct wl_pointer_listener pointer_listener;

	static struct ivi_surface_listener ivi_surface_listener;

	static struct zxdg_toplevel_v6_listener xdg_toplevel_listener;

	static struct zxdg_surface_v6_listener xdg_surface_listener;

};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_DISPLAYSAMPLE_H__
