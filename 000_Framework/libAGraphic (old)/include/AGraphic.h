#ifndef __HARMAN_ADAS_AFRAMEWORK_AGRAPGIC_H_
#define __HARMAN_ADAS_AFRAMEWORK_AGRAPGIC_H_

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include "ivi-application-client-protocol.h"
#include "helpers.h"
#include "platform.h"
#include "weston-egl-ext.h"
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
#include <sys/types.h>
#include <unistd.h>

#define IVI_SURFACE_ID 9000
typedef unsigned char  BYTE;

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AGraphics {

struct window;
struct display;


class AGraphic
{
public:
	void Init();
	void Display(void* Src);
	static AGraphic* getInstance(int width, int height);

	AGraphic(const AGraphic&) = delete;
	AGraphic& operator=(const AGraphic&) = delete;

private:

	AGraphic(int width, int height);

	~AGraphic();

	void draw(void* Src);

	void show(struct window *window);

	void init_egl(struct display *display, struct window *window);

	void release_egl(struct display *display);

	void init_gl();

	GLuint esLoadProgram(const char *vertShaderSrc, const char *fragShaderSrc);

	GLuint loadShader(GLenum type, const char *shaderSrc);

	static void handle_ivi_surface_configure(void *data, struct ivi_surface *ivi_surface, int32_t width, int32_t height);

	static void create_ivi_surface(struct window *window, struct display *display);

    static void registry_handle_global(void *data, struct wl_registry *registry, uint32_t name, const char *interface, uint32_t version);

	static void registry_handle_global_remove(void *data, struct wl_registry *registry, uint32_t name);

 	static void destroy_surface(struct window *window);

private:

	GLuint programObject;
	GLint  positionLoc;
	GLint  texCoordLoc;
	GLint  textureUniformY;
	GLint  textureUniformU;
	GLint  textureUniformV;
	GLuint  textureYId;
	GLuint  textureUId;
	GLuint  textureVId;

 	static struct wl_registry_listener registry_listener;

	static struct ivi_surface_listener ivi_surface_listener;

	static struct display m_Display;

	static struct window  m_Window;

};

struct display {
	struct wl_display *display;
	struct wl_registry *registry;
	struct wl_compositor *compositor;
	struct zxdg_shell_v6 *shell;

	struct {
		EGLDisplay dpy;
		EGLContext ctx;
		EGLConfig conf;
	} egl;

	struct window *window;
	struct ivi_application *ivi_application;
	PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC swap_buffers_with_damage;
};

struct geometry
{
	int width, height;
};

struct window {
	struct display *display;
	struct geometry geometry, window_size;
	struct
	{
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


}//namespace AGraphics
}//namespace AFramework
}//namespace Adas
}//namespace Harman

#endif  //__HARMAN_ADAS_AFRAMEWORK_AGRAPGIC_H_
