#include "NanoIPC.h"
#include "TraceMacros.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

Int32 NanoIPC::connect(eIPCMode mode, const string& uri)
{
	Int32 sock;

	switch(mode)
	{
		case SEND:
			sock = nn_socket(AF_SP, NN_PUSH);
			if(nn_connect(sock, uri.c_str()) >= 0)
			{
				ALOGD("nano connect ok\n");	
			}else
			{
				ALOGD("nano[%s] connect failed\n", uri.c_str());	
			}
		break;
		case RECEIVE:
			sock = nn_socket(AF_SP, NN_PULL);
			if(nn_bind(sock, uri.c_str()) >= 0)
			{
				ALOGD("nano connect ok\n");	
			}else
			{
				ALOGD("nano[%s] connect failed\n", uri.c_str());	
			}
		break;
		default:
		;
	}
}

}
}
}
}