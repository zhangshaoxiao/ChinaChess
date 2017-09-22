// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "chess.h"
#include "ClientSocket.h"
#include "ChessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
{
	m_aSessionIn=NULL;
	m_aSessionOut=NULL;
	m_sfSocketFile=NULL;
	m_binit=false;
	m_bclose=false;
}

CClientSocket::~CClientSocket()
{
	if(m_aSessionIn)
		delete m_aSessionIn;
	if(m_aSessionOut)
		delete m_aSessionOut;
	if(m_sfSocketFile)
		delete m_sfSocketFile;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions
void CClientSocket::Init(CChessDlg *pdlg)
{
	m_sfSocketFile=new CSocketFile(this);
	m_aSessionIn=new CArchive(m_sfSocketFile,CArchive::load);
	m_aSessionOut=new CArchive(m_sfSocketFile,CArchive::store);
	m_bclose=false;
	this->m_pdlg=pdlg;

}
void CClientSocket::OnReceive(int nErrorCode)
{   //接受对方发给的数据
	CSocket::OnReceive(nErrorCode);
	do
	{
		CMessg sendmsg;
		CMessg msg;
		msg.Serialize(*m_aSessionIn);
		int temp=msg.m_messgtype;
		switch(temp)
		{
		case 1:
			//正常下棋
			if(m_pdlg->move.MayMove(m_pdlg->plate.platepos,msg.xfrom,msg.yfrom,msg.xto,msg.yto,m_pdlg->m_bIschangestone))
			{
				m_pdlg->NetMoveStone(msg);
			}
			break;
		case 2:
			//向对方请求悔棋	
			if(AfxMessageBox("对方请求悔棋，同意吗？ ",MB_YESNO)==IDYES)
			{
				sendmsg.m_messgtype=3;
				m_pdlg->Remove();
			}
			else
			{
				sendmsg.m_messgtype=4;
			}
				SendMessage(&sendmsg);
			break;
		case 3:
			//同意悔棋请求
			m_pdlg->Remove();
			break;
		case 4:
			//不同意悔棋请求
			AfxMessageBox("对方不同意你悔棋,老兄你还是小心点下吧！ ");
			break;
		case 5:
			//响应对方的认输
			AfxMessageBox("对方认输了！ ");
			m_pdlg->SetNewGame();
			break;
		case 6:
			//对方请求新棋局
			AfxMessageBox("对方来新棋局");
			m_pdlg->SetNewGame();
			break;
		case 7:
			//接受服务器设置下棋模式
			AfxMessageBox("对方让你先走 !  ");
			m_pdlg->SetRunMode(msg.xfrom);
			m_pdlg->CurrentPrompt();
			break;	
		default:
			break;
		}
	}
	while(!m_aSessionIn->IsBufferEmpty());
}


BOOL CClientSocket::SendMessage(CMessg *msg)
{//想对方发送数据
	if(m_aSessionOut!=NULL)
	{
		msg->Serialize(*m_aSessionOut);//将数据串行化
		m_aSessionOut->Flush();        //直接发送数据
		return TRUE;
	}
	else
	{
		m_bclose=true;
		CloseSocket();
		return FALSE;
	}

}
void CClientSocket::CloseSocket()
{
	if(m_aSessionIn)
	{
		delete m_aSessionIn;
		m_aSessionIn=NULL;
	}
	if(m_aSessionOut)
	{
		delete m_aSessionOut;
		m_aSessionOut=NULL;
	}
	if(m_sfSocketFile)
	{
		delete m_sfSocketFile;
		m_sfSocketFile=NULL;
	}
	Close();
	m_binit=false;
	m_bclose=true;
}
void CClientSocket::OnClose(int nErrorCode)
{
	m_bclose=true;
	CloseSocket();
	CSocket::OnClose(nErrorCode);
}
int CClientSocket::GetLocalHostName(CString &sHostName)
{
	char szHostName[256];
	int ret;
	ret=gethostname(szHostName,sizeof(szHostName));
	if(ret!=0)
	{
		sHostName=_T("不能取得主机名！");
		return GetLastError();
	}
	sHostName=szHostName;
	return 0;
}
int CClientSocket::GetIpAddress(const CString &sHostName,CString &sIpAddress)
{//取得本机的IP地址（字符型的）
	struct hostent FAR *lpHostEnt=gethostbyname(sHostName);
	if(lpHostEnt==NULL)
	{
		sIpAddress=_T("");
		return GetLastError();
	}

	LPSTR lpAddr=lpHostEnt->h_addr_list[0];
	if(lpAddr)
	{
		struct in_addr inAddr;
		memmove(&inAddr,lpAddr,4);
		sIpAddress=inet_ntoa(inAddr);
		if(sIpAddress.IsEmpty())
			sIpAddress=_T("没有获得IP地址！");
	}
	return 0;
}
int CClientSocket::GetIpAddress(const CString &sHostName,BYTE &f0,BYTE &f1,BYTE &f2,BYTE &f3)
{//取得本机的IP地址（BYTE型的）

	struct hostent FAR *lpHostEnt=gethostbyname(sHostName);
	if(lpHostEnt==NULL)
	{
		f0=f1=f2=f3=0;
		return GetLastError();
	}
	LPSTR lpAddr=lpHostEnt->h_addr_list[0];
	if(lpAddr)
	{
		struct in_addr inAddr;
		memmove(&inAddr,lpAddr,4);
		f0=inAddr.S_un.S_un_b.s_b1;
		f1=inAddr.S_un.S_un_b.s_b2;
		f2=inAddr.S_un.S_un_b.s_b3;
		f3=inAddr.S_un.S_un_b.s_b4;
	}
	return 0;
}
