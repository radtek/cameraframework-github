#include "AGraphic.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AGraphics{

struct display AGraphic::m_Display = { 0 };
struct window  AGraphic::m_Window = { 0 };

AGraphic* AGraphic::getInstance(int width, int height)
{
	static AGraphic instance{width, height};
	return &instance;
}

AGraphic::AGraphic(int width, int height)
{
	m_Window.display = &m_Display;
	m_Display.window = &m_Window;
	m_Window.geometry.width = width;
	m_Window.geometry.height = height;

	m_Window.window_size = m_Window.geometry;
	m_Window.buffer_size = 32;
	m_Window.frame_sync = 1;
	m_Window.delay = 0;

	m_Display.display = wl_display_connect(NULL);
	assert(m_Display.display);
	m_Display.registry = wl_display_get_registry(m_Display.display);
	wl_registry_add_listener(m_Display.registry, &registry_listener, &m_Display);
	wl_display_roundtrip(m_Display.display);

};

AGraphic::~AGraphic()
{
	destroy_surface(&m_Window);
	release_egl(&m_Display);

	if (m_Display.ivi_application)
		ivi_application_destroy(m_Display.ivi_application);

	if (m_Display.compositor)
		wl_compositor_destroy(m_Display.compositor);

	wl_display_flush(m_Display.display);
	wl_display_disconnect(m_Display.display);

	glDeleteTextures(1, &textureYId);
	glDeleteTextures(1, &textureUId);
	glDeleteTextures(1, &textureVId);

	glDeleteProgram(programObject);

};

void AGraphic::release_egl(struct display *display)
{
	eglTerminate(display->egl.dpy);
	eglReleaseThread();
}

void AGraphic::destroy_surface(struct window *window)
{
	eglMakeCurrent(window->display->egl.dpy, EGL_NO_SURFACE, EGL_NO_SURFACE,
		EGL_NO_CONTEXT);

	weston_platform_destroy_egl_surface(window->display->egl.dpy,
		window->egl_surface);
	wl_egl_window_destroy(window->native);

	if (window->display->ivi_application)
		ivi_surface_destroy(window->ivi_surface);
	wl_surface_destroy(window->surface);

	if (window->callback)
		wl_callback_destroy(window->callback);
}


void AGraphic::Init()
{

	init_egl(&m_Display, &m_Window);

	init_gl();

}

