#include "afxsock.h"

#if !defined(AFX_SERVERSOCKET_H__BEA3356E_B013_4E23_9D41_3D8EF9B9AB8F__INCLUDED_)
#define AFX_SERVERSOCKET_H__BEA3356E_B013_4E23_9D41_3D8EF9B9AB8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServerSocket command target
class CChessDlg;
class CServerSocket : public CSocket
{
// Attributes
public:
	CChessDlg *m_pdlg;
	UINT m_uport;
	BOOL Init(UINT port,CChessDlg *pdlg);
// Operations
public:
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCKET_H__BEA3356E_B013_4E23_9D41_3D8EF9B9AB8F__INCLUDED_)
