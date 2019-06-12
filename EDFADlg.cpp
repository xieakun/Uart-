// EDFADlg.cpp : implementation file
//

#include "stdafx.h"
#include "EDFA.h"
#include "EDFADlg.h"
#include "afxmt.h"  
//Ϊ���ļ����ܹ���ȷʹ��ͬ���࣬���ļ���ͷ��ӣ�#include "afxmt.h"  
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include	"SkinPPWTL.h"

#pragma comment( lib, "SkinPPWTL.lib" )
int BaudRat[] = {/*9600,19200,38400,57600,*/115200};
#define TIMER_SHOW_MONITOR    1
/****
�����ٽ�����һ���ַ����飬Ϊ���ܹ��ڲ�ͬ�̼߳�ʹ�ã�
����Ϊȫ�ֱ�����CCriticalSection critical_section;  
****/
CCriticalSection critical_section;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEDFADlg dialog

CEDFADlg::CEDFADlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEDFADlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEDFADlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CEDFADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEDFADlg)
	DDX_Control(pDX, IDC_Check_Auto, m_Auto);

	DDX_Control(pDX, IDC_STC_MPO5, m_MPOLED5);
	DDX_Control(pDX, IDC_STC_MPO4, m_MPOLED4);
	DDX_Control(pDX, IDC_STC_MPO3, m_MPOLED3);
	DDX_Control(pDX, IDC_STC_MPO2, m_MPOLED2);
	DDX_Control(pDX, IDC_STC_MPO1, m_MPOLED1);
	DDX_Control(pDX, IDC_STC_DLC5, m_DLCLED5);
	DDX_Control(pDX, IDC_STC_DLC4, m_DLCLED4);
	DDX_Control(pDX, IDC_STC_DLC3, m_DLCLED3);
	DDX_Control(pDX, IDC_STC_DLC2, m_DLCLED2);
	DDX_Control(pDX, IDC_STC_DLC1, m_DLCLED1);
	DDX_Control(pDX, IDC_STC_COMM, m_ComLed);
	DDX_Control(pDX, IDC_COMBO_COMNO, m_ctrlCOMNO);
	DDX_Control(pDX, IDC_COMBO_BANDRATE, m_ctrlBandRate);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEDFADlg, CDialog)
	//{{AFX_MSG_MAP(CEDFADlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON16, OnButtonReadAll)
	ON_BN_CLICKED(IDC_BUTTON_OPENCOM, OnButtonOpenCOM)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECOM, OnButtonCloseCOM)
	ON_BN_CLICKED(IDC_BUTTON_ONEKEYRECEIVE, OnButtonOnekeyreceive)
	ON_BN_CLICKED(IDC_BUTTON_OPENCOM4, OnButtonOnekeywrite)
	ON_BN_CLICKED(IDC_Check_Auto, OnCheckAuto)
	ON_WM_TIMER()
	
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BTN_CHN_W1, OnBtnChnW1)
	ON_BN_CLICKED(IDC_BTN_CHN_R1, OnBtnChnR1)
	ON_BN_CLICKED(IDC_BTN_CHN_R2, OnBtnChnR2)
	ON_BN_CLICKED(IDC_BTN_CHN_R3, OnBtnChnR3)
	ON_BN_CLICKED(IDC_BTN_CHN_R4, OnBtnChnR4)
	ON_BN_CLICKED(IDC_BTN_CHN_R5, OnBtnChnR5)
	ON_BN_CLICKED(IDC_BTN_CHN_W2, OnBtnChnW2)
	ON_BN_CLICKED(IDC_BTN_CHN_W3, OnBtnChnW3)
	ON_BN_CLICKED(IDC_BTN_CHN_W4, OnBtnChnW4)
	ON_BN_CLICKED(IDC_BTN_CHN_W5, OnBtnChnW5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEDFADlg message handlers

BOOL CEDFADlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	CRect m_rect;
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	/**********�����ʳ�ʼ��******/
	CString str;
	for(int i =0; i < sizeof(BaudRat)/sizeof(int);i++)
	{
		str.Format("%d",BaudRat[i]);
		m_ctrlBandRate.AddString((LPCTSTR)str);
	}
	str.Format("%d",115200);
	/* ������������ɫ����ʽ*/
	skinppLoadSkin(_T("Royale.ssk"));
	/************************************************************************/
	/*******Ĭ��ѡ�������е�DLC ��Ҳ����DLC�������� 
	*/
	/************************************************************************/
	
	((CButton *)GetDlgItem(IDC_RIO_DLC1))->SetCheck(TRUE); //ѡ��DLC
	((CButton *)GetDlgItem(IDC_RIO_DLC22))->SetCheck(TRUE); //ѡ��DLC
	((CButton *)GetDlgItem(IDC_RIO_DLC3))->SetCheck(TRUE); //ѡ��DLC
	((CButton *)GetDlgItem(IDC_RIO_DLC4))->SetCheck(TRUE); //ѡ��DLC
	((CButton *)GetDlgItem(IDC_RIO_DLC5))->SetCheck(TRUE); //ѡ��DLC
	((CButton*)GetDlgItem(IDC_RIO_Block1_0))->SetCheck(TRUE);//ѡ�� ��0
	((CButton*)GetDlgItem(IDC_RIO_Block2_0))->SetCheck(TRUE);//ѡ�� ��0
	((CButton*)GetDlgItem(IDC_RIO_Block3_0))->SetCheck(TRUE);//ѡ�� ��0
	((CButton*)GetDlgItem(IDC_RIO_Block4_0))->SetCheck(TRUE);//ѡ�� ��0
	((CButton*)GetDlgItem(IDC_RIO_Block5_0))->SetCheck(TRUE);//ѡ�� ��0
	
	


	
	( (CComboBox*)GetDlgItem( IDC_COMBO_COMNO ) )->SetCurSel( 0 ) ;
	//( (CComboBox*)GetDlgItem( IDC_COMBO_BANDRATE ) )->SetCurSel( 0 ) ;
	m_ctrlBandRate.SetCurSel(m_ctrlBandRate.FindString(0,str));	

	GetClientRect(&m_rect);		//��ȡ�Ի���Ĵ�С
	old.x = m_rect.right - m_rect.left;
	old.y = m_rect.bottom - m_rect.top;

	this->time_flag = Stopping;//��¼��ʱ������ֹͣ����δ����ָ��

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEDFADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEDFADlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEDFADlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CEDFADlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CEDFADlg)
	ON_EVENT(CEDFADlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CEDFADlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp ;
	COleSafeArray safearray_inp ;

	char chArrT[6] = { 0 } ;

	BYTE bt = 0 ;
	
	LONG len, k ;
	BYTE btArrRecv[512] = { 0 } ;//��������֡

	CString csTemp ;
	
	if( this->m_ctrlComm.GetCommEvent( ) == 2 )		//���ջ����������ַ�
	{
		Sleep( 200 ) ;
		memset( btArrRecv, 0, sizeof( BYTE )*512 ) ;
	
		variant_inp = m_ctrlComm.GetInput( ) ;		//��ȡ������������
		safearray_inp = variant_inp ;		//��VARIANT����ת��ΪCOleSafeArray����
		
		len = safearray_inp.GetOneDimSize( ) ;		//ȷ�����ݳ���
				
		for( k = 0 ; k < len ; k++ )
		{
			safearray_inp.GetElement( &k, btArrRecv + k ) ;		//������ת��ΪBYTE����
		}
	/*	д����־�ļ����ò����ή�ͽ��ջ�����ٶ�*/
		this->WriteTxtLog(btArrRecv,len,-1);

		if (btArrRecv[0] != 0X68)
		{
			return ;
		}
		if( btArrRecv[1] != btArrRecv[2] )
		{
			return ;
		}
		//////////////////////////////////////////////////////////////////////////
		/**�����9 ��ָ 68H ���ݳ��� ���ݳ��� 68H 16H 19H ������ У��� 16H**/
		if (len != ((int)btArrRecv[1]+6/*���ݾ��嶨���޸� ������Length+6*/))
		{
			return ;
		}
		if (btArrRecv[3] != 0X68)
		{
			return ;
		}
		if (btArrRecv[4] != 0X16)
		{
			return ;
		}
		if (btArrRecv[5] != 0X19)
		{
			return ;
		}
/************************************************************************/
/*                                DA        ����
	68H  ���ݳ���n  ���ݳ���n  68H  0x16  0x19  FC  ����  У���  16H
                                                                     */
/************************************************************************/
		if (btArrRecv[len - 2] != GetCheckSum( btArrRecv+4, len - 6 ) )
		{
		//	return ;
		}
		if (btArrRecv[len-1] != 0X16)
		{
			return ; 
		}
/*********0XE2��ͷ���������ϱ� ��ʾ��λ����״̬**************/
		if (btArrRecv[6] == 0XE2)
		{
			
			//[����]68 04 04 68 16 19 E2 AA AA AA A5 A5 BA BA BA B5 B5 DE 16
			//��ʾ��λ����״̬ 
			ShowSync(btArrRecv+7);
		}
/*********OXE1���ڲ����ϱ� ��������ʾ**************/		
		if (btArrRecv[6] == 0XE1)
		{
			ShowBandRate(btArrRecv);
		}
		
/****0XE3��ͷEEPROM�����ϱ� DLC MPO����·������ʾ****/
		if (btArrRecv[6] == 0XE3/*������ʾFC����λ*/)
		{
			ShowChannelData(btArrRecv);
		}
/******0XE4��ͷRFID�����ϱ�*******/
		if ( btArrRecv[6] == 0XE4 )
		{
			ShowRFIDData(btArrRecv);
		}

/******����״̬�ϱ�  ��Ӧ֡0XEF*******/
		if (btArrRecv[6] == 0XEF)
		{
			ShowError(btArrRecv);
		}
/***************************/
		

	}

}



void CEDFADlg::ShowBITE( unsigned char *pucBITEData )
{
	char chArrT[40] = { 0 } ;
	unsigned char ucT = 0 ;
	unsigned short usT = 0 ;
	float fT = 0 ;
	
	//SN
	unsigned long ulSN = 0 ;
	ulSN = pucBITEData[7]*10000 + pucBITEData[8]*100 + pucBITEData[9] ;
	sprintf( chArrT, "%ld", ulSN ) ;
	GetDlgItem( IDC_EDIT2 )->SetWindowText( chArrT ) ;

	//alarm
	unsigned char ucAlarm1, ucAlarm2, ucAlarm3 ;
	ucAlarm1 = pucBITEData[10] ;
	ucAlarm2 = pucBITEData[11] ;
	ucAlarm3 = pucBITEData[12] ;
	

/*	*/

	//��д�澯�ֽ�
	sprintf( chArrT, "%.2X %.2X %.2X", ucAlarm1, ucAlarm2, ucAlarm3 ) ;
	GetDlgItem( IDC_EDIT3)->SetWindowText( chArrT ) ;


//	GetDlgItem( IDC_EDIT17 )->SetWindowText( chArrT ) ;
}


int CEDFADlg::PassFail( unsigned char *pucData )
{
	
	return 1 ;
	


}

void CEDFADlg::COMSendData( unsigned char *pucData, int iLength )
{
	
	
	CByteArray hexData ;
	hexData.RemoveAll( ) ;
	hexData.SetSize( iLength ) ;

	for( int i = 0 ; i < iLength ; i++ )
	{
		hexData.SetAt( i, pucData[i] ) ;
	}

	
	m_ctrlComm.SetOutput( COleVariant( hexData ) ) ;
	 
}
/************************************************************************/
/* 
Function Name	:	StdDataSend(unsigned char *strdata)
Explanation		:	��׼�ķ��ͺ��� ��֧�ַ��͵�Ƭ������ѯ֡ �����ݳ���Ϊ2
STD    Value	:	68H  04H  04H  68H  16H  19H  FC  ����  У���  16H
Input Value		:	unsigned char *strdata������Ϊ2
Output Value	:	none	                                                                    */
/************************************************************************/
void CEDFADlg::StdDataSend(unsigned char *strdata)
{
		
		BYTE btArrT[10] = { 0 } ;
		btArrT[0] = 0X68 ;
		btArrT[1] = 0X04 ;
		btArrT[2] = 0X04 ;
		btArrT[3] = 0X68 ;
		btArrT[4] = 0X16 ;
		btArrT[5] = 0X19 ;
		btArrT[6] = strdata[0];
		btArrT[7] = strdata[1];
		btArrT[8] = GetCheckSum( btArrT+4, 4 );
		btArrT[9] = 0X16;
		this->COMSendData( btArrT, 10 );
		this->WriteTxtLog( btArrT, 10 ,1 );
		
}

