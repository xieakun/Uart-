// EDFADlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_EDFADLG_H__BC3E7153_4FDA_4BAC_B67E_B1A7185CE021__INCLUDED_)
#define AFX_EDFADLG_H__BC3E7153_4FDA_4BAC_B67E_B1A7185CE021__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
		
	//波特率初始化
/////////////////////////////////////////////////////////////////////////////
// CEDFADlg dialog



class CEDFADlg : public CDialog
{
// Construction
public:
	CEDFADlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEDFADlg)
	enum { IDD = IDD_EDFA_DIALOG };
	CButton	m_Auto;

	CStatic	m_MPOLED5;
	CStatic	m_MPOLED4;
	CStatic	m_MPOLED3;
	CStatic	m_MPOLED2;
	CStatic	m_MPOLED1;
	CStatic	m_DLCLED5;
	CStatic	m_DLCLED4;
	CStatic	m_DLCLED3;
	CStatic	m_DLCLED2;
	CStatic	m_DLCLED1;
	CStatic	m_ComLed;
	CComboBox	m_ctrlCOMNO;
	CComboBox	m_ctrlBandRate;
	CMSComm	m_ctrlComm;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEDFADlg)

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
		
	unsigned char GetCheckSum( unsigned char *pucData, int iDataLen ) ;

	
	void ShowBITE( unsigned char *pucBITEData ) ;
	void ShowSync(unsigned char *pucSyncData);
	void WriteLog(CString str);
	void ShowBandRate(unsigned char *pucBandRate);
	void ShowChannelData(unsigned char *pucChanData);
	void ShowRFIDData(unsigned char *pucChanData);
	void ShowError(unsigned char *pucChanData);
	void ClearEditBox();
	BOOL CheckPort();
	void ReSize();
	void StdDataSend(unsigned char *strdata);
	char HexChar(char c);
	int Str2Hex(unsigned char *chArrt,/*CString str,*/CByteArray &data);
	void Time1(int useconds);//延时1s 且不影响程序运行

	enum OPType
	{
		E_GET_BITE = 1,
		E_SET_APC,
		E_SET_MODULE_TEMP,
		E_INPUT_LOW_TH,
		E_INPUT_HIGH_T,
		E_OUTPUT_LOW_TH,
		E_OUTPUT_HIGH_TH,
	} ;
	
	unsigned char m_ucOpType ;
	
	enum COMLAN
	{
		COM = -1,
		NOTHING = 0,
		LAN = 1
	} ;
	enum Flag
	{
		Timing = 1,
		Changing = 0,
		Stopping = -1
	};
	int time_flag;



//	void DisplayLCFG( unsigned char *pucBITEData ) ;
	
	void COMSendData( unsigned char *pucData, int iLen ) ;
	void WriteTxtLog(unsigned char *pucData, int iLength,int flag);
	int PassFail( unsigned char *pucData ) ;

// Implementation
protected:
	HICON m_hIcon;
	POINT old;	//缩放窗口，记录窗口属性（宽和高）
	
	// Generated message map functions
	//{{AFX_MSG(CEDFADlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnButtonReadAll();
	afx_msg void OnButtonOpenCOM();
	afx_msg void OnButtonCloseCOM();
	afx_msg void OnButtonOnekeyreceive();
	afx_msg void OnButtonOnekeywrite();
	afx_msg void OnCheckAuto();
	afx_msg void OnTimer(UINT nIDEvent);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnBtnChnW1();
	afx_msg void OnBtnChnR1();
	afx_msg void OnBtnChnR2();
	afx_msg void OnBtnChnR3();
	afx_msg void OnBtnChnR4();
	afx_msg void OnBtnChnR5();
	afx_msg void OnBtnChnW2();
	afx_msg void OnBtnChnW3();
	afx_msg void OnBtnChnW4();
	afx_msg void OnBtnChnW5();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDFADLG_H__BC3E7153_4FDA_4BAC_B67E_B1A7185CE021__INCLUDED_)
