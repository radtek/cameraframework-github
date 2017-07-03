#include "GlShell.h"
#include "fileloader.h"
#include <time.h>

#define VERTEX_ARRAY	0
#define TEXCOORD_ARRAY	1
#define AXIS_ALIGNED_QUAD_VERTEX_ARRAY   0
#define AXIS_ALIGNED_QUAD_TEXCOORD_ARRAY 1

//static struct timespec rt;
#define BILLION             1000000000L


GlShellApp::GlShellApp()
{
	m_typeId = 0;
}

GlShellApp::~GlShellApp()
{
}

int GlShellApp::ShellAppInit(int param1, int param2, void* pContext,void* pScreenCtx)
{
	m_screenWidth = param1;
    m_screenHeight = param2;
    pDisplayContext	= pContext;
    pScreenContext = pScreenCtx;

    return Init();
}

int GlShellApp::Init()
{
	return 0;
}
int GlShellApp::Release()
{
	return 0;
}


int GlShellApp::Update(int param1, int param2)
{
	return 0;
}

int GlShellApp::Draw(PVRTMat4& view, PVRTMat4& proj)
{
	return 0;
}

bool GlShellApp::LoadTextures(CPVRTString* pErrorStr)
{
	return 1;
}

bool GlShellApp::LoadShaders(CPVRTString* pErrorStr)
{
	return 1;
}

bool GlShellApp::LoadMeshes(CPVRTString* pErrorStr)
{
	return 1;
}

