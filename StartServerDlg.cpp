// StartServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chess.h"
#include "StartServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartServerDlg dialog


CStartServerDlg::CStartServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStartServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartServerDlg)
	m_nport =6880;
	//}}AFX_DATA_INIT
}


void CStartServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartServerDlg)
	DDX_Text(pDX, IDC_SERVERPORT, m_nport);
	DDV_MinMaxInt(pDX, m_nport, 1024, 100000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartServerDlg, CDialog)
	//{{AFX_MSG_MAP(CStartServerDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartServerDlg message handlers