void AGraphic::init_egl(struct display *display, struct window *window)
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

	display->egl.ctx = eglCreateContext(display->egl.dpy, display->egl.conf, EGL_NO_CONTEXT, context_attribs);
	assert(display->egl.ctx);

	display->swap_buffers_with_damage = NULL;
	extensions = eglQueryString(display->egl.dpy, EGL_EXTENSIONS);
	if (extensions &&
		weston_check_egl_extension(extensions, "EGL_EXT_buffer_age")) {
		for (i = 0; i < (int)ARRAY_LENGTH(swap_damage_ext_to_entrypoint); i++) {
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

	window->surface = wl_compositor_create_surface(display->compositor);

	window->native = wl_egl_window_create(window->surface, window->geometry.width, window->geometry.height);

	window->egl_surface = weston_platform_create_egl_surface(display->egl.dpy, display->egl.conf, window->native, NULL);

	create_ivi_surface(window, display);

	ret = eglMakeCurrent(window->display->egl.dpy, window->egl_surface,
		window->egl_surface, window->display->egl.ctx);
	assert(ret == EGL_TRUE);

	if (!window->frame_sync)
		eglSwapInterval(display->egl.dpy, 0);

	if (!display->shell)
		return;

}

void AGraphic::init_gl()
{
	GLbyte vShaderStr[] =
		"attribute vec4 vertexIn; \n"
		"attribute vec2 textureIn; \n"
		"varying vec2 textureOut; \n"
		"void main(void) \n"
		"{ \n"
		" gl_Position = vertexIn;  \n"
		" textureOut = textureIn; \n"
		"} \n";
	GLbyte fShaderStr[] =
		"precision mediump float;                          \n"
		"varying vec2 textureOut;                          \n"
		"uniform sampler2D tex_y;                            \n"
		"uniform sampler2D tex_u;                        \n"
		"uniform sampler2D tex_v;                    \n"
		"void main(void)                                         \n"
		"{                                                   \n"
		"  vec3 yuv;                               \n"
		"  vec3 rgb;                                \n"
		"                                                    \n"
		"  yuv.x = texture2D(tex_y, textureOut).r;   \n"
		"  yuv.y = texture2D(tex_u, textureOut).r - 0.5;   \n"
		"  yuv.z = texture2D(tex_v, textureOut).r - 0.5;   \n"
		"  rgb = mat3(1.0, 1.0, 1.0, 0.0, -0.337633, 1.732446, 1.370705, -0.698001, 0.0) * yuv;  \n"
		"  gl_FragColor = vec4(rgb, 1.0);  \n "
		"}                                                   \n";



	programObject = esLoadProgram((const char *)vShaderStr, (const char *)fShaderStr);

	positionLoc = glGetAttribLocation(programObject, "vertexIn");
	texCoordLoc = glGetAttribLocation(programObject, "textureIn");

	glUseProgram(programObject);

	textureUniformY = glGetUniformLocation(programObject, "tex_y");
	textureUniformU = glGetUniformLocation(programObject, "tex_u");
	textureUniformV = glGetUniformLocation(programObject, "tex_v");

	static const GLfloat vertexVertices[] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f,  1.0f,
		1.0f,  1.0f,
	};
	static const GLfloat textureVertices[] = {
		0.0f,  1.0f,//TR
		1.0f,  1.0f,//BR
		0.0f,  0.0f,//BL
		1.0f,  0.0f,//TL
	};

	glVertexAttribPointer(positionLoc, 2, GL_FLOAT, 0, 0, vertexVertices);
	glEnableVertexAttribArray(positionLoc);

	glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, 0, 0, textureVertices);
	glEnableVertexAttribArray(texCoordLoc);

	glGenTextures(1, &textureYId);
	glBindTexture(GL_TEXTURE_2D, textureYId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenTextures(1, &textureUId);
	glBindTexture(GL_TEXTURE_2D, textureUId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenTextures(1, &textureVId);
	glBindTexture(GL_TEXTURE_2D, textureVId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

GLuint AGraphic::esLoadProgram(const char *vertShaderSrc, const char *fragShaderSrc)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObjectTmp;
	GLint linked;

	vertexShader = loadShader(GL_VERTEX_SHADER, vertShaderSrc);
	if (vertexShader == 0)
		return 0;

	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragShaderSrc);
	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return 0;
	}

	programObjectTmp = glCreateProgram();

	if (programObjectTmp == 0)return 0;

	glAttachShader(programObjectTmp, vertexShader);
	glAttachShader(programObjectTmp, fragmentShader);

	glLinkProgram(programObjectTmp);

	glGetProgramiv(programObjectTmp, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(programObjectTmp, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetProgramInfoLog(programObjectTmp, infoLen, NULL, infoLog);

			printf("PROGRAM: %s\n", infoLog);
			free(infoLog);
		}

		glDeleteProgram(programObjectTmp);
		return 0;
	}


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return programObjectTmp;
}

GLuint AGraphic::loadShader(GLenum type, const char *shaderSrc)
{
	GLuint shader;
	GLint compiled;
	shader = glCreateShader(type);
	if (shader == 0) {
		return 0;
	}

	glShaderSource(shader, 1, &shaderSrc, NULL);

	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			char* infoLog = static_cast<char*>(malloc(sizeof(char) * infoLen));
			if (infoLog != NULL) {
				glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
				printf("SHADER %d: %s\n", type, infoLog);
				free(infoLog);
			}
		}
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}


