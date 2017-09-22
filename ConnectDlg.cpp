// ConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chess.h"
#include "ConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog


CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectDlg)
	m_nport = 6880;
	m_ipaddressedit1 = 127;
	m_ipaddressedit2 = 0;
	m_ipaddressedit3 = 0;
	m_ipaddressedit4 = 1;
	//}}AFX_DATA_INIT
}


void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectDlg)
	DDX_Text(pDX, IDC_PORTEDIT, m_nport);
	DDV_MinMaxInt(pDX, m_nport, 1024, 100000);
	DDX_Text(pDX, IDC_IPADDRESSEDIT1, m_ipaddressedit1);
	DDV_MinMaxInt(pDX, m_ipaddressedit1, 0, 255);
	DDX_Text(pDX, IDC_IPADDRESSEDIT2, m_ipaddressedit2);
	DDV_MinMaxInt(pDX, m_ipaddressedit2, 0, 255);
	DDX_Text(pDX, IDC_IPADDRESSEDIT3, m_ipaddressedit3);
	DDV_MinMaxInt(pDX, m_ipaddressedit3, 0, 255);
	DDX_Text(pDX, IDC_IPADDRESSEDIT4, m_ipaddressedit4);
	DDV_MinMaxInt(pDX, m_ipaddressedit4, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg message handlers
