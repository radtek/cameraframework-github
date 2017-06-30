#include "CUniform.h"
#include "../pipeline/CRenderLayout.h"
#include "../pipeline/CRenderUtility.h"


	//void setUniform_Vec3(Object* pRender,Uniform_NameCallBackFunc nameCallBack,Int32 iLoc)
	//{
	//	C3DVector ret;
	//	
	//	CallFunc(Func_Vec3,nameCallBack);
	//	glUniform3f(iLoc,ret.getX(),ret.getY(),ret.getZ());
	//}

	//void setUniform_Vec3Array(Object* pRender,Uniform_NameCallBackFunc nameCallBack,Int32 iLoc)
	//{
	//	Array2<C3DVector> ret;
	//	
	//	CallFunc(Func_ArrayVec3,nameCallBack);
	//	glUniform3fv(iLoc,ret.size(),(const GLfloat*)&ret[0]);
	//}

	//void setUniform_Vec4(Object* pRender,Uniform_NameCallBackFunc nameCallBack,Int32 iLoc)
	//{
	//	C3DVector4 ret ;
	//	
	//	CallFunc(Func_Vec4,nameCallBack);
	//	glUniform4f(iLoc,ret.getX(),ret.getY(),ret.getZ(),ret.getW() );
	//}

	//void setUniform_Vec4Array(Object* pRender,Uniform_NameCallBackFunc nameCallBack,Int32 iLoc)
	//{
	//	Array2<C3DVector4> ret;
	//	
	//	CallFunc(Func_ArrayVec4,nameCallBack);
	//	glUniform4fv(iLoc,ret.size(),(const GLfloat*)&ret[0]);
	//}

	//void setUniform_Matrix3(Object* pRender,Uniform_NameCallBackFunc nameCallBack,Int32 iLoc)
	//{
	//	//C3DMatrix3 ret;
	//	//
	//	//CallFunc(Func_Matrix3,nameCallBack);
	//	//glUniformMatrix3fv(iLoc,1,GL_FALSE,(const GLfloat*)&ret);
	//}

	//void setUniform_Matrix3Array(Object* pRender,Uniform_NameCallBackFunc nameCallBack,Int32 iLoc)
	//{
	//	//Array2<C3DMatrix3> ret;
	//	//
	//	//CallFunc(Func_ArrayMatrix3,nameCallBack);
	//	//glUniformMatrix3fv(iLoc,ret.size(),GL_FALSE,(const GLfloat*)&ret[0]);
	//}

	//void setUniform_Matrix4(Object* pRender,Uniform_NameCallBackFunc nameCallBack,Int32 iLoc)
	//{
	//	C3DMatrix ret;
	//	
	//	CallFunc(Func_Matrix4, nameCallBack);
	//	glUniformMatrix4fv(iLoc, 1, GL_FALSE, (const GLfloat*)ret.ptr());
	//}

	//void setUniform_Matrix4Array(Object* pRender,Uniform_NameCallBackFunc nameCallBack,Int32 iLoc)
	//{
	//	Array2<C3DMatrix> ret;
	//	
	//	CallFunc(Func_ArrayMatrix4,nameCallBack);
	//	glUniformMatrix4fv(iLoc,ret.size(),GL_FALSE,(const GLfloat*)&ret[0]);
	//}

	//--------------------------------------------------------------------------------------------------
	void getProject_UI(Ref* p,C3DMatrix4& ret)
	{
		//C3DMatrix4* pMtRotateZ = NULL;
		//
		CRenderLayout* pRender = (CRenderLayout*)p;
		CRenderContainer* pRenderContainer = pRender->getParent();
		
		const C3DMatrix4& mtProject = pRenderContainer->getProjectMatrix();
		ret = mtProject;
	}

	void getMP_UI(Ref* p,C3DMatrix4& ret)
	{
		//C2DBatchRender* pRender = (C2DBatchRender*)p;
		//C2DBatchRenderGroup* pBatchRndGroup = pRender->getParent();
		//BOOLEAN b25D = pRender->is25D();
		//const C3DMatrix4& mtProject = pBatchRndGroup->getProjectMatrix( b25D );
		//ret = mtProject * pRender->getWorldMatrix();
		
	}
