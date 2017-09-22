#if !defined(AFX_CONNECTDLG_H__98640528_8CC4_43C2_9ED6_C45BB0C629AD__INCLUDED_)
#define AFX_CONNECTDLG_H__98640528_8CC4_43C2_9ED6_C45BB0C629AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog

class CConnectDlg : public CDialog
{
// Construction
public:
	CConnectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnectDlg)
	enum { IDD = IDD_CONNECTSEVERDLG };
	int		m_nport;
	int		m_ipaddressedit1;
	int		m_ipaddressedit2;
	int		m_ipaddressedit3;
	int		m_ipaddressedit4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConnectDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTDLG_H__98640528_8CC4_43C2_9ED6_C45BB0C629AD__INCLUDED_)