void CEDFADlg::OnButtonReadAll() 
{
	// TODO: Add your control notification handler code here
	ClearEditBox();
	GetDlgItem(IDC_EDIT_READCONTENT)->SetWindowText("");



}
/************************************************************************/
/*				У��ͺ���
			��ʼ��ַ��pucData ����iDataLen
			���أ�(char)У���
                                                                     */
/************************************************************************/
unsigned char CEDFADlg::GetCheckSum( unsigned char *pucData, int iDataLen ) 
{
	unsigned char unSum = 0 ;
	long lSum = 0 ;

	for( int i = 0 ; i < iDataLen ; i++ )
	{
		lSum += pucData[i] ;
	}

	unSum = lSum ;

	return unSum ;
}
/************************************************************************/
/*                                DA        ����
 68H  ���ݳ���n  ���ݳ���n  68H  0x16  0x19  FC  ����  У���  16H
                                                                     */
/************************************************************************/
void CEDFADlg::OnButtonOpenCOM() 
{
	// TODO: Add your control notification handler code here
	char BoudRate;
	char chArrNO[10] = { 0 } ;
	char chArrRate[20] = { 0 } ;
	this->m_ctrlCOMNO.GetWindowText( chArrNO, 10 ) ;
	this->m_ctrlBandRate.GetWindowText( chArrRate, 20 ) ;

	CString csTemp = chArrRate ;
	if ("9600"==csTemp)
	{
		BoudRate=0x0;
		WriteLog("If you really want to change zhe BoundRate Please restart the power!");
	} 
	if ("19200"==(csTemp))
	{
		BoudRate=0x1;
		WriteLog("If you really want to change zhe BoundRate Please restart the power!");
	} 
	if ("38400"==csTemp)
	{
		BoudRate=0x2;
		WriteLog("If you really want to change zhe BoundRate Please restart the power!");
	} 
	if ("57600"==csTemp)
	{
		BoudRate=0x3;
		WriteLog("If you really want to change zhe BoundRate Please restart the power!");
	} 
	if ("115200"==csTemp)
	{
		BoudRate=0x4;
	}
	
	csTemp += ",n,8,1" ;

/*	csTemp = "1152000,n,8,1" ;*/
	if( this->m_ctrlComm.GetPortOpen( ) )
	{
		m_ctrlComm.SetPortOpen( FALSE ) ;
	}

	m_ctrlComm.SetCommPort( m_ctrlCOMNO.GetCurSel( ) + 1 ) ;

	m_ctrlComm.SetSettings( csTemp ) ;//���� ������,N,8,1
	m_ctrlComm.SetInputMode( 1 ) ;		//�����Ʒ�ʽ��ȡ����
	m_ctrlComm.SetRThreshold( 1 ) ;		//����1��ʾÿ�����ڻ������ɶ�����ߵ���1������ʱ��������һ��oncomm�¼�
	m_ctrlComm.SetInputLen( 512 ) ;
//	m_ctrlComm.SetOutputLen( 1024 ) ;
	HBITMAP hBitMap1,hBitMap;
	hBitMap1 = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP4));
	try
	{
		if( !m_ctrlComm.GetPortOpen( ) )
		{
			m_ctrlComm.SetPortOpen( TRUE ) ;
			WriteLog( "Open serial port successfully" ) ;
			GetDlgItem( IDC_BUTTON_CLOSECOM )->EnableWindow( TRUE ) ;
			GetDlgItem( IDC_COMBO_BANDRATE )->EnableWindow( FALSE ) ;
			GetDlgItem( IDC_COMBO_COMNO )->EnableWindow( FALSE ) ;
			GetDlgItem( IDC_BUTTON_OPENCOM )->EnableWindow( FALSE ) ;


		}
		else
		{
			
			m_ComLed.SetBitmap(hBitMap1);
			UpdateData(FALSE);
			MessageBox( "Serial port failed to open,please check the serial port settings,check if the serial port is occupied��", "Serial port Error", MB_ICONERROR ) ;
			return ;
		}
	}
	
	catch (CException* e)
	{
		
			m_ComLed.SetBitmap(hBitMap1);
			MessageBox( "Serial Port Error", "Serial Port Error", MB_ICONERROR ) ;
			WriteLog("Serial Port Error");
			return ;
	}
	
	//LED Turn Blue
	
	hBitMap = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP3));
	m_ComLed.SetBitmap(hBitMap);
	UpdateData(FALSE);
	
	m_ctrlComm.GetInput( ) ;

/******���Ͳ�����***********/

	BYTE btArrT[10] = { 0 } ;
	btArrT[0] = 0X68 ;
	btArrT[1] = 4 ;
	btArrT[2] = 4 ;
	btArrT[3] = 0X68 ;
	btArrT[4] = 0X16 ;
	btArrT[5] = 0X19 ;
	btArrT[6] = 0XC2 ;
	//btArrT[7] = 0X41;
	btArrT[7] = BoudRate<<4 ;
	btArrT[8] = GetCheckSum( btArrT+4, 4 ) ;
	btArrT[9] = 0X16 ;
	//������ͣ���� ��ס
	this->COMSendData( btArrT, 10 ) ;
	this->WriteTxtLog(btArrT,10,1);


}

void CEDFADlg::OnButtonCloseCOM() 
{
	// TODO: Add your control notification handler code here
	if( this->m_ctrlComm.GetPortOpen( ) )
	{
		m_ctrlComm.SetPortOpen( FALSE ) ;
	}

	
	
	WriteLog( "Serial port has been closed" ) ;
	HBITMAP hBitMap1/*,hBitMap*/;
	hBitMap1 = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP5));
	m_ComLed.SetBitmap(hBitMap1);

	GetDlgItem( IDC_BUTTON_CLOSECOM )->EnableWindow( FALSE ) ;
	GetDlgItem( IDC_COMBO_BANDRATE )->EnableWindow( TRUE ) ;
	GetDlgItem( IDC_COMBO_COMNO )->EnableWindow( TRUE ) ;
	GetDlgItem( IDC_BUTTON_OPENCOM )->EnableWindow( TRUE ) ;	

//	this->KillTimer( TIMER_DETECT ) ;	
}

/************************************************************************/
/*                                DA        ����
 68H  ���ݳ���n  ���ݳ���n  68H  0x16  0x19  FC  ����  У���  16H
                                                                     */
/************************************************************************/
void CEDFADlg::OnButtonOnekeyreceive() 
{
	// TODO: Add your control notification handler code here
	//((CButton*)GetDlgItem(IDC_Check_Auto))->SetCheck(TRUE);//test
	//((CButton*)GetDlgItem(IDC_Check_Auto))->SetCheck(FALSE);
	
	//����Ƿ�򿪴���
	if (!CheckPort())
	{
		return;

	}
	if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}

	this->OnButtonReadAll();
	
	
	try
	{
	
	
		//1 ��ͷ����״̬��ȡ
		BYTE btArrT[15] = { 0 } ;
		btArrT[0] = 0X68 ;
		btArrT[1] = 0X04 ;
		btArrT[2] = 0X04;
		btArrT[3] = 0X68 ;
		btArrT[4] = 0X16 ;
		btArrT[5] = 0X19 ;
		btArrT[6] = 0XC3 ;
		btArrT[7] = 0XFF ;
		btArrT[8] = GetCheckSum( btArrT+4, 4 ) ;
		btArrT[9] = 0X16 ;
		this->COMSendData( btArrT, 10 ) ;
		this->WriteTxtLog( btArrT, 10,1 );
		
		this->Time1(1200);
		this-> OnBtnChnR1();
		this->Time1(800);
		
		this-> OnBtnChnR2();
		this->Time1(800);
		
		this->OnBtnChnR3();
		this->Time1(800);
		
		this->OnBtnChnR4();
		this->Time1(800);
		
		this->OnBtnChnR5();
		this->Time1(800);
		MessageBox("Receiving Complete","Channel1~5",MB_OK);
		WriteLog("One-key Received complete!!");
// 		//2 ��ͷEEPROM���ݶ�ȡ
// 		btArrT[6] = 0XC4 ;
// 		btArrT[7] = 0XFF ;
// 		btArrT[8] = GetCheckSum( btArrT+4, 4 ) ;
// 		btArrT[9] = 0X16 ;
// 		this->COMSendData( btArrT, 10 ) ;
// 		
// 		//3 ��ͷRFID���ݶ�ȡ
// 		btArrT[6] = 0XC6 ;
// 		btArrT[7] = 0XFF ;
// 		btArrT[8] = GetCheckSum( btArrT+4, 4 ) ;
// 		btArrT[9] = 0X16 ;
// 		this->COMSendData( btArrT, 10 ) ;

		//4 ���ڲ�����ȡ
// 		btArrT[6] = 0XC1 ;
// 		btArrT[7] = 0XFF ;
// 		btArrT[8] = GetCheckSum( btArrT+4, 4 ) ;
// 		btArrT[9] = 0X16 ;
// 		this->COMSendData( btArrT, 10 ) ;
		}

	catch (CException* e)
	{
		AfxMessageBox("Unknown Exception������");
	}

	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}	
}

