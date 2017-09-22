// ChessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chess.h"
#include "ChessDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessDlg dialog

CChessDlg::CChessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pmap=new CDC;
	m_pstone=new CDC;
	m_pplate=new CDC;
	m_pplate1=new CDC;

}
CChessDlg::~CChessDlg()
{
	if(m_pmap)delete m_pmap;
	if(m_pstone)delete m_pstone;
	if(m_pplate)delete m_pplate;
	if(m_pplate1)delete m_pplate1;
}
void CChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChessDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChessDlg, CDialog)
	//{{AFX_MSG_MAP(CChessDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_SET_BCOLOSE_0, OnSetBcolose0)
	ON_COMMAND(ID_SET_BCOLOSE_1, OnSetBcolose1)
	ON_COMMAND(ID_SET_BCOLOSE_2, OnSetBcolose2)
	ON_COMMAND(ID_ACTION_REMOVE, OnActionRemove)
	ON_COMMAND(ID_SET_CHANGESTONE, OnSetChangestone)
	ON_COMMAND(ID_ACTINO_NEW, OnActinoNew)
	ON_COMMAND(ID_START_CREATESERVER, OnStartCreateserver)
	ON_COMMAND(ID_START_EXIT, OnStartExit)
	ON_COMMAND(ID_START_CONNECTSERVER, OnStartConnectserver)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_COMMAND(ID_START_CLOSESOCKET, OnStartClosesocket)
	ON_COMMAND(ID_SET_RUNMODE, OnSetRunmode)
	ON_COMMAND(ID_HELP_GETIP, OnHelpGetip)
	ON_COMMAND(ID_HELP_EXPLAIN, OnHelpExplain)
	ON_COMMAND(ID_ACTION_LOSE, OnActionLose)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessDlg message handlers

