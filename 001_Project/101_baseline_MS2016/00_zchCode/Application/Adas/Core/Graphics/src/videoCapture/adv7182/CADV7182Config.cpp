#include "CADV7182Config.hpp"
#include "foundation.h"

CADV7182Config* CADV7182Config::pInstance = NULL;

CADV7182Config* CADV7182Config::getInstance()
{
	if(pInstance==NULL)
		pInstance = new CADV7182Config();
	return pInstance;
}

CADV7182Config::CADV7182Config()
{
	m_bInit = false;
}

CADV7182Config::~CADV7182Config()
{
	;
}

TRC_SCOPE_DEF(CADV7182Config, CADV7182Config, bInit);
bool CADV7182Config::bInit()
{
	TRC_SCOPE(CADV7182Config, CADV7182Config, bInit);
	if(m_bInit)
		return true;

	bool bRes = false;
	int rc;

	rc = pthread_mutex_init(&mutex, NULL);
	if(rc){
		DBG_ERROR(("mutex init failed!\n"));
		return bRes;
	}

    videoCapture.adv7182_dev.i2c_addr = ADV7182_I2C_BASE;
    videoCapture.adv7182_dev.i2c_name = (char*)I2C_DEV_NAME;
    videoCapture.adv7182_dev.sync_status = 0;

    pthread_mutex_lock(&mutex);

    adv7182_init(&videoCapture);

    pthread_mutex_unlock(&mutex);

	m_bInit = true;
	return true;
}

bool CADV7182Config::bRelease()
{
	if(!m_bInit)
		return true;

	bool bRes = false;
	if(pthread_mutex_destroy(&mutex))
	{
		return bRes;
	}
	return true;
}

int CADV7182Config::iGetSyncStatus()
{
	if(!m_bInit)
		return 0;

	int iRet = 0;

    pthread_mutex_lock(&mutex);

    iRet = adv7182_get_syncstatus(&videoCapture);

    pthread_mutex_unlock(&mutex);

    return iRet;
}

void CADV7182Config::CADV7182Config::vSetContrast(int contrast)
{
	if(!m_bInit)
		return;

    pthread_mutex_lock(&mutex);

    adv7182_set_contrast(&videoCapture,  (uint8_t)(contrast * 2.55));

    pthread_mutex_unlock(&mutex);

}

void CADV7182Config::vSetBrightness(int brightness)
{
	if(!m_bInit)
		return;

	unsigned char tmp;
    if(brightness >= 50)
    {
    	tmp = (brightness - 50) * 2.55;
    } else {
    	tmp = 0x80 + brightness * 2.55;
    }
    pthread_mutex_lock(&mutex);

    adv7182_set_brightness(&videoCapture,  tmp);

    pthread_mutex_unlock(&mutex);
}
