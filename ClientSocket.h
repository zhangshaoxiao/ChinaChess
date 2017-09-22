#include "afxsock.h"
#include "Messg.h"

#if !defined(AFX_CLIENTSOCKET_H__8C41D2AC_D453_43D7_8B24_E4D9DCBA2307__INCLUDED_)
#define AFX_CLIENTSOCKET_H__8C41D2AC_D453_43D7_8B24_E4D9DCBA2307__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target
class CChessDlg;
class CClientSocket : public CSocket
{
// Attributes
public:
	CArchive *m_aSessionIn;	    //输入数据的串行化
	CArchive *m_aSessionOut;    //输出数据的串行化
	CSocketFile *m_sfSocketFile;//专门网络服务的文件
	CChessDlg* m_pdlg;          //主对话框指针，利用该指针控制主对话框
	bool m_binit;
	bool m_bclose;


// Operations
public:
	CClientSocket();
	virtual ~CClientSocket();
	void Init(CChessDlg *pdlg);   //socket和串行化相关的初始化
	BOOL SendMessage(CMessg *msg);//发送消息用的
	void CloseSocket();           //断开连接
public:
	//用来得到主机名和主机的IP地址
	static int GetLocalHostName(CString &sHostName);
	static int GetIpAddress(const CString &sHostName,CString &sIpAddress);
	static int GetIpAddress(const CString &sHostName,BYTE &f0,BYTE &f1,BYTE &f2,BYTE &f3);
	static CString ErrorReason(int tag);
public:
	virtual void OnReceive(int nErrorCode);//数据接受处理消息的处理函数
	virtual void OnClose(int nErrorCode);  //socket关闭的消息处理函数

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__8C41D2AC_D453_43D7_8B24_E4D9DCBA2307__INCLUDED_)