/************************************************************************/
/* 
Function Name	:	ShowSync(unsigned char *pucSyncData)
Explanation		:	��ʾ10·��λ����״̬ IDC_STC_DLC1~5  IDC_STC_MPO1~5��ʾ״̬
Return Value	:	none
Input Value		:	CString ���ͱ���
Output Value	:	none	                          */
/************************************************************************/
void CEDFADlg :: ShowSync(unsigned char *pucSyncData)
{
	unsigned char chArrT[10] = {0};
	
	//�ݶ�10·����������λ�������ݣ�����Ҫ��������
	for (int i =0;i<10;i++)
	{
		chArrT[i]=pucSyncData[i];
	}
	
	HBITMAP hBitMapBlue,hBitMapRed,hBitMapGray,hBitMapYellow,hBitMapGreen;
	hBitMapBlue = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP6));
	hBitMapRed = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP7));
	hBitMapGray = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP8));
	hBitMapYellow = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP9));
	hBitMapGreen = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP10));

	//m_DLCLED1.SetBitmap(hBitMap11);

	
	switch (chArrT[0])
	{
	case 0XAA:
		//DLC1�Ѳ��� ���̵�
		m_DLCLED1.SetBitmap(hBitMapBlue);
		((CButton*)GetDlgItem(IDC_RIO_DLC1))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RIO_MPO1))->SetCheck(FALSE);
		break;
	case 0XA9:
		//DLC1��EEOROM�Ѳ��� ���̵�
		m_DLCLED1.SetBitmap(hBitMapGreen);
		((CButton*)GetDlgItem(IDC_RIO_DLC1))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RIO_MPO1))->SetCheck(FALSE);
		break;
	case 0XA5:
		//DLC1δ���� �����
		m_DLCLED1.SetBitmap(hBitMapRed);
		break;
	case 0X53:
		//DLC1�޵����ߣ����Ƶ�
		m_DLCLED1.SetBitmap(hBitMapYellow);
		break;
	
	default:
		//DLC1 ���ҵ�
		m_DLCLED1.SetBitmap(hBitMapGray);;
		break;
	}


	switch (chArrT[1])
	{
	case 0XAA:
		//DLC2 ���̵�
		m_DLCLED2.SetBitmap(hBitMapBlue);
		((CButton*)GetDlgItem(IDC_RIO_DLC22))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RIO_MPO22))->SetCheck(FALSE);
		break;
	case 0XA9:
		//DLC2 ���̵�
		m_DLCLED2.SetBitmap(hBitMapGreen);
		((CButton*)GetDlgItem(IDC_RIO_DLC22))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RIO_MPO22))->SetCheck(FALSE);
		break;
	case 0XA5:
		//DLC2 �����
		m_DLCLED2.SetBitmap(hBitMapRed);
		break;
	case 0X53:
		//DLC2�޵����ߣ����Ƶ�
		m_DLCLED2.SetBitmap(hBitMapYellow);
		break;
	default:
		//DLC2 ���ҵ�
		m_DLCLED2.SetBitmap(hBitMapGray);
		break;
	}


	switch (chArrT[2])
	{
	case 0XAA:
		//DLC3 ���̵�
		m_DLCLED3.SetBitmap(hBitMapBlue);
		((CButton*)GetDlgItem(IDC_RIO_DLC3))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RIO_MPO3))->SetCheck(FALSE);
		break;
	case 0XA9:
		//DLC3 ���̵� ֱ����EEPROM
		m_DLCLED3.SetBitmap(hBitMapGreen);
		((CButton*)GetDlgItem(IDC_RIO_DLC3))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RIO_MPO3))->SetCheck(FALSE);
		break;
	case 0XA5:
		//DLC3 ����ƣ�MPO3���ҵ�
		m_DLCLED3.SetBitmap(hBitMapRed);
		break;
	case 0X53:
		//DLC3�޵����ߣ����Ƶ�
		m_DLCLED3.SetBitmap(hBitMapYellow);
		break;
	default:
		//DLC3 ���ҵƣ�MPO3���ҵ�
		m_DLCLED3.SetBitmap(hBitMapGray);
		break;
	}


	switch (chArrT[3])
	{
	case 0XAA:
		//DLC4 ���̵�
		m_DLCLED4.SetBitmap(hBitMapBlue);
		((CButton*)GetDlgItem(IDC_RIO_DLC4))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RIO_MPO4))->SetCheck(FALSE);
		break;
	case 0XA9:
		//DLC4 ���̵� ֱ����EEPROM
		m_DLCLED4.SetBitmap(hBitMapGreen);
		((CButton*)GetDlgItem(IDC_RIO_DLC4))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RIO_MPO4))->SetCheck(FALSE);
		break;
	case 0XA5:
		//DLC4 ����ƣ�MPO4���ҵ�
		m_DLCLED4.SetBitmap(hBitMapRed);
		break;
	case 0X53:
		//DLC4�޵����ߣ����Ƶ�
		m_DLCLED4.SetBitmap(hBitMapYellow);
		break;
	default:
		//DLC4 ���ҵƣ�MPO4���ҵ�
		m_DLCLED4.SetBitmap(hBitMapGray);
		break;
	}


	switch (chArrT[4])
	{
	case 0XAA:
		//DLC5 ���̵ƣ�MPO5���ҵ�
		m_DLCLED5.SetBitmap(hBitMapBlue);
		((CButton*)GetDlgItem(IDC_RIO_DLC5))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RIO_MPO5))->SetCheck(FALSE);
		break;
	case 0XA9:
		//DLC5 ���̵ƣ�MPO5���ҵ�
		m_DLCLED5.SetBitmap(hBitMapGreen);
		((CButton*)GetDlgItem(IDC_RIO_DLC5))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RIO_MPO5))->SetCheck(FALSE);
		break;
	case 0XA5:
		//DLC5 ����ƣ�MPO5���ҵ�
		m_DLCLED5.SetBitmap(hBitMapRed);
		break;
	case 0X53:
		//DLC5�޵����ߣ����Ƶ�
		m_DLCLED5.SetBitmap(hBitMapYellow);
		break;
	default:
		//DLC5 ���ҵƣ�MPO5���ҵ�
		m_DLCLED5.SetBitmap(hBitMapGray);
		break;
	}
	switch (chArrT[5])
	{
	case 0XBA:
		m_MPOLED1.SetBitmap(hBitMapBlue);
		((CButton*)GetDlgItem(IDC_RIO_DLC1))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RIO_MPO1))->SetCheck(TRUE);
		break;
	case 0XB9:
		m_MPOLED1.SetBitmap(hBitMapGreen);
		((CButton*)GetDlgItem(IDC_RIO_DLC1))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RIO_MPO1))->SetCheck(TRUE);
		break;
	case 0XB5:
		m_MPOLED1.SetBitmap(hBitMapRed);
		break;
	case 0X54:
		//MPO1�޵����ߣ����Ƶ�
		m_MPOLED1.SetBitmap(hBitMapYellow);
		break;
	default:
		m_MPOLED1.SetBitmap(hBitMapGray);
		break;
	}
	switch (chArrT[6])
	{
	case 0XBA:
		m_MPOLED2.SetBitmap(hBitMapBlue);
		((CButton*)GetDlgItem(IDC_RIO_DLC22))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RIO_MPO22))->SetCheck(TRUE);
		break;
	case 0XB9:
		m_MPOLED2.SetBitmap(hBitMapGreen);
		((CButton*)GetDlgItem(IDC_RIO_DLC22))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RIO_MPO22))->SetCheck(TRUE);
		break;
	case 0XB5:
		m_MPOLED2.SetBitmap(hBitMapRed);
		break;
	case 0X54:
		//MPO2�޵����ߣ����Ƶ�
		m_MPOLED2.SetBitmap(hBitMapYellow);
		break;
	default:
		m_MPOLED2.SetBitmap(hBitMapGray);
		break;
	}
	switch (chArrT[7])
	{
	case 0XBA:
		m_MPOLED3.SetBitmap(hBitMapBlue);
		((CButton*)GetDlgItem(IDC_RIO_DLC3))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RIO_MPO3))->SetCheck(TRUE);
		break;
	case 0XB9:
		m_MPOLED3.SetBitmap(hBitMapGreen);
		((CButton*)GetDlgItem(IDC_RIO_DLC3))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RIO_MPO3))->SetCheck(TRUE);
		break;
	case 0XB5:
		m_MPOLED3.SetBitmap(hBitMapRed);
		break;
	case 0X54:
		//MPO3�޵����ߣ����Ƶ�
		m_MPOLED3.SetBitmap(hBitMapYellow);
		break;
	default:
		m_MPOLED3.SetBitmap(hBitMapGray);
		break;
	}	
	switch (chArrT[8])
	{
	case 0XBA:
		m_MPOLED4.SetBitmap(hBitMapBlue);
		((CButton*)GetDlgItem(IDC_RIO_DLC4))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RIO_MPO4))->SetCheck(TRUE);
		break;
	case 0XB9:
		m_MPOLED4.SetBitmap(hBitMapGreen);
		((CButton*)GetDlgItem(IDC_RIO_DLC4))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RIO_MPO4))->SetCheck(TRUE);
		break;
	case 0XB5:
		m_MPOLED4.SetBitmap(hBitMapRed);
		break;
	case 0X54:
		//MPO4�޵����ߣ����Ƶ�
		m_MPOLED4.SetBitmap(hBitMapYellow);
		break;
	default:
		m_MPOLED4.SetBitmap(hBitMapGray);
		break;
	}	
	switch (chArrT[9])
	{
	case 0XBA:
		m_MPOLED5.SetBitmap(hBitMapBlue);
		((CButton*)GetDlgItem(IDC_RIO_DLC5))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RIO_MPO5))->SetCheck(TRUE);
		break;
	case 0XB9:
		m_MPOLED5.SetBitmap(hBitMapGreen);
		((CButton*)GetDlgItem(IDC_RIO_DLC5))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RIO_MPO5))->SetCheck(TRUE);
		break;
	case 0XB5:
		m_MPOLED5.SetBitmap(hBitMapRed);
		break;
	case 0X54:
		//MPO5�޵����ߣ����Ƶ�
		m_MPOLED5.SetBitmap(hBitMapYellow);
		break;
	default:
		m_MPOLED5.SetBitmap(hBitMapGray);
		break;
	}


	
	UpdateData(FALSE);
}

/************************************************************************************************
Function Name	:	ShowBandRate(unsigned char *pucBandRate)
Explanation		:	��ʾ������ ���·�������Ϣ��
Return Value	:	none
Input Value		:	CString ���ͱ���
Output Value	:	none	
*************************************************************************************************/
void CEDFADlg::ShowBandRate(unsigned char *pucBandRate)
{
	CString cs;
	char BaudRate;
	BaudRate=(int)pucBandRate[7];
	switch (BaudRate>>4)
	{
	case 0:
		cs="9600";
		break;
	case 1:
		cs="19200";
		break;
	case 2:
		cs="38400";
		break;
	case 3:
		cs = "57600";
		break;
	case 4:
		cs="115200";
		break;

	}
	cs+= ",n,8,1" ;
	WriteLog(cs);
	
}

