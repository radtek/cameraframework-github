
#include <stdio.h>
#include <errno.h>


#include "OGLES2Interface.h"
#include "GlGMRVS.h"

int OGLES2Init(void* eglDisplay,rvs_ctx_t* ctx)
{
//	m_GMRVS.Init(ctx,width,height);
	GlGMRVS::getInstance()->Init(ctx,ctx->DispCfg.wndsize[0],ctx->DispCfg.wndsize[1]);

	if(!ctx->symblAvail.UPAResourceAvail)
		pthread_create(NULL, NULL, UPA_Monitor_Thread, ctx);

	
	if(!ctx->symblAvail.RCTAResourceAvail)
		pthread_create(NULL, NULL, RCTA_Monitor_Thread, ctx);

	return 0;
}

void OGLES2Draw(rvs_ctx_t* ctx)
{
	GlGMRVS::getInstance()->Update(ctx);
}