BOOL CChessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	GetClientRect(&rect);
	CClientDC dc(this);
	GetClientRect(rect);
	m_bplate.LoadBitmap(IDB_BITMAP1);
	m_bplate1.LoadBitmap(IDB_BITMAP2);
	m_bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	m_bitstone.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	
	m_pplate->CreateCompatibleDC(&dc);
	m_pplate1->CreateCompatibleDC(&dc);
	m_pmap->CreateCompatibleDC(&dc);
	m_pstone->CreateCompatibleDC(&dc);

	m_pplate->SelectObject(&m_bplate);
	m_pplate1->SelectObject(&m_bplate1);
	m_pmap->SelectObject(&m_bitmap);
	m_pstone->SelectObject(&m_bitstone);	

	m_whichplate=1;//默认是背景1
	m_pickpos.x=m_pickpos.y=-1;
	m_pickno=-1;
	m_beforepickpos.x=m_beforepickpos.y=-1;
	m_whofirst=1;  //红先下
	m_movestep=0;  //棋步计数归零
	m_runmode[0]=0;//默认本机作战
	m_runmode[1]=-1;
	m_binit=false;
	m_bIsserver=-1;
	m_bIschangestone=false;//没有换棋子
	m_port=6880;
	m_bIP[0]=127;m_bIP[1]=m_bIP[2]=0;m_bIP[3]=1;
	m_IsSendMessg=true;
	for(int i=0;i<10;i++)
		for(int j=0;j<9;j++)
		{
			plate.platepos[i][j].x=j;
			plate.platepos[i][j].y=i;
		 	plate.platepos[i][j].chessID=NOCHESS;
		}
	DrawPlate();   //画棋盘

	UpdatePlate();
	//慢慢弹开窗口
	CRect dlgrect;
	GetWindowRect(dlgrect);
	CRect desktoprect;;
	GetDesktopWindow()->GetWindowRect(desktoprect);
	MoveWindow((desktoprect.Width(),dlgrect.Width())/2,
		       (desktoprect.Height()-dlgrect.Height())/2,
			    0,0);
	m_nWidth=dlgrect.Width();
	m_nHeight=dlgrect.Height();
	m_nDx=10;
	m_nDy=10;
	m_nDx1=10;
	m_nDy1=10;
	SetTimer(1,2,NULL);

	static bool flag=false;
	if(flag==false)
	{
		if(::AfxSocketInit()==FALSE)
		{
			AfxMessageBox("socket init error!");
		}
		GetLocalIP();
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChessDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{	CClientDC dc(this);
		GetClientRect(&rect);
		UpdatePlate();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChessDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CChessDlg::DrawPlate()
{
	if(m_whichplate==0)
	{
		GetClientRect(rect);
		CBrush br(GetSysColor(COLOR_3DFACE));
		m_pmap->FillRect(rect,&br);
	}
	if(m_whichplate==1)
		m_pmap->BitBlt(0,0,rect.Width(),rect.Height(),m_pplate,0,0,SRCCOPY);
//	m_pmap->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),m_pplate,0,0,bmInfo.bmWidth,bmInfo.bmHeight,SRCCOPY);
	if(m_whichplate==2)
		m_pmap->BitBlt(0,0,rect.Width(),rect.Height(),m_pplate1,0,0,SRCCOPY);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CPen *pOldpen=m_pmap->SelectObject(&pen);


	for(int i=0;i<10;i++)
	{
		m_pmap->MoveTo(plate.m_nPlateLeft,plate.m_nPlateLeft+i*plate.m_ndy);
		m_pmap->LineTo(plate.m_nPlateRight,plate.m_nPlateLeft+i*plate.m_ndy);

	}

	for(i=0;i<9;i++)//画棋格
	{
		if(i==0||i==8)
		{
			m_pmap->MoveTo(plate.m_nPlateLeft+i*plate.m_ndx,plate.m_nPlateTop);
			m_pmap->LineTo(plate.m_nPlateLeft+i*plate.m_ndx,plate.m_nPlateBottom);
		}
		else
		{
			m_pmap->MoveTo(plate.m_nPlateLeft+i*plate.m_ndx,plate.m_nPlateTop);
			m_pmap->LineTo(plate.m_nPlateLeft+i*plate.m_ndx,plate.m_nPlateTop+4*plate.m_ndy);
			m_pmap->MoveTo(plate.m_nPlateLeft+i*plate.m_ndx,plate.m_nPlateTop+5*plate.m_ndy);
			m_pmap->LineTo(plate.m_nPlateLeft+i*plate.m_ndx,plate.m_nPlateBottom);
		}
	}

		m_pmap->MoveTo(plate.m_nPlateLeft+plate.m_ndx*3,plate.m_nPlateTop);
		m_pmap->LineTo(plate.m_nPlateLeft+plate.m_ndx*5,plate.m_nPlateTop+plate.m_ndy*2);
		m_pmap->MoveTo(plate.m_nPlateLeft+plate.m_ndx*5,plate.m_nPlateTop);
		m_pmap->LineTo(plate.m_nPlateLeft+plate.m_ndx*3,plate.m_nPlateTop+plate.m_ndy*2);

		m_pmap->MoveTo(plate.m_nPlateLeft+plate.m_ndx*3,plate.m_nPlateTop+plate.m_ndy*7);
		m_pmap->LineTo(plate.m_nPlateLeft+plate.m_ndx*5,plate.m_nPlateBottom);
		m_pmap->MoveTo(plate.m_nPlateLeft+plate.m_ndx*5,plate.m_nPlateTop+plate.m_ndy*7);
		m_pmap->LineTo(plate.m_nPlateLeft+plate.m_ndx*3,plate.m_nPlateBottom);

		m_pmap->MoveTo(363,17);
		m_pmap->LineTo(505,17);
		m_pmap->LineTo(505,plate.m_nPlateBottom+3);
		m_pmap->LineTo(363,plate.m_nPlateBottom+3);
		m_pmap->LineTo(363,17);
		m_pmap->SelectObject(pOldpen);

		CPen pen1(PS_SOLID,2,RGB(0,0,0));
		pOldpen=m_pmap->SelectObject(&pen1);
		//画外框
		m_pmap->MoveTo(17,18);
		m_pmap->LineTo(plate.m_nPlateRight+3,18);
		m_pmap->LineTo(plate.m_nPlateRight+3,plate.m_nPlateBottom+3);
		m_pmap->LineTo(17,plate.m_nPlateBottom+3);
		m_pmap->LineTo(17,18);
		m_pmap->SelectObject(pOldpen);
		//画兵炮位
		DrawConer(2,1,0);
		DrawConer(2,7,0);
		DrawConer(3,0,1);
		DrawConer(3,2,0);
		DrawConer(3,4,0);
		DrawConer(3,6,0);
		DrawConer(3,8,2);
		DrawConer(7,1,0);
		DrawConer(7,7,0);
		DrawConer(6,0,1);
		DrawConer(6,2,0);
		DrawConer(6,4,0);
		DrawConer(6,6,0);
		DrawConer(6,8,2);
}
void CChessDlg::DrawConer(int y,int x,int i)
{
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen *pOldpen=m_pmap->SelectObject(&pen);
	if(i==0||i==1)
	{
		m_pmap->MoveTo(plate.m_nPlateLeft+x*plate.m_ndx+3,plate.m_nPlateTop+y*plate.m_ndy-10);
		m_pmap->LineTo(plate.m_nPlateLeft+x*plate.m_ndx+3,plate.m_nPlateTop+y*plate.m_ndy-3);
		m_pmap->LineTo(plate.m_nPlateLeft+x*plate.m_ndx+10,plate.m_nPlateTop+y*plate.m_ndy-3);
		m_pmap->MoveTo(plate.m_nPlateLeft+x*plate.m_ndx+3,plate.m_nPlateTop+y*plate.m_ndy+10);
		m_pmap->LineTo(plate.m_nPlateLeft+x*plate.m_ndx+3,plate.m_nPlateTop+y*plate.m_ndy+3);
		m_pmap->LineTo(plate.m_nPlateLeft+x*plate.m_ndx+10,plate.m_nPlateTop+y*plate.m_ndy+3);
	}
	if(i==0||i==2)
	{
		m_pmap->MoveTo(plate.m_nPlateLeft+x*plate.m_ndx-3,plate.m_nPlateTop+y*plate.m_ndy-10);
		m_pmap->LineTo(plate.m_nPlateLeft+x*plate.m_ndx-3,plate.m_nPlateTop+y*plate.m_ndy-3);
		m_pmap->LineTo(plate.m_nPlateLeft+x*plate.m_ndx-10,plate.m_nPlateTop+y*plate.m_ndy-3);
		m_pmap->MoveTo(plate.m_nPlateLeft+x*plate.m_ndx-3,plate.m_nPlateTop+y*plate.m_ndy+10);
		m_pmap->LineTo(plate.m_nPlateLeft+x*plate.m_ndx-3,plate.m_nPlateTop+y*plate.m_ndy+3);
		m_pmap->LineTo(plate.m_nPlateLeft+x*plate.m_ndx-10,plate.m_nPlateTop+y*plate.m_ndy+3);
	}
	m_pmap->SelectObject(pOldpen);
}
void CChessDlg::UpdatePlate()
{
	//m_pstone->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),m_pmap,rect.left,rect.top,SRCCOPY);
	m_pstone->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),m_pmap,0,0,rect.Width(),rect.Height(),SRCCOPY);
	//画棋盘上的棋子
	for(int i=0;i<10;i++)
		for(int j=0;j<9;j++)
		{
			if(plate.platepos[i][j].chessID!=NOCHESS)
			{
				CPoint p;
				p.x=(long)plate.platepos[i][j].x;
				p.y=(long)plate.platepos[i][j].y;
				p=PointToView(p.x,p.y);
				m_pstone->DrawIcon(p.x-4,p.y-4,m_hIconstone[plate.platepos[i][j].chessID]);
		}
	}
	//画拿起的棋子
	if(m_pickno!=-1)
	{
		m_pstone->DrawIcon(m_pickpos.x,m_pickpos.y,	m_hIconstone[stone[m_pickno].stonepos.chessID]);
	}
//	CString strmovestep;
//	strmovestep.Format("%d,%d",m_chockside,m_pickno/16);
//	ShowSolidFont(370,80,strmovestep);
	CClientDC dc(this);
	dc.BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),m_pstone,rect.left,rect.top,SRCCOPY);

}
void CChessDlg::InitGame()
{
	//加载起子图标
	m_hIconstone[R_K]=AfxGetApp()->LoadIcon(IDI_R_K);
	m_hIconstone[R_C]=AfxGetApp()->LoadIcon(IDI_R_C);
	m_hIconstone[R_M]=AfxGetApp()->LoadIcon(IDI_R_M);
	m_hIconstone[R_P]=AfxGetApp()->LoadIcon(IDI_R_P);
	m_hIconstone[R_S]=AfxGetApp()->LoadIcon(IDI_R_S);
	m_hIconstone[R_X]=AfxGetApp()->LoadIcon(IDI_R_X);
	m_hIconstone[R_B]=AfxGetApp()->LoadIcon(IDI_R_B);
	m_hIconstone[B_K]=AfxGetApp()->LoadIcon(IDI_B_K);
	m_hIconstone[B_C]=AfxGetApp()->LoadIcon(IDI_B_C);
	m_hIconstone[B_M]=AfxGetApp()->LoadIcon(IDI_B_M);
	m_hIconstone[B_P]=AfxGetApp()->LoadIcon(IDI_B_P);
	m_hIconstone[B_S]=AfxGetApp()->LoadIcon(IDI_B_S);
	m_hIconstone[B_X]=AfxGetApp()->LoadIcon(IDI_B_X);
	m_hIconstone[B_B]=AfxGetApp()->LoadIcon(IDI_B_B);
	//stone[0--15]是黑方的
	stone[0].stonepos.x=4;stone[0].stonepos.y=0;stone[0].stonepos.chessID=B_K;//黑将
	stone[1].stonepos.x=0;stone[1].stonepos.y=0;stone[1].stonepos.chessID=B_C;//左边的黑车
	stone[2].stonepos.x=1;stone[2].stonepos.y=0;stone[2].stonepos.chessID=B_M;
	stone[3].stonepos.x=1;stone[3].stonepos.y=2;stone[3].stonepos.chessID=B_P;
	stone[4].stonepos.x=3;stone[4].stonepos.y=0;stone[4].stonepos.chessID=B_S;
	stone[5].stonepos.x=2;stone[5].stonepos.y=0;stone[5].stonepos.chessID=B_X;
	stone[6].stonepos.x=0;stone[6].stonepos.y=3;stone[6].stonepos.chessID=B_B;//从左到右各个黑兵
	stone[7].stonepos.x=2;stone[7].stonepos.y=3;stone[7].stonepos.chessID=B_B;      
	stone[8].stonepos.x=4;stone[8].stonepos.y=3;stone[8].stonepos.chessID=B_B;
	stone[9].stonepos.x=6;stone[9].stonepos.y=3;stone[9].stonepos.chessID=B_B;
	stone[10].stonepos.x=8;stone[10].stonepos.y=3;stone[10].stonepos.chessID=B_B;
	stone[11].stonepos.x=8;stone[11].stonepos.y=0;stone[11].stonepos.chessID=B_C;//右边的黑车
	stone[12].stonepos.x=7;stone[12].stonepos.y=0;stone[12].stonepos.chessID=B_M;
	stone[13].stonepos.x=7;stone[13].stonepos.y=2;stone[13].stonepos.chessID=B_P;
	stone[14].stonepos.x=5;stone[14].stonepos.y=0;stone[14].stonepos.chessID=B_S;
	stone[15].stonepos.x=6;stone[15].stonepos.y=0;stone[15].stonepos.chessID=B_X;//右边的黑象
	//stone[16--31]是红方的子
	stone[16].stonepos.x=4;stone[16].stonepos.y=9;stone[16].stonepos.chessID=R_K;//红将
	stone[17].stonepos.x=0;stone[17].stonepos.y=9;stone[17].stonepos.chessID=R_C;//左边那个车
	stone[18].stonepos.x=1;stone[18].stonepos.y=9;stone[18].stonepos.chessID=R_M;
	stone[19].stonepos.x=1;stone[19].stonepos.y=7;stone[19].stonepos.chessID=R_P;
	stone[20].stonepos.x=3;stone[20].stonepos.y=9;stone[20].stonepos.chessID=R_S;
	stone[21].stonepos.x=2;stone[21].stonepos.y=9;stone[21].stonepos.chessID=R_X;
	stone[22].stonepos.x=0;stone[22].stonepos.y=6;stone[22].stonepos.chessID=R_B;//左边那个兵
	stone[23].stonepos.x=2;stone[23].stonepos.y=6;stone[23].stonepos.chessID=R_B;
	stone[24].stonepos.x=4;stone[24].stonepos.y=6;stone[24].stonepos.chessID=R_B;
	stone[25].stonepos.x=6;stone[25].stonepos.y=6;stone[25].stonepos.chessID=R_B;
	stone[26].stonepos.x=8;stone[26].stonepos.y=6;stone[26].stonepos.chessID=R_B;
	stone[27].stonepos.x=8;stone[27].stonepos.y=9;stone[27].stonepos.chessID=R_C;//右边那个车
	stone[28].stonepos.x=7;stone[28].stonepos.y=9;stone[28].stonepos.chessID=R_M;
	stone[29].stonepos.x=7;stone[29].stonepos.y=7;stone[29].stonepos.chessID=R_P;
	stone[30].stonepos.x=5;stone[30].stonepos.y=9;stone[30].stonepos.chessID=R_S;
	stone[31].stonepos.x=6;stone[31].stonepos.y=9;stone[31].stonepos.chessID=R_X;
	 //初始化棋盘标志
	for(int i=0;i<10;i++)
		for(int j=0;j<9;j++)
		{
			plate.platepos[i][j].x=j;
			plate.platepos[i][j].y=i;
			plate.platepos[i][j].chessID=NOCHESS;
		}
	for(i=0;i<10;i++)
		for(int j=0;j<9;j++)
		{
			for(int k=0;k<32;k++)
			{
				if(stone[k].stonepos.x==j&&stone[k].stonepos.y==i)
				{
					plate.platepos[i][j].chessID=stone[k].stonepos.chessID;
				}
				stone[k].m_stoneno=k;
			}
		}
	m_whofirst=1;//红方先走
	m_movestep=0;//棋步归零
	m_pickno=-1; //没有子被拿起
	m_bIschangestone=false;
	UpdatePlate();
}
CPoint CChessDlg::PlateToPoint(const CPoint &point)
{
	CPoint p;
	p.x=(point.x-plate.m_nPlateLeft/2-1)/plate.m_ndx;
	p.y=(point.y-plate.m_nPlateTop/2-1)/plate.m_ndy;
	return p;
}