GLuint GlShellApp::LoadShaderFromString(const char* pVtx,const char* pFrg,const char** const pszAttribs,const int i32NumAttribs)
{
	GLuint pid = glCreateProgram();

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glAttachShader(pid, vertex_shader);
    glShaderSource(vertex_shader, 1, (const char**)&pVtx, NULL);
    glCompileShader(vertex_shader);

	/* Test if compilation succeeded */
	GLint ShaderCompiled;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &ShaderCompiled);
	if (!ShaderCompiled)
	{
		printf("vertex shader compile failded!!!!\n");
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = (char*)malloc(i32InfoLogLength);
        glGetShaderInfoLog(vertex_shader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
        CPVRTString pReturnError = CPVRTString("Failed to compile shader: ") + pszInfoLog + "\n";
        printf("Vert error: %s", pReturnError.c_str());
		free(pszInfoLog);
		glDeleteShader(vertex_shader);
		return 0;
	}
	glDeleteShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glAttachShader(pid, fragment_shader);
    glShaderSource(fragment_shader, 1, (const char**)&pFrg, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &ShaderCompiled);
	if (!ShaderCompiled)
	{
		printf("frag shader compile failded!!!!\n");
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = (char*)malloc(i32InfoLogLength);
        glGetShaderInfoLog(fragment_shader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
        CPVRTString pReturnError = CPVRTString("Failed to compile shader: ") + pszInfoLog + "\n";
        printf("Frag error: %s", pReturnError.c_str());
		free(pszInfoLog);
		glDeleteShader(fragment_shader);
		return 0;
	}
	glDeleteShader(fragment_shader);

	for(int i=0;i<i32NumAttribs;i++)
		glBindAttribLocation(pid, i, pszAttribs[i]);
    glLinkProgram(pid);
    glUseProgram(pid);

    return pid;
}

//GLuint GlShellApp::LoadShaderFromBinFile(const char* pVtx,const char* pFrg,const char** const pszAttribs,const int i32NumAttribs)
//{
////	PVRTShaderLoadFromFile(
////	c_szVertShaderBinFile, c_szVertShaderSrcFile, GL_VERTEX_SHADER, GL_SGX_BINARY_IMG, &m_uiVertShader, pErrorStr);
////	PVRTShaderLoadBinaryFromMemory(ShaderFile.DataPtr(), ShaderFile.Size(), Type, Format, pObject, pReturnError)
//	CPVRTResourceFile vertShaderFile(pVtx);
//	GLuint vertexShader;
//	if(vertShaderFile.IsOpen())
//	{
//		vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	    GLint numFormats = 0;
//	    GLint *listFormats;
//	    int i;
//	    glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS,&numFormats);
//	    if(numFormats != 0) {
//	        listFormats = (GLint*)malloc(numFormats*sizeof(GLint));
//	        for(i=0;i<numFormats;++i)
//	            listFormats[i] = 0;
//	        glGetIntegerv(GL_SHADER_BINARY_FORMATS,listFormats);
//	        for(i=0;i<numFormats;++i) {
//	            if(listFormats[i] == GL_SGX_BINARY_IMG) {
//	                glShaderBinary(1, &vertexShader, GL_SGX_BINARY_IMG, vertShaderFile.DataPtr(), vertShaderFile.Size());
//	                if (glGetError() != GL_NO_ERROR)
//	                {
//	                    printf("Failed to load vertex binary shader\n");
//	                    glDeleteShader(vertexShader);
//	                    return 1;
//	                }
//	                return 0;
//	            }
//	        }
//	        free(listFormats);
//	    }
//	    printf("Failed to load vertex binary shader\n");
//	    glDeleteShader(vertexShader);
//	}
//
//	CPVRTResourceFile fragShaderFile(pFrg);
//	GLuint fragmentShader;
//	if(fragShaderFile.IsOpen())
//	{
//		fragmentShader = glCreateShader(GL_VERTEX_SHADER);
//	    GLint numFormats = 0;
//	    GLint *listFormats;
//	    int i;
//	    glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS,&numFormats);
//	    if(numFormats != 0) {
//	        listFormats = (GLint*)malloc(numFormats*sizeof(GLint));
//	        for(i=0;i<numFormats;++i)
//	            listFormats[i] = 0;
//	        glGetIntegerv(GL_SHADER_BINARY_FORMATS,listFormats);
//	        for(i=0;i<numFormats;++i) {
//	            if(listFormats[i] == GL_SGX_BINARY_IMG) {
//	                glShaderBinary(1, &fragmentShader, GL_SGX_BINARY_IMG, fragShaderFile.DataPtr(), fragShaderFile.Size());
//	                if (glGetError() != GL_NO_ERROR)
//	                {
//	                    printf("Failed to load fragment binary shader\n");
//	                    glDeleteShader(fragmentShader);
//	                    return 1;
//	                }
//	                return 0;
//	            }
//	        }
//	        free(listFormats);
//	    }
//	    printf("Failed to load fragment binary shader\n");
//	    glDeleteShader(fragmentShader);
//	}
//	GLuint pid = glCreateProgram();
//	glAttachShader(pid, vertexShader);
//	glAttachShader(pid, fragmentShader);
//	for(int i=0;i<i32NumAttribs;i++)
//		glBindAttribLocation(pid, i, pszAttribs[i]);
//    glLinkProgram(pid);
//    glUseProgram(pid);
//
//    return pid;
//}
void LoadShaderFromFile(char* vtxName, char* frgName)
{

}
int GlShellApp::LoadProgramFromFile(char* vtxName, char* frgName)
{
#if 0
	char *vtx_shader, *frg_shader;

	LoadShaderFromFile(vtxName, &vtx_shader);
	LoadShaderFromFile(frgName, &frg_shader);

//	printf("%s\n",vtx_shader);
//	printf("%s\n",frg_shader);

	int pid = glCreateProgram();

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glAttachShader(pid, vertex_shader);
    glShaderSource(vertex_shader, 1, (const char**)&vtx_shader, NULL);
    glCompileShader(vertex_shader);

	/* Test if compilation succeeded */
	GLint ShaderCompiled;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &ShaderCompiled);
	if (!ShaderCompiled)
	{
		printf("%s vertex shader compile failded!!!!\n", vtxName);
	}
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glAttachShader(pid, fragment_shader);
    glShaderSource(fragment_shader, 1, (const char**)&frg_shader, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &ShaderCompiled);
	if (!ShaderCompiled)
	{
		printf("%s frag shader compile failded!!!!\n", frgName);
	}
    glLinkProgram(pid);
    glUseProgram(pid);

//	glDeleteShader(vertex_shader);
//	glDeleteShader(fragment_shader);

    if (vtx_shader) free(vtx_shader);
    if (frg_shader) free(frg_shader);

    return pid;
#endif
	return 1;
}

