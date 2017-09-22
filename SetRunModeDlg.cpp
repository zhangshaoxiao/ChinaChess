// SetRunModeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chess.h"
#include "SetRunModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetRunModeDlg dialog


CSetRunModeDlg::CSetRunModeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetRunModeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetRunModeDlg)
	m_whofirst = 0;
	//}}AFX_DATA_INIT
}


void CSetRunModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetRunModeDlg)
	DDX_Radio(pDX, IDC_WHOFIRSTBLACK, m_whofirst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetRunModeDlg, CDialog)
	//{{AFX_MSG_MAP(CSetRunModeDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetRunModeDlg message handlers
