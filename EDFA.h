// EDFA.h : main header file for the EDFA application
//

#if !defined(AFX_EDFA_H__11B584B0_84E8_4DAC_8EBA_CDE6D989990F__INCLUDED_)
#define AFX_EDFA_H__11B584B0_84E8_4DAC_8EBA_CDE6D989990F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEDFAApp:
// See EDFA.cpp for the implementation of this class
//

class CEDFAApp : public CWinApp
{
public:
	CEDFAApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEDFAApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEDFAApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDFA_H__11B584B0_84E8_4DAC_8EBA_CDE6D989990F__INCLUDED_)