//
///*
// * 'read_word()' - Read a 16-bit unsigned integer.
// */
//
//static unsigned short     /* O - 16-bit unsigned integer */
//read_word(FILE *fp)       /* I - File to read from */
//    {
//    unsigned char b0, b1; /* Bytes from file */
//
//    b0 = getc(fp);
//    b1 = getc(fp);
//
//    return ((b1 << 8) | b0);
//    }
//
//
///*
// * 'read_dword()' - Read a 32-bit unsigned integer.
// */
//
//static unsigned int               /* O - 32-bit unsigned integer */
//read_dword(FILE *fp)              /* I - File to read from */
//    {
//    unsigned char b0, b1, b2, b3; /* Bytes from file */
//
//    b0 = getc(fp);
//    b1 = getc(fp);
//    b2 = getc(fp);
//    b3 = getc(fp);
//
//    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
//    }
//
//
///*
// * 'read_long()' - Read a 32-bit signed integer.
// */
//
//static int                        /* O - 32-bit signed integer */
//read_long(FILE *fp)               /* I - File to read from */
//    {
//    unsigned char b0, b1, b2, b3; /* Bytes from file */
//
//    b0 = getc(fp);
//    b1 = getc(fp);
//    b2 = getc(fp);
//    b3 = getc(fp);
//
//    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
//    }


//unsigned char *                          /* O - Bitmap data */
//LoadDIBitmap(const char *filename, /* I - File to load */
//             BITMAPINFO **info)    /* O - Bitmap information */
//    {
//    FILE             *fp;          /* Open file pointer */
//    unsigned char          *bits;        /* Bitmap pixel bits */
//    unsigned char          *ptr;         /* Pointer into bitmap */
//    unsigned char          temp;         /* Temporary variable to swap red and blue */
//    int              x, y;         /* X and Y position in image */
//    int              length;       /* Line length */
//    int              bitsize;      /* Size of bitmap */
//    int              infosize;     /* Size of header information */
//    BITMAPFILEHEADER header;       /* File header */
//
//
//    /* Try opening the file; use "rb" mode to read this *binary* file. */
//    if ((fp = fopen(filename, "rb")) == NULL)
//    {
//    	printf("open file failed!\n");
//        return (NULL);
//    }
//
//    /* Read the file header and any following bitmap information... */
//    header.bfType      = read_word(fp);
//    header.bfSize      = read_dword(fp);
//    header.bfReserved1 = read_word(fp);
//    header.bfReserved2 = read_word(fp);
//    header.bfOffBits   = read_dword(fp);
//
//    if (header.bfType != BF_TYPE) /* Check for BM reversed... */
//        {
//        /* Not a bitmap file - return NULL... */
//    	printf("not a bitmap file!\n");
//        fclose(fp);
//        return (NULL);
//        }
//
//    infosize = header.bfOffBits - 18;
//    if ((*info = (BITMAPINFO *)malloc(sizeof(BITMAPINFO))) == NULL)
//        {
//        /* Couldn't allocate memory for bitmap info - return NULL... */
//    	printf("Couldn't allocate memory for bitmap info\n");
//        fclose(fp);
//        return (NULL);
//        }
//
//    (*info)->bmiHeader.biSize          = read_dword(fp);
//    (*info)->bmiHeader.biWidth         = read_long(fp);
//    (*info)->bmiHeader.biHeight        = read_long(fp);
//    (*info)->bmiHeader.biPlanes        = read_word(fp);
//    (*info)->bmiHeader.biBitCount      = read_word(fp);
//    (*info)->bmiHeader.biCompression   = read_dword(fp);
//    (*info)->bmiHeader.biSizeImage     = read_dword(fp);
//    (*info)->bmiHeader.biXPelsPerMeter = read_long(fp);
//    (*info)->bmiHeader.biYPelsPerMeter = read_long(fp);
//    (*info)->bmiHeader.biClrUsed       = read_dword(fp);
//    (*info)->bmiHeader.biClrImportant  = read_dword(fp);
//
//    if (infosize > 40)
//	if (fread((*info)->bmiColors, infosize - 40, 1, fp) < 1)
//            {
//            /* Couldn't read the bitmap header - return NULL... */
//		    printf("Couldn't read the bitmap header\n");
//            free(*info);
//            fclose(fp);
//            return (NULL);
//            }
//
//    /* Now that we have all the header info read in, allocate memory for *
//     * the bitmap and read *it* in...                                    */
//    if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
//        bitsize = ((*info)->bmiHeader.biWidth *
//                   (*info)->bmiHeader.biBitCount + 7) / 8 *
//  	           abs((*info)->bmiHeader.biHeight);
//
//    if ((bits = (unsigned char*)malloc(bitsize)) == NULL)
//        {
//        /* Couldn't allocate memory - return NULL! */
//    	printf("Couldn't allocate memory!\n");
//        free(*info);
//        fclose(fp);
//        return (NULL);
//        }
//
//    if (fread(bits, 1, bitsize, fp) < bitsize)
//        {
//        /* Couldn't read bitmap - free memory and return NULL! */
//    	printf("Couldn't read bitmap!\n");
//        free(*info);
//        free(bits);
//        fclose(fp);
//        return (NULL);
//        }
//
//    /* Swap red and blue */
//    length = ((*info)->bmiHeader.biWidth * 3 + 3) & ~3;
//    for (y = 0; y < (*info)->bmiHeader.biHeight; y ++)
//        for (ptr = bits + y * length, x = (*info)->bmiHeader.biWidth;
//             x > 0;
//	     x --, ptr += 3)
//	    {
//	    temp   = ptr[0];
//	    ptr[0] = ptr[2];
//	    ptr[2] = temp;
//	    }
//
//    /* OK, everything went fine - return the allocated bitmap... */
//    fclose(fp);
//
//    return (bits);
//    }