void AGraphic::Display(void* Src)
{
	draw(Src);

	if (m_Window.wait_for_configure) {
		wl_display_dispatch(m_Display.display);
	}
	else {
		wl_display_dispatch_pending(m_Display.display);
		show(&m_Window);
	}
}


void AGraphic::draw(void* Src)
{

	BYTE* _buffer = (BYTE*)Src;
	int lenth = m_Window.geometry.width * m_Window.geometry.height * 2;
	BYTE* m_TmpBuffer = (BYTE*)malloc(lenth);
	int i = 0;
	int j = i + m_Window.geometry.width * m_Window.geometry.height;
	int k = j + ((m_Window.geometry.width * m_Window.geometry.height) >> 1);
	for (int l = 0; l < lenth; l++)
	{
		if (l % 4 == 0 || l % 4 == 2) { m_TmpBuffer[i] = _buffer[l]; i++;}
		if (l % 4 == 1) { m_TmpBuffer[j] = _buffer[l]; j++; }
		if (l % 4 == 3) { m_TmpBuffer[k] = _buffer[l]; k++; }
	}

	glLinkProgram(programObject);
	glUseProgram(programObject);

	glViewport(0, 0, m_Window.geometry.width, m_Window.geometry.height);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureYId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_Window.geometry.width, m_Window.geometry.height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, m_TmpBuffer);
	glUniform1i(textureUniformY, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureUId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_Window.geometry.width / 2, m_Window.geometry.height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, m_TmpBuffer+m_Window.geometry.width*m_Window.geometry.height);
	glUniform1i(textureUniformU, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureVId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_Window.geometry.width / 2, m_Window.geometry.height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, m_TmpBuffer+ m_Window.geometry.width*m_Window.geometry.height+((m_Window.geometry.width*m_Window.geometry.height)>>1));
	glUniform1i(textureUniformV, 2);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	if (m_TmpBuffer) free(m_TmpBuffer);
}

void AGraphic::show(struct window *window)
{
	struct display *display = window->display;
	eglSwapBuffers(display->egl.dpy, window->egl_surface);
}

struct wl_registry_listener AGraphic::registry_listener = {
		registry_handle_global,
		registry_handle_global_remove
};

struct ivi_surface_listener AGraphic::ivi_surface_listener = {
		handle_ivi_surface_configure,
};

void AGraphic::registry_handle_global(void *data, struct wl_registry *registry,uint32_t name, const char *interface, uint32_t version)
{
	struct display *d = (struct display *)data;

	if (strcmp(interface, "wl_compositor") == 0) {
		d->compositor =
			(wl_compositor*)wl_registry_bind(registry, name,
				&wl_compositor_interface,
				MIN(version, 4));
	}

	else if (strcmp(interface, "ivi_application") == 0) {
		d->ivi_application =
			(ivi_application*)wl_registry_bind(registry, name,
				&ivi_application_interface, 1);
	}
}

void AGraphic::registry_handle_global_remove(void *data, struct wl_registry *registry,uint32_t name)
{
}

void AGraphic::handle_ivi_surface_configure(void *data, struct ivi_surface *ivi_surface,int32_t width, int32_t height)
{
	struct window *window = (struct window *)data;

	wl_egl_window_resize(window->native, width, height, 0, 0);

	window->geometry.width = width;
	window->geometry.height = height;

	if (!window->fullscreen)
		window->window_size = window->geometry;
}

void AGraphic::create_ivi_surface(struct window *window, struct display *display)
{
	uint32_t id_ivisurf = IVI_SURFACE_ID + (uint32_t)getpid();
	window->ivi_surface =
		ivi_application_surface_create(display->ivi_application,
			id_ivisurf, window->surface);

	if (window->ivi_surface == NULL) {
		fprintf(stderr, "Failed to create ivi_client_surface\n");
		abort();
	}

	ivi_surface_add_listener(window->ivi_surface,&ivi_surface_listener, window);
}




}//namespace AGraphics
}//namespace AFramework
}//namespace Adas
}//namespace Harman
