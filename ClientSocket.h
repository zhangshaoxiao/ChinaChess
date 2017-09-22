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
	CArchive *m_aSessionIn;	    //�������ݵĴ��л�
	CArchive *m_aSessionOut;    //������ݵĴ��л�
	CSocketFile *m_sfSocketFile;//ר�����������ļ�
	CChessDlg* m_pdlg;          //���Ի���ָ�룬���ø�ָ��������Ի���
	bool m_binit;
	bool m_bclose;


// Operations
public:
	CClientSocket();
	virtual ~CClientSocket();
	void Init(CChessDlg *pdlg);   //socket�ʹ��л���صĳ�ʼ��
	BOOL SendMessage(CMessg *msg);//������Ϣ�õ�
	void CloseSocket();           //�Ͽ�����
public:
	//�����õ���������������IP��ַ
	static int GetLocalHostName(CString &sHostName);
	static int GetIpAddress(const CString &sHostName,CString &sIpAddress);
	static int GetIpAddress(const CString &sHostName,BYTE &f0,BYTE &f1,BYTE &f2,BYTE &f3);
	static CString ErrorReason(int tag);
public:
	virtual void OnReceive(int nErrorCode);//���ݽ��ܴ�����Ϣ�Ĵ�����
	virtual void OnClose(int nErrorCode);  //socket�رյ���Ϣ������

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