/************************************************************************************************
Function Name	:	ShowChannelData(unsigned char *pucChanData)
Explanation		:	��ʾ5ͨ��DLC ��MPO EEPROM���� DLC�� 1 2 3 4 5 MPO�� 6 7 8 9 A
Return Value	:	none
Input Value		:	pucChanData
Output Value	:	none	
*************************************************************************************************/
void CEDFADlg ::ShowChannelData(unsigned char *pucChanData)
{
	CString cs,str;
	unsigned char channel,blocknum;
	int Datalen;
	unsigned char chArrT[50] = {0};
	cs="";
	/********0X01 11 21 31���ֽ�blocknum�ǿ��0~3 ���ֽ�channel��ͨ����1~A*************/
	channel = pucChanData[7]&0X0F;
	blocknum = pucChanData[7]&0XF0;
	blocknum = blocknum>>4;
	/****���յ�֡���ܽ���MessageBox�ж�****/
// 	if (blocknum!=0X00&&blocknum!=0X01&&blocknum!=0X02)
// 	{
// 		MessageBox("Block Num Error","Block Error",MB_OK);
// 		return;
// 	}
	

	//1��ʾ16H 19H FC ͨ����+��� DATA ���Լ�ȥ4ΪDATA����
	//DATA  �е�һλ��ʾͨ���� ��ߴ�������
	Datalen = (int)pucChanData[1]-4;
//	channel = pucChanData[7];
	for (int i=0;i<Datalen;i++)
	{
		chArrT[i] = pucChanData[i+8];
		str.Format("%02X",chArrT[i]);
		cs+=str;
	}
	switch (channel)
	{
		case 0X01:
			((CButton *)GetDlgItem(IDC_RIO_DLC1))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RIO_MPO1))->SetCheck(FALSE);
			if (blocknum==0x00)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block1_0))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_3))->SetCheck(FALSE);

			}
			if (blocknum==0x01)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block1_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_1))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_3))->SetCheck(FALSE);


			}
			if (blocknum==0x02)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block1_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_2))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_3))->SetCheck(FALSE);
			}
			if (blocknum==0x03)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block1_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_3))->SetCheck(TRUE);
			}
			GetDlgItem(IDC_EDIT_CH1) ->SetWindowText(cs);
			break;
		case 0X02:
			((CButton *)GetDlgItem(IDC_RIO_DLC22))->SetCheck(TRUE); //ѡ��DLC2
			((CButton *)GetDlgItem(IDC_RIO_MPO22))->SetCheck(FALSE);
			if (blocknum==0x00)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block2_0))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_3))->SetCheck(FALSE);

			}
			if (blocknum==0x01)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block2_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_1))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_3))->SetCheck(FALSE);

			}
			if (blocknum==0x02)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block2_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_2))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_3))->SetCheck(FALSE);
			}
			if (blocknum==0x03)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block2_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_3))->SetCheck(TRUE);
			}
			GetDlgItem(IDC_EDIT_CH2) ->SetWindowText(cs);
			break;
		case 0X03:
			((CButton *)GetDlgItem(IDC_RIO_DLC3))->SetCheck(TRUE); //ѡ��DLC3
			((CButton *)GetDlgItem(IDC_RIO_MPO3))->SetCheck(FALSE);
			if (blocknum==0x00)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block3_0))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_3))->SetCheck(FALSE);

			}
			if (blocknum==0x01)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block3_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_1))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_3))->SetCheck(FALSE);

			}
			if (blocknum==0x02)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block3_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_2))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_3))->SetCheck(FALSE);
			}
			if (blocknum==0x03)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block3_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_3))->SetCheck(TRUE);
			}
			GetDlgItem(IDC_EDIT_CH3) ->SetWindowText(cs);
			break;
		case 0X04:
			((CButton *)GetDlgItem(IDC_RIO_DLC4))->SetCheck(TRUE); //ѡ��DLC4
			((CButton *)GetDlgItem(IDC_RIO_MPO4))->SetCheck(FALSE);
			if (blocknum==0x00)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block4_0))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_3))->SetCheck(FALSE);
			}
			if (blocknum==0x01)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block4_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_1))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_3))->SetCheck(FALSE);
			}
			if (blocknum==0x02)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block4_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_2))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_3))->SetCheck(FALSE);
			}
			if (blocknum==0x03)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block4_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_3))->SetCheck(TRUE);
			}

			GetDlgItem(IDC_EDIT_CH4) ->SetWindowText(cs);
			break;
		case 0X05:
			((CButton *)GetDlgItem(IDC_RIO_DLC5))->SetCheck(TRUE); //ѡ��DLC5
			((CButton *)GetDlgItem(IDC_RIO_MPO5))->SetCheck(FALSE);
			if (blocknum==0x00)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block5_0))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_3))->SetCheck(FALSE);
			}
			if (blocknum==0x01)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block5_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_1))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_3))->SetCheck(FALSE);
			}
			if (blocknum==0x02)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block5_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_2))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_3))->SetCheck(FALSE);
			}
			if (blocknum==0x03)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block5_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_3))->SetCheck(TRUE);
			}
			GetDlgItem(IDC_EDIT_CH5) ->SetWindowText(cs);
			break;
		case 0X06:
			((CButton*)GetDlgItem(IDC_RIO_MPO1))->SetCheck(TRUE);//ѡ��MPO1
			((CButton *)GetDlgItem(IDC_RIO_DLC1))->SetCheck(FALSE);
			if (blocknum==0x00)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block1_0))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_3))->SetCheck(FALSE);

			}
			if (blocknum==0x01)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block1_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_1))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_3))->SetCheck(FALSE);

			}
			if (blocknum==0x02)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block1_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_2))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_3))->SetCheck(FALSE);
			}
			if (blocknum==0x03)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block1_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block1_3))->SetCheck(TRUE);
			}
			GetDlgItem(IDC_EDIT_CH1) ->SetWindowText(cs);
			break;
		case 0X07:			
			((CButton*)GetDlgItem(IDC_RIO_MPO22))->SetCheck(TRUE);//ѡ��MPO2
			((CButton *)GetDlgItem(IDC_RIO_DLC22))->SetCheck(FALSE);
			if (blocknum==0x00)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block2_0))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_3))->SetCheck(FALSE);
			}
			if (blocknum==0x01)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block2_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_1))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_3))->SetCheck(FALSE);

			}
			if (blocknum==0x02)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block2_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_2))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_3))->SetCheck(FALSE);
			}
			if (blocknum==0x03)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block2_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block2_3))->SetCheck(TRUE);
			}
			GetDlgItem(IDC_EDIT_CH2) ->SetWindowText(cs);
			break;
		case 0X08:
			((CButton*)GetDlgItem(IDC_RIO_MPO3)) ->SetCheck(TRUE);//ѡ��MPO3
			((CButton *)GetDlgItem(IDC_RIO_DLC3))->SetCheck(FALSE);
			if (blocknum==0x00)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block3_0))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_3))->SetCheck(FALSE);

			}
			if (blocknum==0x01)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block3_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_1))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_3))->SetCheck(FALSE);

			}
			if (blocknum==0x02)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block3_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_2))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_3))->SetCheck(FALSE);
			}
			if (blocknum==0x03)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block3_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block3_3))->SetCheck(TRUE);
			}

			GetDlgItem(IDC_EDIT_CH3) ->SetWindowText(cs);			
			break;
		case 0X09:
			((CButton*)GetDlgItem(IDC_RIO_MPO4))->SetCheck(TRUE);//ѡ��MPO4
			((CButton *)GetDlgItem(IDC_RIO_DLC4))->SetCheck(FALSE);
			if (blocknum==0x00)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block4_0))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_3))->SetCheck(FALSE);

			}
			if (blocknum==0x01)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block4_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_1))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_3))->SetCheck(FALSE);
			}
			if (blocknum==0x02)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block4_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_2))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_3))->SetCheck(FALSE);
			}
			if (blocknum==0x03)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block4_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block4_3))->SetCheck(TRUE);
			}
			GetDlgItem(IDC_EDIT_CH4) ->SetWindowText(cs);
			break;
		case 0X0A:
			((CButton*)GetDlgItem(IDC_RIO_MPO5))->SetCheck(TRUE);//ѡ��MPO5
			((CButton *)GetDlgItem(IDC_RIO_DLC5))->SetCheck(FALSE);
			if (blocknum==0x00)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block5_0))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_3))->SetCheck(FALSE);
			}
			if (blocknum==0x01)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block5_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_1))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_3))->SetCheck(FALSE);

			}
			if (blocknum==0x02)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block5_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_2))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_3))->SetCheck(FALSE);
			}
			if (blocknum==0x03)
			{
				((CButton *)GetDlgItem(IDC_RIO_Block5_0))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_1))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_2))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_RIO_Block5_3))->SetCheck(TRUE);
			}
			GetDlgItem(IDC_EDIT_CH5) ->SetWindowText(cs);
			break;
			
		default:
			MessageBox( "Channel Error", "Format Error", MB_ICONERROR ) ;
			ClearEditBox();
			break;
	}

		
}
/************************************************************************************************
Function Name	:	ShowRFIDData(unsigned char *pucChanData)
Explanation		:	��ʾ5ͨ��RFID���� RFID�� 1 2 3 4 5 
Return Value	:	none
Input Value		:	pucChanData
Output Value	:	none	
*************************************************************************************************/
void CEDFADlg :: ShowRFIDData(unsigned char *pucChanData)
{
	CString cs,str;
	int Datalen;
	unsigned char channel/*,blocknum*/;
	unsigned char chArrT[50] = {0};
	cs="";
/********0X01 11 21 ���ֽ�blocknum�ǿ��0~2 ���ֽ�channel��ͨ����1~5*************/
	//1��ʾ16H 19H FC ͨ����+��� DATA ���Լ�ȥ4ΪDATA����
	
	Datalen = (int)pucChanData[1]-4;
	channel = pucChanData[7]&0X0F;
// 	blocknum = pucChanData[7]&0XF0;
// 	blocknum = blocknum>>4;
	
	for (int i=0;i<Datalen;i++)
	{
		chArrT[i] = pucChanData[i+8];
		str.Format("%02X",chArrT[i]);
		cs+=str;
	

	}
	switch (channel)
	{
		case 0X01:
			((CButton*)GetDlgItem(IDC_CHK_RF1))->SetCheck(TRUE);
			GetDlgItem(IDC_EDIT_RFID1) ->SetWindowText(cs);
			break;
		case 0X02:
			((CButton*)GetDlgItem(IDC_CHK_RF2))->SetCheck(TRUE);
			GetDlgItem(IDC_EDIT_RFID2) ->SetWindowText(cs);
			break;
		case 0X03:
			((CButton*)GetDlgItem(IDC_CHK_RF3))->SetCheck(TRUE);
			GetDlgItem(IDC_EDIT_RFID3) ->SetWindowText(cs);
			break;
		case 0X04:
			((CButton*)GetDlgItem(IDC_CHK_RF4))->SetCheck(TRUE);
			GetDlgItem(IDC_EDIT_RFID4) ->SetWindowText(cs);
			break;
		case 0X05:
			((CButton*)GetDlgItem(IDC_CHK_RF5))->SetCheck(TRUE);
			GetDlgItem(IDC_EDIT_RFID5) ->SetWindowText(cs);
			break;
				
		default:
			MessageBox( "Channel Error", "Format Error", MB_ICONERROR ) ;
			ClearEditBox();
			break;
	}
}
/************************************************************************************************
Function Name	:	ShowError(unsigned char *pucChanData)
Explanation		:	��ʾ������Ϣ 
Return Value	:	none
Input Value		:	pucChanData
Output Value	:	none	
*************************************************************************************************/
void CEDFADlg::ShowError(unsigned char *pucData)
{
	unsigned char chArrT,chchannel;
	chchannel = pucData[7];
	chArrT = pucData[8];
	CString str;
	
	if (chchannel == 0XFF)
	{
		WriteLog("Communication error or No RFID,please try again");
		
	}
	else
	{
		switch (chArrT)
		{
			case 0X51:
				str.Format("%02X",chchannel);
				str = "Channel "+ str +"  without ETDLC";
				WriteLog(str);
				break;
			case 0X52:
				str.Format("%02X",chchannel-0X05);
				str = "Channel "+ str +"  without ETMPO";
				WriteLog(str);
				break;
			case 0X53:
				str.Format("%02X",chchannel);
				str = "ETDLC "+ str +"  without EEPROM";
				WriteLog(str);
				break;
			case 0X54:
				str.Format("%02X",chchannel-0X05);
				str = "ETMPO "+ str +"  without EEPROM";
				WriteLog(str);
				break;
			default:
				WriteLog("Unknown Error");
				break;			
		}
	
	}
	
}





/************************************************************************************************
Function Name	:	CheckPort()
Explanation		:	��⴮���Ƿ��TRUE��δ�򿪷���FALSE
Return Value	:	none
Input Value		:	none
Output Value	:	TRUE ��FALSE	
*************************************************************************************************/
BOOL CEDFADlg :: CheckPort()
{

		if (!m_ctrlComm.GetPortOpen())
		{
			MessageBox( "The serial port has not been opened", "Serial Port Error", MB_ICONERROR ) ;
			WriteLog("Serial Port Error");
			KillTimer( TIMER_SHOW_MONITOR ); 
			((CButton*)GetDlgItem(IDC_Check_Auto))->SetCheck(0);
			return FALSE;
		}
		else
		{
			return TRUE;
		}



	
}


/************************************************************************************************
Function Name	:	WriteLog
Explanation		:	��ʾ״̬ ���·�������Ϣ�У�д���״̬
Return Value	:	none
Input Value		:	CString ���ͱ���
Output Value	:	none	
*************************************************************************************************/
void CEDFADlg::WriteLog(CString cs)
{
	//cs+="\r\n";
	GetDlgItem( IDC_EDIT_READCONTENT )->SetWindowText( cs ) ;
}

void CEDFADlg::OnButtonOnekeywrite() 
{
	// TODO: Add your control notification handler code here
	//WriteLog("�������񶫰�");
	if (!CheckPort())
	{
		return;

	}
		if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}

	
	try
	{
	
		if (GetDlgItem(IDC_EDIT_CH1)->GetWindowTextLength()>0)
		{
			this->OnBtnChnW1();
			this->Time1(800);
		}
		if (GetDlgItem(IDC_EDIT_CH2)->GetWindowTextLength()>0)
		{
			this->OnBtnChnW2();
			this->Time1(800);
		}
		if (GetDlgItem(IDC_EDIT_CH3)->GetWindowTextLength()>0)
		{
			this->OnBtnChnW3();
			this->Time1(800);
		}
		if (GetDlgItem(IDC_EDIT_CH4)->GetWindowTextLength()>0)
		{
			this->OnBtnChnW4();
			this->Time1(800);
		}
		if (GetDlgItem(IDC_EDIT_CH5)->GetWindowTextLength()>0)
		{
			this->OnBtnChnW5();
			this->Time1(800);
		}
		WriteLog("One-key Writed!!");
		MessageBox("One-key Write Success","Success",MB_OK);
	
	}

	catch (CException* e)
	{
		AfxMessageBox("Unknown Exception������");
	}

	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}

}

void CEDFADlg::ClearEditBox()
{
	GetDlgItem( IDC_EDIT_CH1 )->SetWindowText( "" ) ;
	GetDlgItem( IDC_EDIT_CH2 )->SetWindowText( "" ) ;
	GetDlgItem( IDC_EDIT_CH3 )->SetWindowText( "" ) ;
	GetDlgItem( IDC_EDIT_CH4 )->SetWindowText( "" ) ;
	GetDlgItem( IDC_EDIT_CH5 )->SetWindowText( "" ) ;

	GetDlgItem( IDC_EDIT_RFID1 )->SetWindowText( "" ) ;
	GetDlgItem( IDC_EDIT_RFID2 )->SetWindowText( "" ) ;
	GetDlgItem( IDC_EDIT_RFID3 )->SetWindowText( "" ) ;
	GetDlgItem( IDC_EDIT_RFID4 )->SetWindowText( "" ) ;
	GetDlgItem( IDC_EDIT_RFID5 )->SetWindowText( "" ) ;

	


}

void CEDFADlg::OnCheckAuto() 
{
	// TODO: Add your control notification handler code here
	if (m_Auto.GetCheck() == TRUE)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	} 
	else
	{
		KillTimer( TIMER_SHOW_MONITOR );   // �����ѡ����ȡ��ѡ�еĲ�����ֹͣ���е�MONITOR��ȡ����ʾ
		this->time_flag = Stopping;
	}
	
}

void CEDFADlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case TIMER_SHOW_MONITOR:
		/*this->OnButtonOnekeyreceive();*/
		if (!CheckPort())
		{
			return;

		}
		this->time_flag = Timing;
		//1 ��ͷ����״̬��ȡ
		BYTE btArrT[15] = { 0 } ;
		btArrT[0] = 0X68 ;
		btArrT[1] = 0X04;
		btArrT[2] = 0X04;
		btArrT[3] = 0X68 ;
		btArrT[4] = 0X16 ;
		btArrT[5] = 0X19 ;
		btArrT[6] = 0XC3 ;
		btArrT[7] = 0XFF ;
		btArrT[8] = GetCheckSum( btArrT+4, 4 ) ;
		btArrT[9] = 0X16 ;
		this->COMSendData( btArrT, 10 ) ;
		this ->WriteTxtLog( btArrT,10,1 );
		break;
	}
	CDialog::OnTimer(nIDEvent);
}





void CEDFADlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	if(nType!=SIZE_MINIMIZED&&cx>=1000&&cx<=2000&&cy>=700&&cy<=1400 )  //�жϴ����ǲ�����С���ˣ���Ϊ������С��֮�� �����ڵĳ��Ϳ����0����ǰһ�α仯��ʱ�ͻ���ֳ���0�Ĵ������
    {
        ReSize();
    }
	
// 	if(nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)//�����С�����䶯��������resize
// 	 {
// 		 ReSize();
// 	 }
}

void CEDFADlg::ReSize()
{
	float fsp[2];	//��¼���ű���new/old
	
	POINT Newp;		//��ȡ���ڶԻ���Ĵ�С
	CRect recta;
	GetClientRect(&recta);		//��ȡ�ͻ�����С
	
	Newp.x=recta.right-recta.left;
	Newp.y=recta.bottom-recta.top;

	fsp[0]=(float)Newp.x/old.x;		//X�����ű���
	fsp[1]=(float)Newp.y/old.y;		//Y�����ű���
	CRect temRect;
	int IDnum;			//��ȡ�ɣĺ�
	CPoint oldTopLeftPoint,newTopLeftPoint;		//���Ͻ�
	CPoint oldBottomRightPoint,newBottomRightPoint;	//���½�
/************************************************************************/
/* ͨ��hwndChild=::GetWindow(m_hWnd,GW_CHILD);
   ��::GetWindow(hwndChild, GW_HWNDNEXT); �г����пؼ� 
   Ҳ������ض��ؼ��������С
*/
/************************************************************************/
	HWND hwndChild = ::GetWindow(m_hWnd,GW_CHILD);//�г����пؼ�
	while(hwndChild)
	{
		IDnum = ::GetDlgCtrlID(hwndChild);	//ȡ��ID
		GetDlgItem(IDnum)->GetWindowRect(temRect);
		ScreenToClient(temRect);
		oldTopLeftPoint = temRect.TopLeft();
			newTopLeftPoint.x = long(oldTopLeftPoint.x * fsp[0]);
			newTopLeftPoint.y = long(oldTopLeftPoint.y * fsp[1]);
		oldBottomRightPoint = temRect.BottomRight();
			newBottomRightPoint.x = long(oldBottomRightPoint.x * fsp[0]);
			newBottomRightPoint.y = long(oldBottomRightPoint.y * fsp[1]);
		temRect.SetRect(newTopLeftPoint,newBottomRightPoint);
		GetDlgItem(IDnum)->MoveWindow(temRect,TRUE);
		hwndChild = ::GetWindow(hwndChild,GW_HWNDNEXT);

	}
	old = Newp;
		
	

	
	

	
	
}
/************************************************************************/
/*
�������ܣ����ô��ڵĳߴ�����ֵ����Сֵ
������Ҫ�����ڽ�Border���ó�Resizing���Ե�ʱ���������ı䴰�ڵĴ�С����OnSize()����һֱִ��
Ϊ�˴����������ף����Կ��ƴ���ߴ��С�øú���OnGetMinMaxInfo()��������Ϣ��ӦWM_GETMINMAXINFO��Ϣ��
��������Dialog���� �޷��ҵ�����Ϣ��Ӧ����ʱ�������취
1.�ֶ����
2.��ClassWizard��class info�½�Message filter��Dialog��Ϊwindow

                                                                      */
/************************************************************************/
void CEDFADlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	//cx>=1000&&cx<=2000&&cy>=700&&cy<=1400
	lpMMI ->ptMinTrackSize = CPoint( 1000, 760 );
	lpMMI ->ptMaxTrackSize = CPoint(1600,1200);
	
	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CEDFADlg::OnBtnChnW1() 
{
	// TODO: Add your control notification handler code here
	CString str;
	char chArrTxt[100] = {0};
	BYTE chArrBxt[100] = {0};
/*	WriteLog("������");*/
// ����ע��
	if (!CheckPort())
 	{
 		return;
 
 	}
	if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}

	//�ٽ�����Դ����
	critical_section.Lock();
	//��ȡIDC_EDIT_DLC1�е�����
	GetDlgItem(IDC_EDIT_CH1)->GetWindowText(str);

	//��ȡ���ݳ���

	int len = str.GetLength();

	if (len>64)
	{
		MessageBox( "Data length limited 32 bytes!", "Data length ERROR", MB_OK );
		return;
	}
/********��ȡ���� ��������ݳ���Ϊ65 ��(32)*2+/0 ******/
	GetDlgItem( IDC_EDIT_CH1 )->GetWindowText( chArrTxt, 65 );
	//int iNameLen = strlen(chArrTxt);

		
		CByteArray DATA;
		

		BYTE btArrT[42] = { 0 } ;
		btArrT[0] = 0X68 ;
		btArrT[1] = 36 ;
		btArrT[2] = 36 ;
		btArrT[3] = 0X68 ;
		btArrT[4] = 0X16 ;
		btArrT[5] = 0X19 ;
		btArrT[6] = 0XC5 ;//�������� DLC
		if (((CButton *)GetDlgItem(IDC_RIO_DLC1))->GetCheck())
			{
				if (((CButton *)GetDlgItem(IDC_RIO_Block1_0))->GetCheck())
				{
					btArrT[7] = 0X01 ;//01 11 21 31
				}
				if (((CButton *)GetDlgItem(IDC_RIO_Block1_1))->GetCheck())
				{
					btArrT[7] = 0X11 ;//01 11 21 31
				}
				if (((CButton *)GetDlgItem(IDC_RIO_Block1_2))->GetCheck())
				{
					btArrT[7] = 0X21 ;//01 11 21 31
				}
				/**����д��block3**/
				if (((CButton*)GetDlgItem(IDC_RIO_Block1_3))->GetCheck())
				{
					btArrT[7] = 0X31 ;//01 11 21 31

				}
				
				
			}
			if (((CButton*)GetDlgItem(IDC_RIO_MPO1)) ->GetCheck())
			{
				
				if (((CButton *)GetDlgItem(IDC_RIO_Block1_0))->GetCheck())
				{
					btArrT[7] = 0X06 ;//06 16 26 36
				}
				if (((CButton *)GetDlgItem(IDC_RIO_Block1_1))->GetCheck())
				{
					btArrT[7] = 0X16 ;//06 16 26 36
				}
				if (((CButton *)GetDlgItem(IDC_RIO_Block1_2))->GetCheck())
				{
					btArrT[7] = 0X26 ;//06 16 26 36
				}
				/**����д��block3**/
				if (((CButton*)GetDlgItem(IDC_RIO_Block1_3))->GetCheck())
				{
					btArrT[7] = 0X36 ;//06 16 26 36
				}
			}
		for (int n=0 ;n<64;n++)
		{
			chArrBxt[n] = chArrTxt[n];
		}
		int datalenth = Str2Hex(chArrBxt,DATA);
		for( int i = 0 ; i < datalenth ; i++ )
		{
			/*hexData.SetAt( i+7, DATA[i] ) ;*/
			btArrT[i+8] = DATA[i];
		}
		btArrT[datalenth+8] = GetCheckSum(btArrT+4,datalenth+4);
		btArrT[41] = 0X16;
		/*���ڷ��͵���ʹ�� ����ע�͵���*/
		this->COMSendData( btArrT, 42 ) ;
		this->WriteTxtLog( btArrT, 42 ,1);
		DATA.RemoveAll() ;
		//�ͷ��ٽ�����Դ
		critical_section.Unlock(); 
	
		//this->COMSendData( btArrT, 42 ) ;

//		ShowChannelData(btArrT);
		this->Time1(1000);
		//MessageBox("Sending������","Sending",MB_OK);
/*****��Ƶ���ݷ��� ��EEPROM���ݷ���ͬ������********/
		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHK_RF1))->GetCheck())
		{
			//�ٽ�����Դ����
			critical_section.Lock();
			GetDlgItem(IDC_EDIT_RFID1) -> GetWindowText(str);
			len = str.GetLength();
			memset(chArrTxt,0,100);

			if (len>64)
			{
				MessageBox( "Data length limited 32 bytes!", "Data length ERROR", MB_OK );
				return;
			}
			GetDlgItem(IDC_EDIT_RFID1) ->GetWindowText(chArrTxt,65);


			
			BYTE btArrTRFID[42] = { 0 } ;
			btArrTRFID[0] = 0X68 ;
			btArrTRFID[1] = 36 ;
			btArrTRFID[2] = 36 ;
			btArrTRFID[3] = 0X68 ;
			btArrTRFID[4] = 0X16 ;
			btArrTRFID[5] = 0X19 ;
			btArrTRFID[6] = 0XC7 ;//RF�������� DLC
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_0))->GetCheck())
			{
				btArrTRFID[7] = 0X01 ;//01 11 21 31
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_1))->GetCheck())
			{
				btArrTRFID[7] = 0X11 ;//01 11 21 31
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_2))->GetCheck())
			{
				btArrTRFID[7] = 0X21 ;//01 11 21 31
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_3))->GetCheck())
			{
				btArrTRFID[7] = 0X31 ;//01 11 21 31
			}

			for ( n=0 ;n<64;n++)
			{
				chArrBxt[n] = chArrTxt[n];
			}
			 datalenth = Str2Hex(chArrBxt,DATA);
			for( i = 0 ; i < datalenth ; i++ )
			{
				btArrTRFID[i+8] = DATA[i];
			}
			btArrTRFID[datalenth+8] = GetCheckSum(btArrTRFID+4,datalenth+4);
			btArrTRFID[41] = 0X16;
			

			//ShowRFIDData(btArrT);
			/*���ڷ��͵���ʹ�� ����ע�͵���*/
			
			
			this->COMSendData( btArrTRFID, 42 ) ;
			this->WriteTxtLog( btArrTRFID, 42 ,1);
			//�ͷ��ٽ�����Դ
			critical_section.Unlock(); 
			this->Time1(3000);
			
			
		}

	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}


}

void CEDFADlg::OnBtnChnR1() 
{
	// TODO: Add your control notification handler code here
	//WriteLog("������1");
	if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}
	if (!CheckPort())
	{
		return;

	}
	
	try
	{	
		//1 ��ͷ����״̬��ȡ
		//�ٽ�����Դ����
		critical_section.Lock();

		BYTE btArrT[2] = { 0 } ;
		
		btArrT[0] = 0XC4 ;
/************************************************************************/
/*������һ���ֽڣ�����λȡֵ0XH/1XH/2XH��������������š�
����λȡֵ1-A������Ҫ��ȡ��ͨ���š�1-5��ӦDLC1-DLC5��6-A��ӦMPO1-MPO5��
		*/
/************************************************************************/
		if (((CButton *)GetDlgItem(IDC_RIO_DLC1))->GetCheck())
		{
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_0))->GetCheck())
			{
				btArrT[1] = 0X01 ;//01 11 21 31
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_1))->GetCheck())
			{
				btArrT[1] = 0X11 ;//01 11 21 31
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_2))->GetCheck())
			{
				btArrT[1] = 0X21 ;//01 11 21 31
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_3))->GetCheck())
			{
				btArrT[1] = 0X31 ;//01 11 21 31
			}
			
			
		}
		if (((CButton*)GetDlgItem(IDC_RIO_MPO1)) ->GetCheck())
		{
			
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_0))->GetCheck())
			{
				btArrT[1] = 0X06 ;//06 16 26 36
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_1))->GetCheck())
			{
				btArrT[1] = 0X16 ;//06 16 26 36 
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_2))->GetCheck())
			{
				btArrT[1] = 0X26 ;//06 16 26 36
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_3))->GetCheck())
			{
				btArrT[1] = 0X36 ;//06 16 26 36
			}
		}
		
			StdDataSend(btArrT);
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(800);
//�ж�RF��check box�Ƿ�ѡ�з�����Ƶ���ݶ�ȡ��־
		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHK_RF1))->GetCheck())
		{
			//�ٽ�����Դ����
			critical_section.Lock(); 
			btArrT[0] = 0XC6;
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_0))->GetCheck())
			{
				btArrT[1] = 0X01 ;//01 11 21
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_1))->GetCheck())
			{
				btArrT[1] = 0X11 ;//01 11 21
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_2))->GetCheck())
			{
				btArrT[1] = 0X21 ;//01 11 21
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block1_3))->GetCheck())
			{
				btArrT[1] = 0X31 ;//01 11 21
			}
			
			StdDataSend(btArrT);
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(2500);
			

		}
	}
	catch (CException* e)
	{
		AfxMessageBox("Unknown Exception������");
	}

	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}
	
}

