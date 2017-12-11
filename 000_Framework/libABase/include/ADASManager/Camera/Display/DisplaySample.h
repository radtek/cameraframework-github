

#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_DISPLAYSAMPLE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_DISPLAYSAMPLE_H__

#include "external/config.h"

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

#include <sys/types.h>
#include <unistd.h>
#include "external/ivi-application-client-protocol.h"

#include "external/shared/helpers.h"
#include "external/shared/platform.h"
#include "external/shared/weston-egl-ext.h"

#include "AFoundation.h"

using namespace Harman::Adas::AFramework::AFoundation;
using namespace std;


namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

struct window;

struct display {
	struct wl_display *display;
	struct wl_registry *registry;
	struct wl_compositor *compositor;

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

    int Start();

    void Init();

    ~DisplaySample();

    void init_egl(struct display *display, struct window *window);

	void fini_egl(struct display *display);

	GLuint create_shader(struct window *window, const char *source, GLenum shader_type);


	void handle_ivi_surface_configure(void *data, struct ivi_surface *ivi_surface, int32_t width, int32_t height);

	void create_ivi_surface(struct window *window, struct display *display);

	void create_surface(struct window *window);

	void destroy_surface(struct window *window);

	void redraw(void *data, struct wl_callback *callback, uint32_t time);


	static void registry_handle_global(void *data, struct wl_registry *registry, uint32_t name, const char *interface, uint32_t version);
	static void registry_handle_global_remove(void *data, struct wl_registry *registry, uint32_t name);

	void signal_int(int signum);


private:
	char *vert_shader_text;
	char *frag_shader_text;

	static struct wl_registry_listener registry_listener;
	static struct ivi_surface_listener ivi_surface_listener;

	struct display m_Display;
	struct window  m_Window;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_DISPLAYSAMPLE_H__