int GlShellApp::LoadAlphaTextureFromBMP(const char* name, unsigned int* tid)
{
#if 0
	BITMAPINFO *maskBitmapInfo; /* Bitmap information */
	unsigned char    *maskBitmapBits; /* Bitmap data */
	maskBitmapBits = LoadDIBitmap(name, &maskBitmapInfo);

	glGenTextures(1, tid);
	glBindTexture(GL_TEXTURE_2D,*tid);
	int width, height,i;
	width=maskBitmapInfo->bmiHeader.biWidth;
	height=maskBitmapInfo->bmiHeader.biHeight;
//	printf("width = %d,height= %d\n",width, height);

	if (24 == maskBitmapInfo->bmiHeader.biBitCount) {
		unsigned char *temp=(unsigned char*)malloc(width*height);

		for(i=0;i<width*height;i++) {
			temp[i]=maskBitmapBits[i*3];
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp);
		free(temp);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//	printf("start!\n");
	if (maskBitmapInfo) {
		free(maskBitmapInfo);
		free(maskBitmapBits);
	}
//	printf("end!\n");
#endif
	printf("tbd: LoadAlphaTextureFromBMP!\n");
	return 0;
}

int GlShellApp::LoadAlphaTextureFromBMP(const char* name, unsigned int* tid, int& bmpWidth,int& bmpHeight)
{
#if 0
	BITMAPINFO *maskBitmapInfo; /* Bitmap information */
	unsigned char    *maskBitmapBits; /* Bitmap data */
	maskBitmapBits = LoadDIBitmap(name, &maskBitmapInfo);
	if(!maskBitmapBits)
		return -1;

	glGenTextures(1, tid);
	glBindTexture(GL_TEXTURE_2D,*tid);
	int width, height,i;
	width=maskBitmapInfo->bmiHeader.biWidth;
	height=maskBitmapInfo->bmiHeader.biHeight;
	bmpWidth = width;
	bmpHeight = height;

	if (24 == maskBitmapInfo->bmiHeader.biBitCount) {
		unsigned char *temp=(unsigned char*)malloc(width*height);

		for(i=0;i<width*height;i++) {
			temp[i]=maskBitmapBits[i*3];
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp);
		free(temp);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (maskBitmapInfo) {
		free(maskBitmapInfo);
		free(maskBitmapBits);
	}
#endif
	printf("tbd: LoadAlphaTextureFromBMP!\n");
	return 0;
}

int GlShellApp::LoadRGBTextureFromBMP(const char* name,unsigned int* tid)
{
#if 0
	BITMAPINFO *maskBitmapInfo; /* Bitmap information */
	unsigned char    *maskBitmapBits; /* Bitmap data */
	maskBitmapBits = LoadDIBitmap(name, &maskBitmapInfo);

	glGenTextures(1, tid);
	glBindTexture(GL_TEXTURE_2D,*tid);
	int width, height;
	width=maskBitmapInfo->bmiHeader.biWidth;
	height=maskBitmapInfo->bmiHeader.biHeight;

	if (24 == maskBitmapInfo->bmiHeader.biBitCount) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, maskBitmapBits);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

//	printf("start!\n");
	if (maskBitmapInfo) {
		free(maskBitmapInfo);
		free(maskBitmapBits);
	}
//	printf("end!\n");
#endif
printf("tbd: LoadRGBTextureFromBMP!\n");
	return 0;
}

int GlShellApp::PVRShellGet(const prefNameIntEnum prefName)
{
	switch(prefName)
	{
	case prefWidth:		return m_screenWidth;
	case prefHeight:	return m_screenHeight;
	default:
		{
			return -1;
		}
	}
}

unsigned long GlShellApp::PVRShellGetTime()
{
//	clock_gettime(CLOCK_REALTIME, &rt);
//	return rt.tv_sec * 1000 + rt.tv_nsec/1000000;
	return 1;
}

void GlShellApp::HandleInput()
{
//	static float dir=-0.01f;
//
//	m_scale += dir;
//
//	if (m_scale > 1.0f) {
//		m_scale = 1.0f;
//		dir = -dir;
//	}
//
//	if (m_scale < 0.00000f) {
//		m_scale = 0.00f;
//		dir = -dir;
//	}
}

void GlShellApp::DrawAxisAlignedQuad(PVRTVec2 afLowerLeft, PVRTVec2 afUpperRight)
{
	glDisable(GL_DEPTH_TEST);

	// Enable vertex arributes
	glEnableVertexAttribArray(AXIS_ALIGNED_QUAD_VERTEX_ARRAY);
	glEnableVertexAttribArray(AXIS_ALIGNED_QUAD_TEXCOORD_ARRAY);

	const float afVertexData[] = { afLowerLeft.x, afLowerLeft.y,  afUpperRight.x, afLowerLeft.y,
		                           afLowerLeft.x, afUpperRight.y,  afUpperRight.x, afUpperRight.y };
	glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 0, afVertexData);

	const float afTexCoordData[] = { 0, 0,  1, 0,  0, 1,  1, 1 };
	glVertexAttribPointer(TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, 0, afTexCoordData);

	// Draw the quad
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Disable vertex arributes
	glDisableVertexAttribArray(AXIS_ALIGNED_QUAD_VERTEX_ARRAY);
	glDisableVertexAttribArray(AXIS_ALIGNED_QUAD_TEXCOORD_ARRAY);

	// Disable blending
	glEnable(GL_DEPTH_TEST);
}

void GlShellApp::OnMouseDown(int x, int y)
{
}

void GlShellApp::OnMouseUp(int x, int y)
{

}

void GlShellApp::OnMouseMove(int x, int y)
{

}

void GlShellApp::OnKeyPressed(unsigned char keyCode)
{

}

void GlShellApp::OnKeyReleased(unsigned char keyCode)
{

}


void GlShellApp::setContinueDraw(int continueDraw)
{
	bContinueDraw = (bool)continueDraw;
}

bool GlShellApp::IsContinue2Draw()
{
//	printf("bContinueDraw = %d\n",bContinueDraw);
	return bContinueDraw;
}
