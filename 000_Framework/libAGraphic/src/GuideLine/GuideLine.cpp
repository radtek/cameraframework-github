#include "GuideLine.h"


namespace Harman {
namespace Adas {
namespace AFramework {
namespace AGraphic {

GuideLine::GuideLine()
{
	if(calpointer==nullptr)
	{
		calpointer=new Calculator();
	}
	cameraPara_t camparam;
	        	camparam.intrinsic = {
	                    0.7,  //fx;
	                0.58,  //fy;
	                0.49,  //cx;
	                0.51,  //cy;
	                -0.42632,    //k1;
	                0.280939,    //k2;
	                    };
	        	camparam.extrinsic = {
	                    0.015,
	                -0.25,
	                0.738,
	                124.0,
	                -1,
	                -0.3
	                    };
		 float groupSeq[9 * 2]={
        			//start distance, end distance
		           0.0, 0.1,
		             0.15,0.2,//2 distLines
			0.3,0.55,//2 distLines
			0.65,0.95,
			1.15,1.45,
			1.55,1.80,
			1.95,2.25,
			2.35,2.65,
		             0,0//background 
            			};
        	color3 color[9]={ COLOR_PINK,COLOR_RED,COLOR_LIGNTBLUE,COLOR_YELLOW };
        	float tickLength[9] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

        	dynamic_para_t GUIDELINE_PARA={
              				0,
              			  	0,
                				3.5,
              				0.01,
                				0,
                				10
            					};
            	
	info.width=1280;
	info.height=720;
	info.startX=0;
	info.startY=0;
        	info.camparam=camparam;
        	info.groupSeq=groupSeq;
	info.color=color;
	info.tickLength=tickLength;
	info.GUIDELINE_PARA=GUIDELINE_PARA;
	calpointer->Init(info);
	GenTexture();
}

GuideLine::~GuideLine()
{
	glDeleteTextures(1, &GuideLineTexture);
	if(calpointer!=nullptr)
	{
		delete calpointer;
		calpointer=nullptr;
	}
}

void GuideLine::GuideLineRender(guidelineinfo infos)
{
	info.GUIDELINE_PARA=infos.GUIDELINE_PARA;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glViewport(info.startX,info.startY,info.width,info.height);
	
	calpointer->Update(info);
	
	LoadProgram();
		
	glUniform1i(glGetUniformLocation(programObject,"tex"),0);
	const char* Attribs[] = { "myVert","myUV" };
	for(int i=0;i<2;i++)
	{
		glBindAttribLocation(programObject, i, Attribs[i]);
	}
	
	glUseProgram(programObject);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GuideLineTexture);
	glUniform1f(glGetUniformLocation(programObject, "myAlpha"), 1);
	glUniform2f(glGetUniformLocation(programObject, "imgSize"), info.width - 1, info.height - 1);
	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(TEXCOORD_ARRAY);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		
	for (int i = 0; i < 8; i++)
	{
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, calpointer->LineTex_width, calpointer->LineTex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, calpointer->pTexData[i]);
		
		RenderGroupLines(i);
	}
	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(TEXCOORD_ARRAY);
	glDisable(GL_BLEND);
	
}

void GuideLine::GuideLineHide()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClearDepthf(1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glDisable(GL_DEPTH_TEST);
}

void GuideLine::GenTexture()
{
	glGenTextures(1, &GuideLineTexture);
	glBindTexture(GL_TEXTURE_2D, GuideLineTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	
}

void GuideLine::LoadProgram()
{
	const char* vertexShader = "\
	attribute mediump vec4 myVert;\
	attribute mediump vec4 myUV;\
	uniform mediump vec2 imgSize;\
	varying mediump vec2 texCoord;\
	void main()\
	{\
		float x = 2.0*myVert.x/imgSize.x-1.0;\
		float y = 2.0 * myVert.y/imgSize.y - 1.0;\
		gl_Position = vec4(x,-y,0.0,1.0);\
		texCoord = myUV.st;\
	}";

	const char* fragmentShader = "\
	uniform lowp sampler2D tex;\
	uniform mediump float myAlpha;\
	varying mediump vec2 texCoord;\
	void main()\
	{\
		gl_FragColor = vec4(texture2D(tex, texCoord).rgb,myAlpha);\
	}";

	programObject = LoadShaders(vertexShader,fragmentShader);	
	
}

GLuint GuideLine::LoadShaders(const char* vertexShaderSrc,const char* fragmentShaderSrc)
{
	GLuint programObjectTmp;
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLint linked;
	GLint ShaderCompiled;

	programObjectTmp=glCreateProgram();
	
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glAttachShader(programObjectTmp, vertex_shader);
	glShaderSource(vertex_shader, 1, (const char**)&vertexShaderSrc, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &ShaderCompiled);
	if (!ShaderCompiled)
	{
		printf("vertex shader compile failded!!!!\n");
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = (char*)malloc(i32InfoLogLength);
	        	glGetShaderInfoLog(vertex_shader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
	        	printf("Vert error:\n");
		free(pszInfoLog);
		glDeleteShader(vertex_shader);
		return 0;
	}
	glDeleteShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glAttachShader(programObjectTmp, fragment_shader);
	glShaderSource(fragment_shader, 1, (const char**)&fragmentShaderSrc, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &ShaderCompiled);
	if (!ShaderCompiled)
	{
		printf("frag shader compile failded!!!!\n");
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = (char*)malloc(i32InfoLogLength);
	        	glGetShaderInfoLog(fragment_shader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
	        	printf("Frag error:\n");
		free(pszInfoLog);
		glDeleteShader(fragment_shader);
		return 0;
	}
	glDeleteShader(fragment_shader);
	

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
	

	return programObjectTmp;
}

void GuideLine::RenderGroupLines(int index)
{
	linesData lineGroup = calpointer->m_pGroups[index];
	glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)lineGroup.pBorderData);
	glVertexAttribPointer(TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(&lineGroup.pBorderData[2]));
	glDrawElements(GL_TRIANGLES, lineGroup.pBorderIndexNum, GL_UNSIGNED_SHORT, lineGroup.pBorderIndex);
}







}//namespace AGraphic
}//namespace Adas 
}//namespace AFramework
}//namespace Harman
