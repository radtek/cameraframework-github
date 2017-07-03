/*
 * GlLineGroup.h
 *
 *  Created on: 2012-6-11
 *      Author: QiLiu
 */

#ifndef GLLINEGROUP_H_
#define GLLINEGROUP_H_

#include "GlShell.h"
#include "LCommon.h"
#include "lineBorderOp.h"
#include "trajectory.h"
#include "RVSDefine.h"

typedef float color3[3];

//two side line + five diatance line
//two groups: L segment lines and normal guide lines

//define the side line info struct
typedef struct _linesData{
	int lineNums;  //two side lines and five distance mark lines = 7
	int* pLinePtNums; //num of veterx on a segment of side line or a  mark distance line
	float** pLineData;  //coordinate of the veterx on a segment of side line(save in first and second pLineData) or distance line(save in last 5 pLineData)
//	float** pLineBorderData;
//	unsigned short** pLineBorderIndex;
//	unsigned short* pLineBorderIndexNum;

	unsigned short* pLinePtElemStartNum;//used for pBorderData[pLinePtElemStartNum];
	unsigned short* pLineIndexElemStartNum;//used for pBorderIndex[pLineIndexElemStartNum];
	unsigned short* pLineBorderStartIndex;//startIndex of each line in pBorderIndex;--->stride = PTELEMNUM = 4

	float* pBorderData;//two for vertex and two for TEXCOORD,so stride is 4
	unsigned short* pBorderIndex;
	unsigned short pBorderIndexNum;
	unsigned short pBorderPtElemNum;
	color3 color;
}linesData;


class GlLineGroup: public GlShellApp
{
public:
	GlLineGroup();
	~GlLineGroup();

	void InitView();
	void Render(PVRTMat4& mat);
	void RenderTest(PVRTMat4& mat);
	
protected:
	void FreeLinesData();
	void Shutdown();

private:
	void FreeGroupData(int index);
	void RenderGroupLines(int index);
	void RenderLinesTest(int index);
	
	void RenderGroupLines_new(int index);
	void LoadShaders();
	void LoadTextures();

private:
	struct{
		GLuint uiId;
		GLuint uiColor;
		GLuint uiImgSize;
//		GLuint uiMVP;

		GLuint uiSourcePosition;
	}m_RenderObj;
	GLuint m_uiTexture;

protected:
	linesData* m_pGroups;//save info from side line and distance mark line according groups
	int m_iGroupNum;
	int m_iLinePixelWidth;
	int m_iScreenWidth;
	int m_iScreenHeight;
};

//in win32: AdjustWindowRectEx
#define RVS_LINE_WIDTH		4
#define RVS_DISPLAY_LEFT_MAX	0
#define RVS_DISPLAY_RIGHT_MAX	640
//in windows? why not 480?
#define RVS_DISPLAY_TOP_MAX		(480-30)
#define RVS_DISPLAY_BOTTOM_MAX	0

#endif /* GLLINEGROUP_H_ */
