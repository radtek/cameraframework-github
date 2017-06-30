#include "CSVGraphicsThread.h"


bool CSVGraphicsThread::initialize()
{
	m_aryCameraTex.reserve(eCameraNum);
	m_arySkyRenderDelegate.reserve(eCameraNum);
	for(UInt32 i = 0 ;i < eCameraNum; ++ i)
	{
		m_aryCameraTex[i] = new CCameraTexture(i, CCameraSysManager::getInstance()->getCaptureDriver(i) );

		m_aryCameraTex->setup();

		m_arySkyRenderDelegate[i] =  new CSVSkyRenderDelegate(m_aryCameraTex[i]);
	}



	return TRUE;
}

void CSVGraphicsThread::unInitialize()
{

}

void CSVGraphicsThread::beforeHandleMessageQueue()
{

}

void CSVGraphicsThread::afterHandleMessageQueue()
{

}