void CEDFADlg::OnBtnChnR2() 
{
	// TODO: Add your control notification handler code here
/*	WriteLog("������2");*/
	if (!CheckPort())
	{
		return;

	}
	if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}

	try
	{	
		//�ٽ�����Դ����
		critical_section.Lock(); 
		BYTE btArrT[2] = { 0 } ;
		
		btArrT[0] = 0XC4 ;
/************************************************************************/
/*������һ���ֽڣ�����λȡֵ0XH/1XH/2XH��������������š�
����λȡֵ1-A������Ҫ��ȡ��ͨ���š�1-5��ӦDLC1-DLC5��6-A��ӦMPO1-MPO5��
		*/
/************************************************************************/
		if (((CButton *)GetDlgItem(IDC_RIO_DLC22))->GetCheck())
		{
			btArrT[1] = 0X02 ;//02 12 22
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_0))->GetCheck())
			{
				btArrT[1] = 0X02 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_1))->GetCheck())
			{
				btArrT[1] = 0X12 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_2))->GetCheck())
			{
				btArrT[1] = 0X22 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_3))->GetCheck())
			{
				btArrT[1] = 0X32 ;//02 12 22 32
			}
		}
		if (((CButton*)GetDlgItem(IDC_RIO_MPO22)) ->GetCheck())
		{
			btArrT[1] = 0X07 ;//07 17 27
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_0))->GetCheck())
			{
				btArrT[1] = 0X07 ;//07 17 27
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_1))->GetCheck())
			{
				btArrT[1] = 0X17 ;//07 17 27
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_2))->GetCheck())
			{
				btArrT[1] = 0X27 ;//07 17 27
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_3))->GetCheck())
			{
				btArrT[1] = 0X37 ;//07 17 27 37
			}

		}
		
		
			StdDataSend(btArrT);
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(800);
//�ж�RF��check box�Ƿ�ѡ�з�����Ƶ���ݶ�ȡ��־
		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHK_RF2))->GetCheck())
		{
			//�ٽ�����Դ����
			critical_section.Lock();
			btArrT[0] = 0XC6;
			btArrT[1] = 0X02;//02 12 22
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_0))->GetCheck())
			{
				btArrT[1] = 0X02 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_1))->GetCheck())
			{
				btArrT[1] = 0X12 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_2))->GetCheck())
			{
				btArrT[1] = 0X22 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_3))->GetCheck())
			{
				btArrT[1] = 0X32 ;//02 12 22 32
			}
			StdDataSend(btArrT);
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(2500);
			

		}
	}
	catch (CException* e)
	{
		AfxMessageBox("Unknown Exception������");
	}

	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}
	
}

void CEDFADlg::OnBtnChnR3() 
{
	// TODO: Add your control notification handler code here
// 	WriteLog("������3");
	if (!CheckPort())
	{
		return;

	}

	if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}
	//�ٽ�����Դ����
	critical_section.Lock();
	BYTE btArrT[2] = { 0 } ;
		
		btArrT[0] = 0XC4 ;
/************************************************************************/
/*������һ���ֽڣ�����λȡֵ0XH/1XH/2XH��������������š�
����λȡֵ1-A������Ҫ��ȡ��ͨ���š�1-5��ӦDLC1-DLC5��6-A��ӦMPO1-MPO5��
		*/
/************************************************************************/
		if (((CButton *)GetDlgItem(IDC_RIO_DLC3))->GetCheck())
		{
			btArrT[1] = 0X03 ;//03 13 23
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_0))->GetCheck())
			{
				btArrT[1] = 0X03 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_1))->GetCheck())
			{
				btArrT[1] = 0X13 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_2))->GetCheck())
			{
				btArrT[1] = 0X23 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_3))->GetCheck())
			{
				btArrT[1] = 0X33 ;//03 13 23 33
			}
		}
		if (((CButton*)GetDlgItem(IDC_RIO_MPO3)) ->GetCheck())
		{
			btArrT[1] = 0X08 ;//08 18 28
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_0))->GetCheck())
			{
				btArrT[1] = 0X08 ;//08 18 28
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_1))->GetCheck())
			{
				btArrT[1] = 0X18 ;//08 18 28
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_2))->GetCheck())
			{
				btArrT[1] = 0X28 ;//08 18 28
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_3))->GetCheck())
			{
				btArrT[1] = 0X38 ;//08 18 28 38
			}
		}
		
			StdDataSend(btArrT);

			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(800);
//�ж�RF��check box�Ƿ�ѡ�з�����Ƶ���ݶ�ȡ��־
		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHK_RF3))->GetCheck())
		{
			//�ٽ�����Դ����
			critical_section.Lock(); 
			btArrT[0] = 0XC6;
			btArrT[1] = 0X03;//03 13 23
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_0))->GetCheck())
			{
				btArrT[1] = 0X03 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_1))->GetCheck())
			{
				btArrT[1] = 0X13 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_2))->GetCheck())
			{
				btArrT[1] = 0X23 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_3))->GetCheck())
			{
				btArrT[1] = 0X33 ;//03 13 23 33
			}
			StdDataSend(btArrT);

			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(2500);
			

		}

	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}	


}

void CEDFADlg::OnBtnChnR4() 
{
	// TODO: Add your control notification handler code here
/*	WriteLog("������4");*/
	if (!CheckPort())
	{
		return;

	}

	if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}

	//�ٽ�����Դ����
	critical_section.Lock();
	BYTE btArrT[2] = { 0 } ;
		
		btArrT[0] = 0XC4 ;
/************************************************************************/
/*������һ���ֽڣ�����λȡֵ0XH/1XH/2XH��������������š�
����λȡֵ1-A������Ҫ��ȡ��ͨ���š�1-5��ӦDLC1-DLC5��6-A��ӦMPO1-MPO5��
		*/
/************************************************************************/
		if (((CButton *)GetDlgItem(IDC_RIO_DLC4))->GetCheck())
		{
			btArrT[1] = 0X04 ;//04 14 24
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_0))->GetCheck())
			{
				btArrT[1] = 0X04 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_1))->GetCheck())
			{
				btArrT[1] = 0X14 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_2))->GetCheck())
			{
				btArrT[1] = 0X24 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_3))->GetCheck())
			{
				btArrT[1] = 0X34 ;//04 14 24 34
			}
		}
		if (((CButton*)GetDlgItem(IDC_RIO_MPO4)) ->GetCheck())
		{
			btArrT[1] = 0X09 ;//09 19 29
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_0))->GetCheck())
			{
				btArrT[1] = 0X09 ;//09 19 29
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_1))->GetCheck())
			{
				btArrT[1] = 0X19 ;//09 19 29
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_2))->GetCheck())
			{
				btArrT[1] = 0X29 ;//09 19 29
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_3))->GetCheck())
			{
				btArrT[1] = 0X39 ;//09 19 29 39
			}

		}
		
			StdDataSend(btArrT);
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(800);
//�ж�RF��check box�Ƿ�ѡ�з�����Ƶ���ݶ�ȡ��־
		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHK_RF4))->GetCheck())
		{
			//�ٽ�����Դ����
			critical_section.Lock();  
			btArrT[0] = 0XC6;
			btArrT[1] = 0X04;//04 14 24
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_0))->GetCheck())
			{
				btArrT[1] = 0X04 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_1))->GetCheck())
			{
				btArrT[1] = 0X14 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_2))->GetCheck())
			{
				btArrT[1] = 0X24 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_3))->GetCheck())
			{
				btArrT[1] = 0X34 ;//04 14 24 34
			}
			StdDataSend(btArrT);
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(2500);
		}
	
	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}


}

void CEDFADlg::OnBtnChnR5() 
{
	// TODO: Add your control notification handler code here
/*	WriteLog("������5");*/
		if (!CheckPort())
	{
		return;

	}
	if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}
	//�ٽ�����Դ����
	critical_section.Lock(); 
	BYTE btArrT[2] = { 0 } ;
		
		btArrT[0] = 0XC4 ;
/************************************************************************/
/*������һ���ֽڣ�����λȡֵ0XH/1XH/2XH��������������š�
����λȡֵ1-A������Ҫ��ȡ��ͨ���š�1-5��ӦDLC1-DLC5��6-A��ӦMPO1-MPO5��
		*/
/************************************************************************/
		if (((CButton *)GetDlgItem(IDC_RIO_DLC5))->GetCheck())
		{
			btArrT[1] = 0X05 ;//05 15 25
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_0))->GetCheck())
			{
				btArrT[1] = 0X05 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_1))->GetCheck())
			{
				btArrT[1] = 0X15 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_2))->GetCheck())
			{
				btArrT[1] = 0X25 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_3))->GetCheck())
			{
				btArrT[1] = 0X35 ;//05 15 25 35
			}

		}
		if (((CButton*)GetDlgItem(IDC_RIO_MPO5)) ->GetCheck())
		{
			btArrT[1] = 0X0A ;//0A 1A 2A
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_0))->GetCheck())
			{
				btArrT[1] = 0X0A ;//0A 1A 2A
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_1))->GetCheck())
			{
				btArrT[1] = 0X1A ;//0A 1A 2A
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_2))->GetCheck())
			{
				btArrT[1] = 0X2A ;//0A 1A 2A
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_3))->GetCheck())
			{
				btArrT[1] = 0X3A ;//0A 1A 2A 3A
			}
		}
		
			StdDataSend(btArrT);
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(800);
//�ж�RF��check box�Ƿ�ѡ�з�����Ƶ���ݶ�ȡ��־
		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHK_RF5))->GetCheck())
		{
			//�ٽ�����Դ����
			critical_section.Lock(); 
			btArrT[0] = 0XC6;
			btArrT[1] = 0X05;//05 15 25
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_0))->GetCheck())
			{
				btArrT[1] = 0X05 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_1))->GetCheck())
			{
				btArrT[1] = 0X15 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_2))->GetCheck())
			{
				btArrT[1] = 0X25 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_3))->GetCheck())
			{
				btArrT[1] = 0X35 ;//05 15 25 35
			}
			StdDataSend(btArrT);
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(2500);
		}
	

	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}


}

/*************************************************************
���һ���ַ��ǲ���ʮ�������ַ������Ƿ�����Ӧ��ֵ�����򷵻�0x10��
**************************************************************/
char CEDFADlg:: HexChar(char c)//���һ���ַ��ǲ���ʮ�������ַ������Ƿ�����Ӧ��ֵ�����򷵻�0x10��
{	
	if((c>='0')&&(c<='9'))
		return c-0X30;
	else if((c>='A')&&(c<='F'))
			return c-'A'+0X0A;
		 else if((c>='a')&&(c<='f'))
				  return c-'a'+0X0A;
			  else
				  return 0x00;
}
/*************************************************************

  //��һ���ַ�����Ϊʮ�����ƴ�ת��Ϊһ���ֽ����飬�ֽڼ���ÿո�ָ�������ת������ֽ����鳤�ȣ�ͬʱ�ֽ����鳤���Զ����á�
********************************************************/
int CEDFADlg:: Str2Hex(unsigned char *chArrt,/*CString str,*/CByteArray &data)
{
	unsigned char t,t1;
	int rlen=0/*,len*/;
/*	len=str.GetLength();*/
	//len = = strlen(chArrt);
	
	data.SetSize(32);
	for(int i=0;i<63;)
	{
		char l,h=chArrt[i];
		i++;

		l=chArrt[i];
		t=HexChar(h);
		t1=HexChar(l);
		if((t==16)||(t1==16))
			break;
		else 
			t=t*16+t1;
		i++;
		data[rlen]=(char)t;
		rlen++;
	}
	
	data.SetSize(rlen);
	return rlen;
}

void CEDFADlg::OnBtnChnW2() 
{
	// TODO: Add your control notification handler code here
	CString str;
	char chArrTxt[100] = {0};
	BYTE chArrBxt[100] = {0};
	if (!CheckPort())
 	{
 		return;
 	}
	if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}

	//�ٽ�����Դ����
	critical_section.Lock(); 
	GetDlgItem(IDC_EDIT_CH2)->GetWindowText(str);
	int len = str.GetLength();
	if (len>64)
	{
		MessageBox( "Data length limited 32 bytes!", "Data length ERROR", MB_OK );
		return;
	}
