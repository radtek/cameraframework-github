#ifndef CADV7182CONFIG_HPP_
#define CADV7182CONFIG_HPP_
#include "adv7182.h"
#include <pthread.h>

class CADV7182Config{
public:
	static CADV7182Config* getInstance();
	bool bInit();
	bool bRelease();
	int iGetSyncStatus();
	void vSetContrast(int contrast);
	void vSetBrightness(int brightness);
protected:
	CADV7182Config();
	~CADV7182Config();
private:

private:
	static CADV7182Config* pInstance;

    pthread_mutex_t mutex;
	SV_Video_Capture videoCapture;
	bool m_bInit;
};

#endif /* CADV7182CONFIG_HPP_ */
