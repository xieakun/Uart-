// UDPClient.cpp: implementation of the CUDPClient class.
//
//////////////////////////////////////////////////////////////////////

#include	"UDPClient.h"
#include	<winsock2.h>

#pragma comment( lib, "ws2_32.lib" )

#define		MAX_LENGTH		1024*10

SOCKET			g_SockSrv ;
SOCKET			g_SockClient ;
SOCKADDR_IN		g_addrSrv ;
SOCKADDR_IN		g_addrClient ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUDPClient::CUDPClient()
{

}

CUDPClient::~CUDPClient()
{

}

/***********************************************************************
Function Name	:	UDPInit
Explanation		:	UDP initial
Return Value	:	Pass return 0, WSA启动失败返回-1, WSA版本错误返回-2
Input Value		:	pchSrvIP	--- Server IP address
					usPort		--- 程序端口
Output Value	:	None
Others			:	
History			:	<Author>		<Date>		<Desc>
					Zhao Liguo		2014.10.28	First create
***********************************************************************/
int CUDPClient::UDPInit( char *pchSrvIP, unsigned short usSrvPort, char *pchClientIP, unsigned short usClientPort )
{
	WORD wVersion ;
	WSADATA wsaData ;
	int iRet = 0 ;

	wVersion = MAKEWORD( 2, 2 ) ;
	iRet = WSAStartup( wVersion, &wsaData ) ;
	if( iRet != 0 )
	{
		return -1 ;
	}

	if( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 )
	{
		WSACleanup( ) ;
		return -2 ;
	}

	g_SockSrv = socket( AF_INET, SOCK_DGRAM, 0 ) ;

	g_addrSrv.sin_addr.S_un.S_addr = inet_addr( pchSrvIP ) ;
//	g_addrSrv.sin_addr.S_un.S_addr = htonl( INADDR_ANY ) ;
	g_addrSrv.sin_family           = AF_INET ;
	g_addrSrv.sin_port             = htons( usSrvPort ) ;

	g_addrClient.sin_addr.S_un.S_addr = inet_addr( pchClientIP ) ;
//	g_addrClient.sin_addr.S_un.S_addr = htonl( INADDR_ANY ) ;
	g_addrClient.sin_family           = AF_INET ;
	g_addrClient.sin_port             = htons( usClientPort ) ;

	bind( g_SockSrv, (SOCKADDR*)&g_addrSrv, sizeof( SOCKADDR ) ) ;

	return 0 ;
}

/***********************************************************
Function Name	:	UDPRelease
Explanation		:	UDP release
Return Value	:	0
Input Value		:	None
Output Value	:	None
Others			:	
History			:	<Author>		<Date>		<Desc>
					Zhao Liguo		2014.10.28	First create
***********************************************************/
int CUDPClient::UDPRelease( )
{
	closesocket( g_SockClient ) ;
	WSACleanup( ) ;

	return 0 ;
}

/*******************************************************************
Function Name	:	UDPRecv
Explanation		:	UDP receive data
Return Value	:	Pass return received data length, fail return -1
Input Value		:	None
Output Value	:	pchRecvBuf		--- Received data buffer
Others			:	
History			:	<Author>		<Date>		<Desc>
					Zhao Liguo		2014.10.28	First create
*******************************************************************/
int CUDPClient::UDPRecv( char *pchRecvBuf )
{
	int iRet = 0 ;
	int iLen = sizeof( SOCKADDR ) ;
	SOCKADDR_IN addr ;

	iRet = recvfrom( g_SockSrv, pchRecvBuf, MAX_LENGTH, 0, (SOCKADDR*)&g_addrClient, &iLen ) ;
	if( iRet == SOCKET_ERROR )
	{
		iRet = WSAGetLastError( ) ;
		return iRet ;
		return -1 ;
	}

	return iRet ;
}

/*****************************************************************
Function Name	:	UDPSend
Explanation		:	UDP send data
Return Value	:	Pass return sended data length, fail return -1
Input Value		:	pchSendBuf		--- Send data buf
Output Value	:	None
Others			:	
History			:	<Author>		<Date>		<Desc>
					Zhao Liguo		2014.10.28	First create
****************************************************************/
int CUDPClient::UDPSend( char *pchSendBuf, int iLen )
{
	int iRet = 0 ;

	iRet = sendto( g_SockSrv, pchSendBuf, iLen, 0, (SOCKADDR*)&g_addrClient,
		           sizeof( SOCKADDR ) ) ;
	if( iRet == SOCKET_ERROR )
	{
		return -1 ;
	}

	return iRet ;
}

int UDPSendByte( char chByte )
{
	int iRet = 0 ;

	iRet = sendto( g_SockClient, &chByte, 1, 0, (SOCKADDR*)&g_addrSrv,
		           sizeof( SOCKADDR ) ) ;
	if( iRet == SOCKET_ERROR )
	{
		return -1 ;
	}

	return iRet ;
}

/***********************************************************
Function Name	:	UDPConfig
Explanation		:	UDP配置超时和收发缓冲区大小
Return Value	:	0
Input Value		:	iRecvBufLen		--- 接收缓冲区大小
					iSendBufLen		--- 发送缓冲区大小
					iRecvTimeout	--- 接收超时（毫秒）
					iSendTimeout	--- 发送超时（毫秒）
Output Value	:	None
Others			:	
History			:	<Author>		<Date>		<Desc>
					Zhao Liguo		2014.10.28	First create
***********************************************************/
int CUDPClient::UDPConfig( int iRecvBufLen, int iSendBufLen, int iRecvTimeout, int iSendTimeout )
{
	setsockopt( g_SockClient, SOL_SOCKET, SO_RCVBUF, (const char*)&iRecvBufLen,
		        sizeof( int ) ) ;
	setsockopt( g_SockClient, SOL_SOCKET, SO_SNDBUF, (const char*)&iSendBufLen,
		        sizeof( int ) ) ;
	setsockopt( g_SockClient, SOL_SOCKET, SO_RCVTIMEO, (char*)&iRecvTimeout, sizeof( int ) ) ;
	setsockopt( g_SockClient, SOL_SOCKET, SO_SNDTIMEO, (char*)&iSendTimeout, sizeof( int ) ) ;

	return 0 ;
}