/********��ȡ���� ��������ݳ���Ϊ67 ��(32+0)*2+/0 ******/
	GetDlgItem( IDC_EDIT_CH2 )->GetWindowText( chArrTxt, 65 );
	//int iNameLen = strlen(chArrTxt);

		CByteArray DATA;

		BYTE btArrT[42] = { 0 } ;
		btArrT[0] = 0X68 ;
		btArrT[1] = 36 ;
		btArrT[2] = 36 ;
		btArrT[3] = 0X68 ;
		btArrT[4] = 0X16 ;
		btArrT[5] = 0X19 ;
		btArrT[6] = 0XC5 ;//�������� DLC��MPO������
		if (((CButton *)GetDlgItem(IDC_RIO_DLC22))->GetCheck())
		{
			btArrT[7] = 0X02 ;//02 12 22
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_0))->GetCheck())
			{
				btArrT[7] = 0X02 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_1))->GetCheck())
			{
				btArrT[7] = 0X12 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_2))->GetCheck())
			{
				btArrT[7] = 0X22 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_3))->GetCheck())
			{
				btArrT[7] = 0X32 ;//02 12 22 32
			}
		}
		if (((CButton*)GetDlgItem(IDC_RIO_MPO22)) ->GetCheck())
		{
			btArrT[7] = 0X07 ;//07 17 27
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_0))->GetCheck())
			{
				btArrT[7] = 0X07 ;//07 17 27
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_1))->GetCheck())
			{
				btArrT[7] = 0X17 ;//07 17 27
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_2))->GetCheck())
			{
				btArrT[7] = 0X27 ;//07 17 27
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_3))->GetCheck())
			{
				btArrT[7] = 0X37 ;//07 17 27 37
			}
		}
		for (int n=0 ;n<64;n++)
		{
			chArrBxt[n] = chArrTxt[n];
		}
		int datalenth = Str2Hex(chArrBxt,DATA);
		for( int i = 0 ; i < datalenth ; i++ )
		{
			/*hexData.SetAt( i+7, DATA[i] ) ;*/
			btArrT[i+8] = DATA[i];
		}
		btArrT[datalenth+8] = GetCheckSum(btArrT+4,datalenth+4);
		btArrT[41] = 0X16;
		/*���ڷ��͵���ʹ�� ����ע�͵���*/
		this->COMSendData( btArrT, 42 ) ;
		this->WriteTxtLog( btArrT, 42,1 );
		DATA.RemoveAll() ;
		//�ٽ�����Դ���
		critical_section.Unlock();
	
		//this->COMSendData( btArrT, 42 ) ;

//		ShowChannelData(btArrT);
		this->Time1(800);
		//MessageBox("Sending������","Sending",MB_OK);
/*****��Ƶ���ݷ��� ��EEPROM���ݷ���ͬ������********/
		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHK_RF2))->GetCheck())
		{
			//�ٽ�����Դ����
			critical_section.Lock();
			GetDlgItem(IDC_EDIT_RFID2) -> GetWindowText(str);
			len = str.GetLength();
			memset(chArrTxt,0,100);
			if (len>64)
			{
				MessageBox( "Data length limited 32 bytes!", "Data length ERROR", MB_OK );
				return;
			}
			GetDlgItem(IDC_EDIT_RFID2) ->GetWindowText(chArrTxt,65);

			
			btArrT[0] = 0X68 ;
			btArrT[1] = 36 ;
			btArrT[2] = 36 ;
			btArrT[3] = 0X68 ;
			btArrT[4] = 0X16 ;
			btArrT[5] = 0X19 ;
			btArrT[6] = 0XC7 ;//RF��������
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_0))->GetCheck())
			{
				btArrT[7] = 0X02 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_1))->GetCheck())
			{
				btArrT[7] = 0X12 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_2))->GetCheck())
			{
				btArrT[7] = 0X22 ;//02 12 22
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block2_3))->GetCheck())
			{
				btArrT[7] = 0X32 ;//02 12 22 32
			}
			for ( n=0 ;n<64;n++)
			{
				chArrBxt[n] = chArrTxt[n];
			}
			 datalenth = Str2Hex(chArrBxt,DATA);
			for( i = 0 ; i < datalenth ; i++ )
			{
				btArrT[i+8] = DATA[i];
			}
			btArrT[datalenth+8] = GetCheckSum(btArrT+4,datalenth+4);
			btArrT[41] = 0X16;			
			//ShowRFIDData(btArrT);
			/*���ڷ��͵���ʹ�� ����ע�͵���*/			
			this->COMSendData( btArrT, 42 ) ;
			this->WriteTxtLog( btArrT, 42,1 );
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(3000);		
		}
	
	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}


}

void CEDFADlg::OnBtnChnW3() 
{
	// TODO: Add your control notification handler code here
		CString str;
	char chArrTxt[100] = {0};
	BYTE chArrBxt[100] = {0};
	if (!CheckPort())
 	{
 		return;
 	}

	if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}

	//�ٽ�����Դ����
	critical_section.Lock();
	GetDlgItem(IDC_EDIT_CH3)->GetWindowText(str);
	int len = str.GetLength();
	if (len>64)
	{
		MessageBox( "Data length limited 32 bytes!", "Data length ERROR", MB_OK );
		return;
	}
/********��ȡ���� ��������ݳ���Ϊ67 ��(32+1)*2+/0 ******/
	GetDlgItem( IDC_EDIT_CH3 )->GetWindowText( chArrTxt, 65 );
	//int iNameLen = strlen(chArrTxt);
// 		if ((chArrTxt[1]<'1')||(chArrTxt[1]>'A'))
// 		{
// 			
// 				MessageBox("Channle Error!","Channel ERROR",MB_OK);
// 				return;
// 		}
// 		if (chArrTxt[0]>'2')
// 		{
// 			MessageBox("Block Error!","Block ERROR",MB_OK);
// 			return;
// 		}

		CByteArray DATA;
		int datalenth;
		BYTE btArrT[42] = { 0 } ;
		btArrT[0] = 0X68 ;
		btArrT[1] = 36 ;
		btArrT[2] = 36 ;
		btArrT[3] = 0X68 ;
		btArrT[4] = 0X16 ;
		btArrT[5] = 0X19 ;
		btArrT[6] = 0XC5 ;//�������� DLC��MPO������
		if (((CButton *)GetDlgItem(IDC_RIO_DLC3))->GetCheck())
		{
			/*btArrT[7] = 0X03 ;//03 13 23*/
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_0))->GetCheck())
			{
				btArrT[7] = 0X03 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_1))->GetCheck())
			{
				btArrT[7] = 0X13 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_2))->GetCheck())
			{
				btArrT[7] = 0X23 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_3))->GetCheck())
			{
				btArrT[7] = 0X33 ;//03 13 23 33
			}
		}
		if (((CButton*)GetDlgItem(IDC_RIO_MPO3)) ->GetCheck())
		{
			/*btArrT[1] = 0X08 ;//08 18 28*/
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_0))->GetCheck())
			{
				btArrT[7] = 0X08 ;//08 18 28
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_1))->GetCheck())
			{
				btArrT[7] = 0X18 ;//08 18 28
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_2))->GetCheck())
			{
				btArrT[7] = 0X28 ;//08 18 28
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_3))->GetCheck())
			{
				btArrT[7] = 0X38 ;//08 18 28 38
			}
		}
		/**����block3 �����ݲ���32�ֽڣ�����谴��112 -96 =16 **/
// 		if (((CButton *)GetDlgItem(IDC_RIO_Block3_2))->GetCheck())
// 		{
// 			if (len>32)
// 			{
// 				MessageBox( "Block3 Data length limited 32 bytes!", "Data length ERROR", MB_OK );
// 				return;
// 			}
// 		}
	
			for (int n=0 ;n<64;n++)
			{
				chArrBxt[n] = chArrTxt[n];
			}
			datalenth = Str2Hex(chArrBxt,DATA);
			for( int i = 0 ; i < datalenth ; i++ )
			{
				/*hexData.SetAt( i+8, DATA[i] ) ;*/
				btArrT[i+8] = DATA[i];
			}
			btArrT[datalenth+8] = GetCheckSum(btArrT+4,datalenth+4);
			btArrT[41] = 0X16;
			/*���ڷ��͵���ʹ�� ����ע�͵���*/
			this->COMSendData( btArrT, 42 ) ;
			this->WriteTxtLog( btArrT, 42,1 );
			DATA.RemoveAll() ;
			//�ٽ�����Դ���
			critical_section.Unlock();	
			//this->COMSendData( btArrT, 42 ) ;

//			ShowChannelData(btArrT);
		
		
		this->Time1(800);
		//MessageBox("Sending������","Sending",MB_OK);
/*****��Ƶ���ݷ��� ��EEPROM���ݷ���ͬ������********/
		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHK_RF3))->GetCheck())
		{
			//�ٽ�����Դ����
			critical_section.Lock();
			GetDlgItem(IDC_EDIT_RFID3) -> GetWindowText(str);
			len = str.GetLength();
			memset(chArrTxt,0,100);
			if (len>64)
			{
				MessageBox( "Data length limited 32 bytes!", "Data length ERROR", MB_OK );
				return;
			}
			GetDlgItem(IDC_EDIT_RFID3) ->GetWindowText(chArrTxt,65);
// 			if ((chArrTxt[1]<'1')||(chArrTxt[1]>'5'))
// 			{
// 				
// 					MessageBox("RF Channle Error!","Channel ERROR",MB_OK);
// 					return;
// 			}
// 			if (chArrTxt[0]>'2')
// 			{
// 				MessageBox("Block Error!","Block ERROR",MB_OK);
// 				return;
// 			}
			
			btArrT[0] = 0X68 ;
			btArrT[1] = 36 ;
			btArrT[2] = 36 ;
			btArrT[3] = 0X68 ;
			btArrT[4] = 0X16 ;
			btArrT[5] = 0X19 ;
			btArrT[6] = 0XC7 ;//RF��������
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_0))->GetCheck())
			{
				btArrT[7] = 0X03 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_1))->GetCheck())
			{
				btArrT[7] = 0X13 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_2))->GetCheck())
			{
				btArrT[7] = 0X23 ;//03 13 23
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block3_3))->GetCheck())
			{
				btArrT[7] = 0X33 ;//03 13 23 33
			}
			for ( n=0 ;n<64;n++)
			{
				chArrBxt[n] = chArrTxt[n];
			}
			 datalenth = Str2Hex(chArrBxt,DATA);
			for( i = 0 ; i < datalenth ; i++ )
			{
				btArrT[i+8] = DATA[i];
			}
			btArrT[datalenth+8] = GetCheckSum(btArrT+4,datalenth+4);
			btArrT[41] = 0X16;			
			//ShowRFIDData(btArrT);
			/*���ڷ��͵���ʹ�� ����ע�͵���*/			
			this->COMSendData( btArrT, 42 ) ;
			this->WriteTxtLog( btArrT, 42,1 );
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(3000);		
		}

	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}


	
}

void CEDFADlg::OnBtnChnW4() 
{
	// TODO: Add your control notification handler code here
	CString str;
	char chArrTxt[100] = {0};
	BYTE chArrBxt[100] = {0};
	if (!CheckPort())
 	{
 		return;
 	}
	if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}

	//�ٽ�����Դ����
	critical_section.Lock();
	GetDlgItem(IDC_EDIT_CH4)->GetWindowText(str);
	int len = str.GetLength();
	if (len>64)
	{
		MessageBox( "Data length limited 32 bytes!", "Data length ERROR", MB_OK );
		return;
	}
/********��ȡ���� ��������ݳ���Ϊ67 ��(32)*2+/0 ******/
	GetDlgItem( IDC_EDIT_CH4 )->GetWindowText( chArrTxt, 65 );
	//int iNameLen = strlen(chArrTxt);