CPoint CChessDlg::PointToView(const BYTE x, const BYTE y)
{
	CPoint p;
	p.x=x*plate.m_ndx+plate.m_nPlateLeft/2+1;
	p.y=y*plate.m_ndy+plate.m_nPlateTop/2+1;
	return p;
}
int CChessDlg::GetStoneNum(CPoint &point)
{   //获得棋子的号码
	for(int i=0;i<32;i++)
	{
		if(stone[i].stonepos.x==point.x&&stone[i].stonepos.y==point.y)
			return i;
	}
}
void CChessDlg::MoveStone(CPoint p1,CPoint p2)
{
	if(m_bIschangestone==false)//棋盘没有交换的时候
	{
		if(plate.platepos[p2.y][p2.x].chessID==NOCHESS)	//不吃子的时候
		{

			plate.platepos[p2.y][p2.x].chessID=stone[m_pickno].stonepos.chessID;
	
			//将棋步压栈
			StepNode temp;
			temp.from=p1;
			temp.to=p2;
			temp.movestoneID=stone[m_pickno].stonepos.chessID;
			temp.movestoneno=m_pickno;
			temp.bekillstonepos.x=temp.bekillstonepos.y=-1;
			temp.bekillstoneID=NOCHESS;
			temp.bekillstoneno=-1;
			move.PutStack(temp);

			stone[m_pickno].stonepos.x=(BYTE)p2.x;
			stone[m_pickno].stonepos.y=(BYTE)p2.y;
		}
		else if(plate.platepos[p2.y][p2.x].chessID!=NOCHESS)//吃子的时候
		{
		
			int y=GetStoneNum(p2);//目标棋子的号码
			plate.platepos[p2.y][p2.x].chessID=stone[m_pickno].stonepos.chessID;
			//将棋步压栈
			StepNode temp;
			temp.from=p1;
			temp.to=p2;
			temp.movestoneID=stone[m_pickno].stonepos.chessID;
			temp.movestoneno=m_pickno;
			temp.bekillstonepos=p2;
			temp.bekillstoneID=stone[y].stonepos.chessID;
			temp.bekillstoneno=y;
			move.PutStack(temp);
			//处理被吃的子
			stone[y].stonepos.x=stone[y].stonepos.y=-1;
			stone[y].stonepos.chessID=NOCHESS;

			stone[m_pickno].stonepos.x=(BYTE)p2.x;
			stone[m_pickno].stonepos.y=(BYTE)p2.y;
		}
		m_movestep++;
		UpdatePlate();
	}
	else//棋盘交换的情况下
	{
		if(plate.platepos[p2.y][p2.x].chessID==NOCHESS)
		{
			plate.platepos[p2.y][p2.x].chessID=stone[m_pickno].stonepos.chessID;
			StepNode temp;
			temp.from.x=8-p1.x;
			temp.from.y=9-p1.y;
			temp.to.x=8-p2.x;
			temp.to.y=9-p2.y;
			temp.movestoneID=stone[m_pickno].stonepos.chessID;
			temp.movestoneno=m_pickno;
			temp.bekillstoneID=NOCHESS;
			temp.bekillstoneno=-1;
			temp.bekillstonepos.x=temp.bekillstonepos.y=-1;
			move.PutStack(temp);
			stone[m_pickno].stonepos.x=(BYTE)p2.x;
			stone[m_pickno].stonepos.y=(BYTE)p2.y;
		}
		else if(plate.platepos[p2.y][p2.x].chessID!=NOCHESS)
		{
			CPoint p3,p4;
			int y=GetStoneNum(p2);
			p3.x=8-p1.x;
			p3.y=9-p1.y;
			p4.x=8-p2.x;
			p4.y=9-p2.y;
			plate.platepos[p2.y][p2.x].chessID=stone[m_pickno].stonepos.chessID;
			//将棋步压栈
			StepNode temp;
			temp.from=p3;
			temp.to=p4;
			temp.movestoneID=stone[m_pickno].stonepos.chessID;
			temp.movestoneno=m_pickno;
			temp.bekillstonepos=p4;
			temp.bekillstoneID=stone[y].stonepos.chessID;
			temp.bekillstoneno=y;
			move.PutStack(temp);
			//处理被吃的子
			stone[y].stonepos.x=stone[y].stonepos.y=-1;
			stone[y].stonepos.chessID=NOCHESS;

			stone[m_pickno].stonepos.x=(BYTE)p2.x;
			stone[m_pickno].stonepos.y=(BYTE)p2.y;
		}
		m_movestep++;
		UpdatePlate();


	}

}

