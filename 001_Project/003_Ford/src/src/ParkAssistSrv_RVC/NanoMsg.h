/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            NanoMsg.h
* @ingroup         Park-Asist
* @author          Atita Halemani and Ashwini Shamaprasad (Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           Provide the IPC communication between PAM and ford video app for later rvc usecase. 
*				   
*/
#ifndef __NANO_MESSAGE__
#define __NANO_MESSAGE__


#include <nanomsg/nn.h>
#include <nanomsg/bus.h>


/* @brief NanoMsg List required to interact between different process*/
enum NanoMessges
{
	RVC_SCREEN_ON = 1,
	RVC_SCREEN_OFF = 2,
	RVC_GET_STATUS = 3,
	PAM_AVALIABEL_NOTIFACTION =4 ,
	PAM_AVALIABEL_ACK =4 ,
	PAM_NOT_AVALIABEL  = 5 ,
	SWITCH_OFF_RVC_REQ = 6,
	SWICTH_OFF_RVC_ACK = 7,
	SWICTH_ON_RVC_ACK = 8,
	RVC_NOT_CONFIGURED = 9,
	RVC_NO_SIGNAL = 15,
	RVC_MALFUNCTION_ERROR = 16

};


/**@Brief Broadcst Nano messages over bus , registered process will receive the messages
 *
 * \param Socket Handel *
 * \return  No of Byte Sent 
 *
 */

inline int SendNanoMessage(int socket,int message) 
{
  int Bytes_Sent = nn_send(socket, &message, sizeof(int), 0);
  return Bytes_Sent;
}


/** Initial handshake between PAM(client) and ford video App(server) to make sure that connection established properly before sending the messages 
 *
 * \param Socket Handel *
 * \return  NanoMessges 
 *
 */
 
inline int NanoMsgHandShake(int socket) 
{
	int count = 0;
	int recv = 0;
	int iReturn = -1;
	//Receive time out of 100ms 
	int timeout = 500;
	char *buf = NULL;
	int MessgaeType =-1;
	
	//making socket as non blocking with a time out of 100 ms to achieve initial handshake
	nn_setsockopt (socket, NN_SOL_SOCKET, NN_RCVTIMEO, &timeout, sizeof (timeout)) ;
	
	//making sure that connection is established before sending the messages on bus
	while(count < 10)
	{
		printf("NanoMsgHandShake count :%d \n ",count);
		SendNanoMessage(socket,PAM_AVALIABEL_NOTIFACTION);
		recv = nn_recv (socket, &buf, NN_MSG, 0);
		if (recv > 0)
        {
			MessgaeType = *((int *)buf);
			nn_freemsg (buf);
			if(MessgaeType == PAM_AVALIABEL_ACK)
			{
				printf("NanoMsgHandShake is success \n");
				iReturn = 1;
				break;
			
			}
        }

		count ++;
	}
	timeout = -1; //to make socket blocking  to avoid cpu loading 
	nn_setsockopt (socket, NN_SOL_SOCKET, NN_RCVTIMEO, &timeout, sizeof (timeout)) ;
	return iReturn;
}

/** Receiving and Parsing Nano messages
 *
 * \param Socket Handel *
 * \return  NanoMessges 
 *
 */
 
inline int RecvNanoMessage(int socket) 
{
 	void *buf = NULL;
	int MessgaeType =-1;
	
	//Blocking RECV until recv the msg on bus
	int recv = nn_recv (socket, &buf, NN_MSG, 0);
	if (recv > 0)
	{
		// conversion of received msg to NanoMessges enum list
		MessgaeType = *((int *)buf);
		nn_freemsg (buf);  //free the buffer memory 
	}
	//Error in case socket is closed
	else if((errno== EBADF) || (errno== ENOTSUP ) || (errno== EFSM) || (errno== ETERM))
	{
		MessgaeType = recv;
	}
	return MessgaeType;
}

/**Closing the connection
 *
 * \param Socket Handel *
 */

inline void CloseNanoMsgConnection(int sock) 
{
  nn_shutdown (sock, 0);
}


/**Opening server side socket and binding it
 *
 * \return socket handel for server
 */

inline int OpenNanoMsgHost() 
{
    //Node to be created in /tmp folder to achive IPC communication 
	const char *Serverurl = "ipc:///tmp/FordVidApp.ipc";
	int sock;
	//creating Nano socket
	sock = nn_socket (AF_SP,NN_BUS);
	if (sock < 0)
	{
		return -1;
	}
	
	//creating node in tmp to archive IPC communication
	if ((nn_bind (sock, Serverurl)) < 0)
	{
		// close the socket if creating node is failed 
		CloseNanoMsgConnection(sock);
		return -1;  
	}
	return sock;
}


/**Opening server side socket and binding it
 *
 * \return socket handle for server
 */

inline int ConnectToNanoMsgHost() 
{
	//Connect to /tmp/FordVidApp.ipc  node  to achieve IPC communication
  	const char *Serverurl = "ipc:///tmp/FordVidApp.ipc";
	int sock;
	int result = 0;
	//creating Nano socket
	sock = nn_socket (AF_SP,NN_BUS);
	if (sock < 0)
	{
		return -1;
	}
	
	//connecting to IPC node 
	result = nn_connect (sock, Serverurl);
	if (result < 0)
	{
		CloseNanoMsgConnection(sock);
		return -1; 
	}
	return sock;
}

#endif

