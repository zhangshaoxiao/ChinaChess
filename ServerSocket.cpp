// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "chess.h"
#include "ServerSocket.h"
#include "ChessDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions
BOOL CServerSocket::Init(UINT port,CChessDlg *pdlg)
{
	m_uport=port;
	m_pdlg=pdlg;
	if(Create(m_uport)==FALSE)
	{
		AfxMessageBox("服务器套接字创建失败！");
		return FALSE;
	}
	if(this->Listen(1)==FALSE)//只能一个客户端连接
	{
		AfxMessageBox("服务器监听失败！");
			return FALSE;
	}

	return TRUE;
}
void CServerSocket::OnAccept(int nErrorCode)
{
	CSocket::OnAccept(nErrorCode);
	m_pdlg->ProcessPendingAccept();

}