void CChessDlg::NetMoveStone(CMessg &msg)
{    //处理对方发给的棋步
	if(m_bIschangestone==false)
	{//没有交换棋盘的情况下
		CPoint point;
		point.x=msg.xfrom;
		point.y=msg.yfrom;
		int x=GetStoneNum(point);//取得走的棋子的号数
		StepNode temp;
		temp.from.x=msg.xfrom;
		temp.from.y=msg.yfrom;
		temp.to.x=msg.xto;
		temp.to.y=msg.yto;
		if(plate.platepos[msg.yto][msg.xto].chessID==NOCHESS)
		{
			plate.platepos[msg.yto][msg.xto].chessID=stone[x].stonepos.chessID;
			plate.platepos[msg.yfrom][msg.xfrom].chessID=NOCHESS;

			temp.movestoneID=plate.platepos[msg.yto][msg.xto].chessID;
			temp.movestoneno=x;
			temp.bekillstoneID=NOCHESS;
			temp.bekillstoneno=-1;
			
		}
		else
		{
			CPoint point1;
			point1.x=msg.xto;
			point1.y=msg.yto;
			int y=GetStoneNum(point1);
			temp.movestoneID=plate.platepos[msg.yfrom][msg.xfrom].chessID;;
			temp.movestoneno=x;
			temp.bekillstoneID=plate.platepos[msg.yto][msg.xto].chessID;;
			temp.bekillstoneno=y;
			stone[y].stonepos.chessID=NOCHESS;
			stone[y].stonepos.x=stone[y].stonepos.y=-1;
			plate.platepos[msg.yto][msg.xto].chessID=stone[x].stonepos.chessID;
			plate.platepos[msg.yfrom][msg.xfrom].chessID=NOCHESS;
		}
		stone[x].stonepos.x=(int)temp.to.x;
		stone[x].stonepos.y=(int)temp.to.y;
		move.PutStack(temp);
	}
	else
	{   //在本机交换棋盘的情况下
		CPoint point1,point2;
		point1.x=8-msg.xfrom;
		point1.y=9-msg.yfrom;
		point2.x=8-msg.xto;
		point2.y=9-msg.yto;
		int x=GetStoneNum(point1);//取得走的棋子的号数
		StepNode temp;
		temp.from=point1;
		temp.to=point2;
		//没有吃子的情况下
		if(plate.platepos[point2.y][point2.x].chessID==NOCHESS)
		{
			plate.platepos[point2.y][point2.x].chessID=stone[x].stonepos.chessID;
			plate.platepos[point1.y][point1.x].chessID=NOCHESS;

			temp.movestoneID=stone[x].stonepos.chessID;
			temp.movestoneno=x;
			temp.bekillstoneID=NOCHESS;
			temp.bekillstoneno=-1;	
		}
		else//吃子的情况下
		{   //记录吃子的信息		
			int y=GetStoneNum(point2);
			temp.movestoneID=stone[x].stonepos.chessID;
			temp.movestoneno=x;
			temp.bekillstoneID=stone[y].stonepos.chessID;
			temp.bekillstoneno=y;
			stone[y].stonepos.chessID=NOCHESS;
			stone[y].stonepos.x=stone[y].stonepos.y=-1;
			plate.platepos[point2.y][point2.x].chessID=plate.platepos[point1.y][point1.x].chessID;
			plate.platepos[point1.y][point1.x].chessID=NOCHESS;
					
		}
		stone[x].stonepos.x=(int)point2.x;
		stone[x].stonepos.y=(int)point2.y;
		move.PutStack(temp);
	}
	m_movestep++;
	CurrentPrompt();
	UpdatePlate();


}
void CChessDlg::Remove()
{
	if(m_movestep==0)
	{
		CString str;
		str=_T("不能再悔棋");
		ShowSolidFont(370,92,str);
		UpdatePlate();
		::Sleep(900);
		str="";
		ShowSolidFont(370,92,str);
		UpdatePlate();
		return;
	}
    if(m_movestep!=0)//&&m_runmode[0]==-1)
	{
		if(m_bIschangestone==false)//没有将换棋盘的情况下
		{
			StepNode ret=move.PushStack();
			CPoint p1,p2;
			p1=ret.to;
			p2=ret.from;
			if(ret.bekillstoneID==NOCHESS)//没有吃子的情况下
			{
				stone[ret.movestoneno].stonepos.x=(BYTE)p2.x;
				stone[ret.movestoneno].stonepos.y=(BYTE)p2.y;
				stone[ret.movestoneno].stonepos.chessID=ret.movestoneID;
				plate.platepos[p2.y][p2.x].chessID=ret.movestoneID;
				plate.platepos[p1.y][p1.x].chessID=NOCHESS;
					
			}
			else //吃子的情况下
			{
				stone[ret.movestoneno].stonepos.x=(BYTE)p2.x;
				stone[ret.movestoneno].stonepos.y=(BYTE)p2.y;
				stone[ret.movestoneno].stonepos.chessID=ret.movestoneID;
				plate.platepos[p2.y][p2.x].chessID=ret.movestoneID;
				stone[ret.bekillstoneno].stonepos.x=(BYTE)p1.x;
				stone[ret.bekillstoneno].stonepos.y=(BYTE)p1.y;
				stone[ret.bekillstoneno].stonepos.chessID=ret.bekillstoneID;
				plate.platepos[p1.y][p1.x].chessID=ret.bekillstoneID;
			}

		}
		else//交换棋盘的情况下
		{
			StepNode ret=move.PushStack();
			CPoint p1,p2;
			p1.x=8-ret.to.x;
			p1.y=9-ret.to.y;
			p2.x=8-ret.from.x;
			p2.y=9-ret.from.y;
			if(ret.bekillstoneID==NOCHESS)
			{
				stone[ret.movestoneno].stonepos.x=(BYTE)p2.x;
				stone[ret.movestoneno].stonepos.y=(BYTE)p2.y;
				stone[ret.movestoneno].stonepos.chessID=ret.movestoneID;
				plate.platepos[p2.y][p2.x].chessID=ret.movestoneID;
				plate.platepos[p1.y][p1.x].chessID=NOCHESS;
					
			}
			else 
			{
				stone[ret.movestoneno].stonepos.x=(BYTE)p2.x;
				stone[ret.movestoneno].stonepos.y=(BYTE)p2.y;
				stone[ret.movestoneno].stonepos.chessID=ret.movestoneID;
				plate.platepos[p2.y][p2.x].chessID=ret.movestoneID;
				stone[ret.bekillstoneno].stonepos.x=(BYTE)p1.x;
				stone[ret.bekillstoneno].stonepos.y=(BYTE)p1.y;
				stone[ret.bekillstoneno].stonepos.chessID=ret.bekillstoneID;
				plate.platepos[p1.y][p1.x].chessID=ret.bekillstoneID;
			}
		}
			m_movestep--;
			m_pickno=-1;
			CurrentPrompt();
			UpdatePlate();
	}		

}
void CChessDlg::SetRunMode()
{
	OnSetRunmode();
}

