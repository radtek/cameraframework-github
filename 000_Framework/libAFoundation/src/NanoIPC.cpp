#include "NanoIPC.h"
#include "TraceMacros.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

Int32 NanoIPC::connect(eIPCMode mode, const string& uri)
{
	Int32 sock = -1;

	switch(mode)
	{
		case SEND:
			sock = nn_socket(AF_SP, NN_PUSH);
			if(sock < 0)
			{
				ALOGE("Unable to create read socket for mode[%d]\n", mode);
				return -1;
			}
			if(nn_connect(sock, uri.c_str()) < 0)
			{
				ALOGE("nano[%s] connect failed\n", uri.c_str());
			}
		break;
		case RECEIVE:
			sock = nn_socket(AF_SP, NN_PULL);
			if(sock < 0)
			{
				ALOGE("Unable to create read socket for mode[%d]\n", mode);
				return -1;
			}
			if(nn_bind(sock, uri.c_str()) < 0)
			{
				ALOGE("nano[%s] connect failed\n", uri.c_str());	
			}
		break;
		default:
		;
	}

	return sock;
}

BOOLEAN NanoIPC::send(Int32 sock, const CHAR* msg, Int32 size)
{
	Int32 bytes = size;
	if(sock >= 0)
	{
		
		while(bytes > 0)
		{
			int count = nn_send(sock, msg, bytes, 0);
			if(count >= 0)
			{
				ALOGI("nn_send send[%s] [%d]bytes ok\n", msg, bytes);
				bytes -= count;
				msg += count;
			}else{
				ALOGE("nn_send failed errno[%s]\n", msg, bytes, strerror(errno));
				return FALSE;
			}
		}
		
	}
	else{
		ALOGE("NanoIPC send sock unavailable.\n");
		return FALSE;
	}

	return TRUE;
}

Int32 NanoIPC::receive(Int32 sock, VOID* buff)
{
	Int32 bytes = 0;
	VOID *buffer = NULL;
	if(sock >= 0)
	{
		bytes = nn_recv(sock, &buffer, NN_MSG, 0);
		if (bytes < 0)
		{
			ALOGE("Error in reading Nano messages.\n");
			return -1;	// Error
		}
	}else{
		ALOGE("NanoIPC receive sock unavailable.\n");
		return -1;
	}

	strncpy((CHAR*)buff, (CHAR*)buffer, bytes);
	ALOGI("NanoIPC receive [%d]bytes buff[%s] ok\n", bytes, buff);

	nn_freemsg(buffer);
	return bytes;
}

VOID NanoIPC::close(Int32 sock)
{
	if(sock >= 0)
	{
		nn_shutdown(sock, 0);
		nn_close(sock);
	}
}

SendNode::SendNode(const string& uri)
	:m_uri(uri)
	,m_ipc(new NanoIPC())
	,m_sock(-1)
{

}

SendNode::~SendNode()
{
	if(m_ipc != NULL)
	{
		delete m_ipc;
		m_ipc = NULL;
	}
}

VOID SendNode::create_node()
{
	if(m_ipc != NULL)
	{
		m_sock = m_ipc->connect(SEND, m_uri);
		if(m_sock < 0)
		{
			ALOGE("Unable to create send socket for Node.");
			return;	// Error
		}
	}
}

VOID SendNode::send(const string& data)
{
	BOOLEAN ret;
	if(m_ipc != NULL)
	{
		ret = m_ipc->send(m_sock, data.c_str(), data.size()+1);
	}
}

VOID SendNode::release()
{
	if(m_ipc != NULL)
	{
		m_ipc->close(m_sock);
	}
}


ReceiveNode::ReceiveNode(const string& uri)
	:m_uri(uri)
	,m_ipc(new NanoIPC())
	,m_sock(-1)
{
}

ReceiveNode::~ReceiveNode()
{
	if(m_ipc != NULL)
	{
		delete m_ipc;
		m_ipc = NULL;
	}
}

VOID ReceiveNode::create_node()
{
	if(m_ipc != NULL)
	{

		m_sock = m_ipc->connect(RECEIVE, m_uri);
		if(m_sock < 0)
		{
			ALOGE("Unable to create receive socket for Node.");
			return;	// Error
		}
	}
}

Int32 ReceiveNode::receive(CHAR* data)
{
	Int32 ret = -1;
	if(m_ipc != NULL)
	{
		ret = m_ipc->receive(m_sock, (VOID*)data);
	}
	return ret;
}

VOID ReceiveNode::release()
{
	if(m_ipc != NULL)
	{
		m_ipc->close(m_sock);
	}
}

}
}
}
}