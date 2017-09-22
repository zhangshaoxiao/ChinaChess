#if !defined(AFX_STARTSERVERDLG_H__7E99AC3A_EA29_4B8D_AC0B_C8BF511498A9__INCLUDED_)
#define AFX_STARTSERVERDLG_H__7E99AC3A_EA29_4B8D_AC0B_C8BF511498A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartServerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartServerDlg dialog

class CStartServerDlg : public CDialog
{
// Construction
public:
	CStartServerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStartServerDlg)
	enum { IDD = IDD_STARTSERVERDLG };
	int		m_nport;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStartServerDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTSERVERDLG_H__7E99AC3A_EA29_4B8D_AC0B_C8BF511498A9__INCLUDED_)
