#if !defined(AFX_SETRUNMODEDLG_H__A701BC58_3DFD_4F84_9BBB_B0F7CCEC944A__INCLUDED_)
#define AFX_SETRUNMODEDLG_H__A701BC58_3DFD_4F84_9BBB_B0F7CCEC944A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetRunModeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetRunModeDlg dialog

class CSetRunModeDlg : public CDialog
{
// Construction
public:
	CSetRunModeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetRunModeDlg)
	enum { IDD = IDD_SETRUNMODE };
	int		m_whofirst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetRunModeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetRunModeDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETRUNMODEDLG_H__A701BC58_3DFD_4F84_9BBB_B0F7CCEC944A__INCLUDED_)