void CChessDlg::SetRunMode(int whofirst)
{
	m_whofirst=whofirst;
	CurrentPrompt();

}
void CChessDlg::SetNewGame()
{
	m_binit=true;
	InitGame();
	CurrentPrompt();	
}
BOOL CChessDlg::IsInPlate(const CPoint &point)
{
	if(point.x<4||point.x>plate.m_nPlateRight+16)
		return FALSE;
	if(point.y<4||point.y>plate.m_nPlateBottom+16)
		return FALSE;
	return TRUE;
}
BOOL CChessDlg::IsGameOver()
{
	if(stone[0].stonepos.chessID==NOCHESS||
		stone[16].stonepos.chessID==NOCHESS)	
		return TRUE;
	return FALSE;
}
BOOL CChessDlg::IsTurnRun()
{
	if(IsGameOver())
	{
		AfxMessageBox("游戏已经结束!");
		return FALSE;
	}
	else 
	{
		if(m_runmode[1]!=-1)//不是同一台机下
		{
			if(m_pickno/16!=m_chockside)//不是拿起自己的子
			{
				return FALSE;
			}//以下是判断是否到自己下
			if(m_whofirst==1)//红先下
			{
				if((m_movestep+1)%2!=m_chockside)
					return FALSE;
			}
			if(m_whofirst==0)//黑先下
			{
				if(m_movestep%2!=m_chockside)
					return FALSE;
			}	
		}
		else	//同一台机下
		{	//以下是判断是否到自己下
			if(m_whofirst==0)//黑先下
			{
				if(m_movestep%2!=m_pickno/16)
					return FALSE;
			}
			if(m_whofirst==1)//红先下
			{
				if((m_movestep+1)%2!=m_pickno/16)
					return FALSE;
			}
		}
	}
	return TRUE;
}
void CChessDlg::ShowSolidFont(int x,int y,CString str)
{   //制作立体字提示
	CRect rc(x,y,x+130,y+30);
	CBrush br(RGB(0,128,128));
	m_pmap->FillRect(rc,&br);

	CFont font;
	font.CreateFont(22,0,0,0,FW_BOLD,true,
		FALSE,0,0,0,0,0,0,"宋体");

	m_pmap->SetBkMode(TRANSPARENT);
	CFont *pOldFont=m_pmap->SelectObject(&font);
	//画亮字
	COLORREF oldcolor=m_pmap->SetTextColor(::GetSysColor(COLOR_3DFACE));
	m_pmap->DrawText(str,rc+CPoint(1,1),DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	//画暗字
	m_pmap->SetTextColor(::GetSysColor(COLOR_3DSHADOW));
	m_pmap->DrawText(str,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	
	m_pmap->SetTextColor(oldcolor);
	m_pmap->SelectObject(pOldFont);
}
void CChessDlg::CurrentPrompt()
{
	CString str=_T(" ");
	CString strStep;
	strStep=_T("棋步数:");
	m_strstep.Format("%d",m_movestep);
	strStep+=m_strstep;
	ShowSolidFont(370,28,strStep);
	if(!IsGameOver())
	{
		//判断是否将军
		CPoint movestonepos;
		for(int i=0;i<16;i++)//检查黑方对红帅
		{
			movestonepos.x=stone[i].stonepos.x;
			movestonepos.y=stone[i].stonepos.y;
			if(stone[i].stonepos.chessID!=NOCHESS)
			{
				if(move.MayMove(plate.platepos,movestonepos.x,movestonepos.y,stone[16].stonepos.x,stone[16].stonepos.y,m_bIschangestone))
				{
					str=_T("[黑方将军]");
					break;
				}
			}
		}
		for(i=16;i<32;i++)//检查红方对黑将
		{
			movestonepos.x=stone[i].stonepos.x;
			movestonepos.y=stone[i].stonepos.y;
			if(stone[i].stonepos.chessID!=NOCHESS)
			{
				if(move.MayMove(plate.platepos,movestonepos.x,movestonepos.y,stone[0].stonepos.x,stone[0].stonepos.y,m_bIschangestone))
				{
					str=_T("[红方将军]");
					break;
				}
			}
		}
	}
	else
	{
		if(stone[0].stonepos.chessID==NOCHESS)
			str=_T("红方胜利!");
		else if(stone[16].stonepos.chessID==NOCHESS)
			str=_T("黑方胜利!");
	}
	ShowSolidFont(370,92,str);
	CString strturn=_T("");
	if(m_whofirst==1)		//红先下
	{
		if(m_movestep%2==1)
			strturn="到黑方走棋";
		else
			strturn="到红方走棋";
	}
	else if(m_whofirst==0) //黑先下
	{
		if((m_movestep+1)%2==1)
			strturn="到黑方走棋";
		else
			strturn="到红方走棋";
	}
	ShowSolidFont(370,60,strturn);

	CString strside=_T("");
	if(m_chockside==0)
		strside="(本机选黑)";
	else
		strside="(本机选红)";
	CString strrunmode=_T("中国象棋(网络版)");
	if(m_runmode[1]!=-1)
	{
		switch(m_runmode[1])
		{
		case 0:
			strrunmode+="--本机做服务器";
			break;
		case 1:
			strrunmode+="--本机做客户端";
			break;
		default:
			strrunmode=_T("国象棋【网络版】");
		}
	}
	UpdatePlate();
	if(m_runmode[1]!=-1)
		strrunmode+=strside;
	SetWindowText(strrunmode);

}
void CChessDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	CPoint p=PlateToPoint(point);
	if(IsInPlate(point))//在棋盘内,该点有棋子
	{
		m_pickno=GetStoneNum(p);//取得拿起的棋子的号码
		if(plate.platepos[p.y][p.x].chessID!=NOCHESS&&IsTurnRun())
		{
			HCURSOR hcursor=AfxGetApp()->LoadCursor(IDC_CURSOR2);
		    SetCursor(hcursor);
			m_beforepickpos.x=p.x;
			m_beforepickpos.y=p.y;
			move.m_pickstoneID=plate.platepos[p.y][p.x].chessID;
			plate.platepos[p.y][p.x].chessID=NOCHESS;
			SetCapture();
		}
		else
		{
			m_pickno=-1;
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CChessDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_pickno!=-1)//有棋子被拿起
	{
		CPoint targetpoint=PlateToPoint(point);//将屏幕坐标转换成棋盘坐标
		if(move.MayMove(plate.platepos,m_beforepickpos.x,m_beforepickpos.y,targetpoint.x,targetpoint.y,m_bIschangestone)&&IsTurnRun())
		{
			MoveStone(m_beforepickpos,targetpoint);
			CMessg msg;
			if(m_bIschangestone==false)//棋子没有交换的情况下
			{
				msg.xfrom=m_beforepickpos.x;
				msg.yfrom=m_beforepickpos.y;
				msg.xto=targetpoint.x;
				msg.yto=targetpoint.y;
			}
			else                      //交换棋子的情况下
			{
				msg.xfrom=8-m_beforepickpos.x;
				msg.yfrom=9-m_beforepickpos.y;
				msg.xto=8-targetpoint.x;
				msg.yto=9-targetpoint.y;
			}
			msg.m_messgtype=1;		 //发送棋子的消息类型设为1
			msg.strchat=_T("");
			m_ClientSocket.SendMessage(&msg);//将棋步发给对方
		}
		else
		{//不能动，还原
			plate.platepos[m_beforepickpos.y][m_beforepickpos.x].chessID=stone[m_pickno].stonepos.chessID;
		}
		move.m_pickstoneID=NOCHESS;
		m_beforepickpos.x=m_beforepickpos.y=-1;
		m_pickpos.x=m_pickpos.y=-1;
		m_pickno=-1;
		ReleaseCapture();
		CurrentPrompt();
		UpdatePlate();
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CChessDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!IsGameOver())//有棋子被拿起的时候
	{
		if(IsTurnRun()&&m_pickno!=-1)
		{
			//不能那出棋盘
			if(point.x<plate.m_nPlateLeft-16)
				point.x=plate.m_nPlateLeft+2;
			if(point.x>plate.m_nPlateRight+16)
				point.x=plate.m_nPlateRight+3;
			if(point.y<plate.m_nPlateTop-16)
				point.y=plate.m_nPlateTop+3;
			if(point.y>plate.m_nPlateBottom+16)
				point.y=plate.m_nPlateBottom+3;
			//记录显示那起棋子的实际位置
			m_pickpos.x=point.x-16;
			m_pickpos.y=point.y-16;
			//更新画面
			UpdatePlate();
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CChessDlg::OnSetBcolose0() 
{
	// TODO: Add your command handler code here
	m_whichplate=0;
	DrawPlate();
	UpdatePlate();	
}

void CChessDlg::OnSetBcolose1() 
{
	// TODO: Add your command handler code here
	m_whichplate=1;
	DrawPlate();
	UpdatePlate();	
}

void CChessDlg::OnSetBcolose2() 
{
	// TODO: Add your command handler code here
	m_whichplate=2;
	DrawPlate();
	UpdatePlate();
	
}

void CChessDlg::OnActionRemove() 
{
	// TODO: Add your command handler code here
	if(m_runmode[1]!=-1)
	{
		CMessg msg;
		msg.m_messgtype=2;
		m_ClientSocket.SendMessage(&msg);
	}
	else
	{
		Remove();
	}
}

void CChessDlg::OnSetChangestone() 
{
	// TODO: Add your command handler code here
	if(m_binit==true)//在游戏初始化后才能
	{
		//棋子交换
		m_bIschangestone=!m_bIschangestone;
		for(int i=0;i<32;i++)
		{
			stone[i].stonepos.x=8-stone[i].stonepos.x;
			stone[i].stonepos.y=9-stone[i].stonepos.y;
		}
		for(i=0;i<10;i++)
			for(int j=0;j<9;j++)
			{
				plate.platepos[i][j].chessID=NOCHESS;
			}
		for(i=0;i<10;i++)
			for(int j=0;j<9;j++)
			{
				for(int k=0;k<32;k++)
				{
					if(stone[k].stonepos.x==j&&stone[k].stonepos.y==i)
					{
						plate.platepos[i][j].chessID=stone[k].stonepos.chessID;
					}
				}
			}
	}
	UpdatePlate();
}

void CChessDlg::OnActinoNew() 
{
	// TODO: Add your command handler code here
	m_binit=true;
	CMessg msg;
	msg.m_messgtype=6;
	m_ClientSocket.SendMessage(&msg);
	InitGame();
	CurrentPrompt();
}

void CChessDlg::OnStartCreateserver() 
{
	// TODO: Add your command handler code here
	CStartServerDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_port=dlg.m_nport;
		m_bIsserver=0;
		m_ListenSocket.Init(m_port,this);
		m_runmode[0]=-1;
		m_runmode[1]=0;//做服务器
		m_chockside=1; //选红
		CString str=_T("");
		CString str1=_T("");
		str1.Format("%d.%d.%d.%d",m_bIP[0],m_bIP[1],m_bIP[02],m_bIP[3]);
		str="[等待客户连接……][本机IP:"+str1+"]";
		SetWindowText(str);
	}
	

}

void CChessDlg::OnStartExit() 
{
	// TODO: Add your command handler code here
	if(AfxMessageBox("确定要退出游戏吗？",MB_YESNO)==IDNO)
	{
		return;
	}
	else 
	{
		m_ClientSocket.CloseSocket();
		m_ClientSocket.Close();
		m_ListenSocket.Close();	
		CDialog::OnClose();
		exit(1);
	}
}

void CChessDlg::OnStartConnectserver() 
{
	// TODO: Add your command handler code here
	m_bIsserver=1;//做客户端
	CConnectDlg dlg;
	dlg.m_nport=m_port;
	if(dlg.DoModal()==IDOK)
	{
		m_runmode[0]=0;
		m_runmode[1]=1;//做客户端
		m_chockside=0; //选黑
		m_port=dlg.m_nport;
		m_bIP[0]=dlg.m_ipaddressedit1;
		m_bIP[1]=dlg.m_ipaddressedit2;
		m_bIP[2]=dlg.m_ipaddressedit3;
		m_bIP[3]=dlg.m_ipaddressedit4;
		m_ip.Format("%d.%d.%d.%d",m_bIP[0],m_bIP[1],m_bIP[2],m_bIP[3]);
		m_ClientSocket.Create();
		CString str="[正在连接服务器,请稍等……]"+m_ip;
		SetWindowText(str);
		if(m_ClientSocket.Connect(LPCSTR(m_ip),m_port))
		{
			m_ClientSocket.Init(this);
			m_binit=true;
			InitGame();
			CurrentPrompt();
			AfxMessageBox("【连接成功!!!\n现在你可以开始游戏了!】");
		}	
		else
		{
			m_ClientSocket.Close();
			AfxMessageBox("【连接失败……】  ");
		}
	}
}

void CChessDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CRect dlgrect;
	GetWindowRect(dlgrect);
	CRect desktoprect;
	GetDesktopWindow()->GetWindowRect(desktoprect);
	if(nIDEvent==1)
	{
		MoveWindow(
			(-m_nDx+desktoprect.Width()-dlgrect.Width())/2,
			(-m_nDy+desktoprect.Height()-dlgrect.Height())/2,
			+m_nDx+dlgrect.Width(),
			+m_nDy+dlgrect.Height());
		if(dlgrect.Width()>=m_nWidth)
			m_nDx=0;
		if(dlgrect.Height()>=m_nHeight)
			m_nDy=0;
		if((dlgrect.Width()>=m_nWidth)&&(dlgrect.Height()>=m_nHeight))
			KillTimer(1);
	}
	if((dlgrect.Width()>=m_nWidth)&&(dlgrect.Height()>=m_nHeight))
		KillTimer(1);	
	CDialog::OnTimer(nIDEvent);
}

void CChessDlg::ProcessPendingAccept()
{//处理客户端的连接的
	if(m_ListenSocket.Accept(m_ClientSocket)==FALSE)
	{
		AfxMessageBox("server listen Socket Error");
		return ;
	}
	else
	{
		m_ClientSocket.Init(this);
		m_binit=true;
		InitGame();
		CurrentPrompt();
		AfxMessageBox("有人进来\n现在你可以开始游戏了!");
	}

}

void CChessDlg::GetLocalIP()
{
	static BOOL first=TRUE;
	if(first==TRUE)
	{
		CClientSocket::GetLocalHostName(m_sLocalName);
		CClientSocket::GetIpAddress(LPCSTR(m_sLocalName),m_bIP[0],m_bIP[1],m_bIP[2],m_bIP[3]);
		m_ip.Format("%d.%d.%d.%d",m_bIP[0],m_bIP[1],m_bIP[2],m_bIP[3]);
		first=FALSE;
	}
}

void CChessDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(AfxMessageBox("确定要退出游戏吗？",MB_YESNO)==IDNO)
	{
		return;
	}
	else 
	{
		m_ClientSocket.CloseSocket();
		m_ClientSocket.Close();
		m_ListenSocket.Close();	
		CDialog::OnClose();
		exit(1);
	}
}

void CChessDlg::OnStartClosesocket() 
{
	// TODO: Add your command handler code here
	m_ClientSocket.CloseSocket();
	m_ClientSocket.Close();
	m_ListenSocket.Close();	
	CDialog::OnClose();	
	AfxMessageBox("连接已经断开！");
}

void CChessDlg::OnSetRunmode() 
{
	// TODO: Add your command handler code here
	if(m_movestep==0)
	{
		if(m_bIsserver!=1)//不是做客户端的情况
		{
			CSetRunModeDlg dlg;
			dlg.m_whofirst=m_whofirst;
			if(dlg.DoModal()==IDOK)
			{
				m_whofirst=dlg.m_whofirst;
				if(m_runmode[1]==0)//做服务器是情况下才发送
				{
					CMessg msg;
					msg.m_messgtype=7;
					msg.xfrom=m_whofirst;	
					m_ClientSocket.SendMessage(&msg);
				}
				CurrentPrompt();
			}
		}
		else
		{
			AfxMessageBox("你做客户端，没这个权利!");
		}
	}
	else
	{ 
		CString str,str1;
		str="游戏中不能做这样的设置!";
		SetWindowText(str);
	}

}

void CChessDlg::OnHelpGetip() 
{
	// TODO: Add your command handler code here
	CString str,str1;
	str="本机IP:";
	str1.Format("%d.%d.%d.%d",m_bIP[0],m_bIP[1],m_bIP[2],m_bIP[3]);
	str+=str1+"　　";
	AfxMessageBox(str);

	
}

void CChessDlg::OnHelpExplain() 
{
	// TODO: Add your command handler code here
	CFileDialog filedlg(TRUE,"txt","chess.txt",NULL,NULL,this);
	int respond=filedlg.DoModal();
	if(respond==IDOK)
	{
	ShellExecute(this->m_hWnd,"open",filedlg.GetPathName(),NULL,NULL,SW_SHOW);
	}
}

void CChessDlg::OnActionLose() 
{
	// TODO: Add your command handler code here
	if(m_runmode[1]!=-1)
	{
		if(AfxMessageBox("确定认输了吗?",MB_YESNO)==IDYES)
		{
			CMessg msg;
			msg.m_messgtype=5;
			m_ClientSocket.SendMessage(&msg);
			SetNewGame();
		}
	}

}



void CChessDlg::OnHelpAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	if(dlg.DoModal()==IDOK)
	{

	}
}
