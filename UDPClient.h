// UDPClient.h: interface for the CUDPClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UDPCLIENT_H__AE9C93A4_02FC_44A5_9A78_ED019E21900E__INCLUDED_)
#define AFX_UDPCLIENT_H__AE9C93A4_02FC_44A5_9A78_ED019E21900E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#ifndef		UDPCLIENT_API
//#define		UDPCLIENT_API		__declspec( dllimport )
//#endif

class  CUDPClient  
{
public:
	CUDPClient();
	virtual ~CUDPClient();

public:
	int UDPInit( char *pchSrvIP, unsigned short usPort, char *pchClientIP, unsigned short usClientPort ) ;
	int UDPRecv( char *pchRecvBuf ) ;
	int UDPSend( char *pchSendBuf, int iLen ) ;
	int UDPSendByte( char chByte ) ;
	int UDPRelease( ) ;
	int UDPConfig( int iRecvBufLen, int iSendBufLen, int iRecvTimeout, int iSendTimeout ) ;

};

#endif // !defined(AFX_UDPCLIENT_H__AE9C93A4_02FC_44A5_9A78_ED019E21900E__INCLUDED_)