// 		if ((chArrTxt[1]<'1')||(chArrTxt[1]>'A'))
// 		{
// 			
// 				MessageBox("Channle Error!","Channel ERROR",MB_OK);
// 				return;
// 		}
// 		if (chArrTxt[0]>'2')
// 		{
// 			MessageBox("Block Error!","Block ERROR",MB_OK);
// 			return;
// 		}	


		CByteArray DATA;

		BYTE btArrT[42] = { 0 } ;
		btArrT[0] = 0X68 ;
		btArrT[1] = 36 ;
		btArrT[2] = 36 ;
		btArrT[3] = 0X68 ;
		btArrT[4] = 0X16 ;
		btArrT[5] = 0X19 ;
		btArrT[6] = 0XC5 ;//�������� DLC��MPO������
		if (((CButton *)GetDlgItem(IDC_RIO_DLC4))->GetCheck())
		{
			/*btArrT[7] = 0X04 ;//04 14 24*/
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_0))->GetCheck())
			{
				btArrT[7] = 0X04 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_1))->GetCheck())
			{
				btArrT[7] = 0X14 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_2))->GetCheck())
			{
				btArrT[7] = 0X24 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_3))->GetCheck())
			{
				btArrT[7] = 0X34 ;//04 14 24 34
			}
		}
		if (((CButton*)GetDlgItem(IDC_RIO_MPO4)) ->GetCheck())
		{
			/*btArrT[1] = 0X09 ;//09 19 29*/
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_0))->GetCheck())
			{
				btArrT[7] = 0X09 ;//09 19 29
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_1))->GetCheck())
			{
				btArrT[7] = 0X19 ;//09 19 29
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_2))->GetCheck())
			{
				btArrT[7] = 0X29 ;//09 19 29
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_3))->GetCheck())
			{
				btArrT[7] = 0X39 ;//09 19 29 39
			}

		}
		for (int n=0 ;n<64;n++)
		{
			chArrBxt[n] = chArrTxt[n];
		}
		int datalenth = Str2Hex(chArrBxt,DATA);
		for( int i = 0 ; i < datalenth ; i++ )
		{
			/*hexData.SetAt( i+8, DATA[i] ) ;*/
			btArrT[i+8] = DATA[i];
		}
		btArrT[datalenth+8] = GetCheckSum(btArrT+4,datalenth+4);
		btArrT[41] = 0X16;
		/*���ڷ��͵���ʹ�� ����ע�͵���*/
		this->COMSendData( btArrT, 42 ) ;
		this->WriteTxtLog( btArrT, 42,1 );
		DATA.RemoveAll( ) ;
		//�ٽ�����Դ���
		critical_section.Unlock();
		//this->COMSendData( btArrT, 42 ) ;

//		ShowChannelData(btArrT);
		this->Time1(800);
		//MessageBox("Sending������","Sending",MB_OK);
/*****��Ƶ���ݷ��� ��EEPROM���ݷ���ͬ������********/
		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHK_RF4))->GetCheck())
		{
			//�ٽ�����Դ����
			critical_section.Lock();
			GetDlgItem(IDC_EDIT_RFID4) -> GetWindowText(str);
			len = str.GetLength();
			memset(chArrTxt,0,100);
			if (len>64)
			{
				MessageBox( "Data length limited 32 bytes!", "Data length ERROR", MB_OK );
				return;
			}
			GetDlgItem(IDC_EDIT_RFID4) ->GetWindowText(chArrTxt,65);
// 			if ((chArrTxt[1]<'1')||(chArrTxt[1]>'5'))
// 			{
// 				
// 					MessageBox("RF Channle Error!","Channel ERROR",MB_OK);
// 					return;
// 			}
// 			if (chArrTxt[0]>'2')
// 			{
// 				MessageBox("Block Error!","Block ERROR",MB_OK);
// 				return;
// 			}
			
			btArrT[0] = 0X68 ;
			btArrT[1] = 36 ;
			btArrT[2] = 36 ;
			btArrT[3] = 0X68 ;
			btArrT[4] = 0X16 ;
			btArrT[5] = 0X19 ;
			btArrT[6] = 0XC7 ;//RF��������
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_0))->GetCheck())
			{
				btArrT[7] = 0X04 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_1))->GetCheck())
			{
				btArrT[7] = 0X14 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_2))->GetCheck())
			{
				btArrT[7] = 0X24 ;//04 14 24
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block4_3))->GetCheck())
			{
				btArrT[7] = 0X34 ;//04 14 24 34
			}
			for ( n=0 ;n<64;n++)
			{
				chArrBxt[n] = chArrTxt[n];
			}
			 datalenth = Str2Hex(chArrBxt,DATA);
			for( i = 0 ; i < datalenth ; i++ )
			{
				btArrT[i+8] = DATA[i];
			}
			btArrT[datalenth+8] = GetCheckSum(btArrT+4,datalenth+4);
			btArrT[41] = 0X16;			
			//ShowRFIDData(btArrT);
			/*���ڷ��͵���ʹ�� ����ע�͵���*/			
			this->COMSendData( btArrT, 42 ) ;
			this->WriteTxtLog( btArrT, 42,1 );
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(3000);		
		}
	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}	

}

void CEDFADlg::OnBtnChnW5() 
{
	// TODO: Add your control notification handler code here
	CString str;
	char chArrTxt[100] = {0};
	BYTE chArrBxt[100] = {0};
	if (!CheckPort())
 	{
 		return;
 	}
	if (this->time_flag == Timing)
	{
		KillTimer(TIMER_SHOW_MONITOR);
		this->time_flag = Changing;
	}
	//�ٽ�����Դ����
	critical_section.Lock();
	GetDlgItem(IDC_EDIT_CH5)->GetWindowText(str);
	int len = str.GetLength();
	if (len>64)
	{
		MessageBox( "Data length limited 32 bytes!", "Data length ERROR", MB_OK );
		return;
	}
/********��ȡ���� ��������ݳ���Ϊ65 ��(32)*2+/0 ******/
	GetDlgItem( IDC_EDIT_CH5 )->GetWindowText( chArrTxt, 65 );
	//int iNameLen = strlen(chArrTxt);
// 		if ((chArrTxt[1]<'1')||(chArrTxt[1]>'A'))
// 		{
// 			
// 				MessageBox("Channle Error!","Channel ERROR",MB_OK);
// 				return;
// 		}
// 		if (chArrTxt[0]>'2')
// 		{
// 			MessageBox("Block Error!","Block ERROR",MB_OK);
// 			return;
// 		}

		CByteArray DATA;

		BYTE btArrT[42] = { 0 } ;
		btArrT[0] = 0X68 ;
		btArrT[1] = 36 ;
		btArrT[2] = 36 ;
		btArrT[3] = 0X68 ;
		btArrT[4] = 0X16 ;
		btArrT[5] = 0X19 ;
		btArrT[6] = 0XC5 ;//�������� DLC��MPO������
		if (((CButton *)GetDlgItem(IDC_RIO_DLC5))->GetCheck())
		{
		/*	btArrT[7] = 0X05 ;//05 15 25*/
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_0))->GetCheck())
			{
				btArrT[7] = 0X05 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_1))->GetCheck())
			{
				btArrT[7] = 0X15 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_2))->GetCheck())
			{
				btArrT[7] = 0X25 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_3))->GetCheck())
			{
				btArrT[7] = 0X35 ;//05 15 25 35
			}

		}
		if (((CButton*)GetDlgItem(IDC_RIO_MPO5)) ->GetCheck())
		{
			/*btArrT[7] = 0X0A ;//0A 1A 2A*/
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_0))->GetCheck())
			{
				btArrT[7] = 0X0A ;//0A 1A 2A
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_1))->GetCheck())
			{
				btArrT[7] = 0X1A ;//0A 1A 2A
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_2))->GetCheck())
			{
				btArrT[7] = 0X2A ;//0A 1A 2A
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_3))->GetCheck())
			{
				btArrT[7] = 0X3A ;//0A 1A 2A 3A
			}
		}
		for (int n=0 ;n<64;n++)
		{
			chArrBxt[n] = chArrTxt[n];
		}
		int datalenth = Str2Hex(chArrBxt,DATA);
		for( int i = 0 ; i < datalenth ; i++ )
		{
			/*hexData.SetAt( i+7, DATA[i] ) ;*/
			btArrT[i+8] = DATA[i];
		}
		btArrT[datalenth+8] = GetCheckSum(btArrT+4,datalenth+4);
		btArrT[41] = 0X16;
		/*���ڷ��͵���ʹ�� ����ע�͵���*/
		this->COMSendData( btArrT, 42 ) ;
		this->WriteTxtLog( btArrT, 42 ,1);
		DATA.RemoveAll( ) ;
		//�ٽ�����Դ���
		critical_section.Unlock();
	
		//this->COMSendData( btArrT, 42 ) ;

//		ShowChannelData(btArrT);
		this->Time1(800);
		//MessageBox("Sending������","Sending",MB_OK);
/*****��Ƶ���ݷ��� ��EEPROM���ݷ���ͬ������********/
		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHK_RF5))->GetCheck())
		{
			//�ٽ�����Դ����
			critical_section.Lock();
			GetDlgItem(IDC_EDIT_RFID5) -> GetWindowText(str);
			len = str.GetLength();
			memset(chArrTxt,0,100);
			if (len>64)
			{
				MessageBox( "Data length limited 32 bytes!", "Data length ERROR", MB_OK );
				return;
			}
			GetDlgItem(IDC_EDIT_RFID5) ->GetWindowText(chArrTxt,65);
// 			if ((chArrTxt[1]<'1')||(chArrTxt[1]>'5'))
// 			{
// 				
// 					MessageBox("RF Channle Error!","Channel ERROR",MB_OK);
// 					return;
// 			}
// 			if (chArrTxt[0]>'2')
// 			{
// 				MessageBox("Block Error!","Block ERROR",MB_OK);
// 				return;
// 			}
			
			btArrT[0] = 0X68 ;
			btArrT[1] = 36 ;
			btArrT[2] = 36 ;
			btArrT[3] = 0X68 ;
			btArrT[4] = 0X16 ;
			btArrT[5] = 0X19 ;
			btArrT[6] = 0XC7 ;//RF��������
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_0))->GetCheck())
			{
				btArrT[7] = 0X05 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_1))->GetCheck())
			{
				btArrT[7] = 0X15 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_2))->GetCheck())
			{
				btArrT[7] = 0X25 ;//05 15 25
			}
			if (((CButton *)GetDlgItem(IDC_RIO_Block5_3))->GetCheck())
			{
				btArrT[7] = 0X35 ;//05 15 25 35
			}
			for ( n=0 ;n<64;n++)
			{
				chArrBxt[n] = chArrTxt[n];
			}
			 datalenth = Str2Hex(chArrBxt,DATA);
			for( i = 0 ; i < datalenth ; i++ )
			{
				btArrT[i+8] = DATA[i];
			}
			btArrT[datalenth+8] = GetCheckSum(btArrT+4,datalenth+4);
			btArrT[41] = 0X16;			
			//ShowRFIDData(btArrT);
			/*���ڷ��͵���ʹ�� ����ע�͵���*/			
			this->COMSendData( btArrT, 42 ) ;
			this->WriteTxtLog( btArrT, 42,1 );
			//�ٽ�����Դ���
			critical_section.Unlock();
			this->Time1(3000);		
		}
	if (this ->time_flag == Changing)
	{
		SetTimer( TIMER_SHOW_MONITOR, 2000, NULL ); // ������ʱ����ʾMONITOR���
	}	
}
/************************************************************************/
/*
�������ܣ� ����ʵ����ʱ useconds���룬��������ʱͬʱ�����ó�CPU����������Ϣ
                                                                     */
/************************************************************************/

void CEDFADlg::Time1(int useconds)
{
	DWORD dwStart = GetTickCount();
	DWORD dwEnd = dwStart;
	do 
	{
		MSG msg;
		GetMessage(&msg,NULL,0,0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		dwEnd = GetTickCount()-dwStart;
	} while (dwEnd<useconds);
}



void CEDFADlg::WriteTxtLog(unsigned char *pucData, int iLength,int flag)
{
	unsigned char chArrTemp[100] = { 0 };
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	CString strtime,str;
	if (flag == 1)
	{
		strtime.Format("%04d %02d %02d %02d:%02d:%02d Send:",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
	}
	if ( flag== -1 )
	{
		strtime.Format("%04d %02d %02d %02d:%02d:%02d Recs:",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
	}
	
	for (int i=0;i < iLength;i++)
	{
		chArrTemp[i] = pucData[i];
		str.Format("%02X",chArrTemp[i]);
		strtime+=str;
	}
	strtime+="\r\n";
	FILE *pFile = fopen("log.txt","a");
	fseek(pFile,0,SEEK_END);
	fwrite(strtime,1,strlen(strtime),pFile);
	fflush(pFile);
	fclose(pFile);

}
