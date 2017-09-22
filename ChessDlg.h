// ChessDlg.h : header file
//

#include "Plate.h"
#include "Stone.h"
#include "define.h"
#include "Move.h"
#include "Messg.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "ConnectDlg.h"
#include "SetRunModeDlg.h"
#include "StartServerDlg.h"
#if !defined(AFX_CHESSDLG_H__C5DC7209_CFC1_4972_A700_3129510ABEB0__INCLUDED_)
#define AFX_CHESSDLG_H__C5DC7209_CFC1_4972_A700_3129510ABEB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChessDlg dialog

class CChessDlg : public CDialog
{
// Construction
public:
	CChessDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CChessDlg();
	void DrawPlate();                              //画棋盘
	void DrawConer(int y,int x,int i);             //画兵炮位
	void InitGame();                               //初始化游戏
	BOOL IsInPlate(const CPoint &point);           //是否在棋盘内
	CPoint PlateToPoint(const CPoint &point);      //屏幕向棋盘坐标的转换
	CPoint PointToView(const BYTE x,const BYTE y); //棋盘向屏幕坐标的转换
	void UpdatePlate();                            //更新画面
	void ShowSolidFont(int x,int y ,CString str);  //显示立体字
	void MoveStone(CPoint p1,CPoint p2);           //移动棋子
	void NetMoveStone(CMessg &msg);				   //显示对方移动棋子
	void CurrentPrompt();						   //当前提示
	int GetStoneNum(CPoint &point);                //取得棋子号码
	BOOL IsGameOver();                             //游戏是结束
	BOOL IsTurnRun();							   //是否轮到自己下棋
	void Remove();                                 //悔棋用的
	void SetRunMode();                             //设置下棋模式
	void SetRunMode(int whofirst);     
	void SetNewGame();
	void GetLocalIP();                             //取得本机的IP
	void ProcessPendingAccept();                   //处理客户端的连接
// Dialog Data
	//{{AFX_DATA(CChessDlg)
	enum { IDD = IDD_CHESS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CPlate plate;                 //棋盘
	CMove move;		              //移动对象
	CRect rect;                   //用于取得客户区的
	bool m_bIschangestone;        //是否换棋子
	//用于网络的部分
	CServerSocket m_ListenSocket;
	CClientSocket m_ClientSocket;
	int m_bIsserver;			   //是否做服务器
	bool m_binit;				   //是否初始化
	int m_port;                    //端口号
	bool m_IsSendMessg;            //控制是否向对方发送消息
	CString m_ip;
	BYTE m_bIP[4];
	CString m_sLocalName;
protected:
	HICON m_hIcon;
	HICON m_hIconstone[32];		  //32个棋子图标句柄
	int m_movestep;				  //记录下棋的步数
	CString m_strstep;            //下棋的步数字符串
	CPoint m_beforepickpos;		  //记录拿其棋子前的位置		  
	CPoint m_pickpos;			  //拿起的棋子的实际位置
	int m_pickno;				  //记录拿起的棋子的号码
	CStone stone[32];             //32个棋子
	int m_whichplate;			  //选择哪一个背景图片
	CBitmap m_bplate,m_bplate1;	  //背景图片的位图
	CDC *m_pplate,*m_pplate1;     //兼容背景图片的DC
	CBitmap m_bitmap;             //做棋盘的位图
	CBitmap m_bitstone;           //棋子的位图
	CDC *m_pmap,*m_pstone;        //双缓冲DC
private:
	CPoint m_point;
	int m_nWidth,m_nHeight;		  //这六个变量是控制窗口特效的
	int m_nDx,m_nDy;              
	int m_nDx1,m_nDy1;
	int m_whofirst;				  //谁先下0是红，1是黑
	int m_chockside;			  //是选红1还是选黑0
	int m_runmode[2];			  //下棋模式
	// Generated message map functions
	//{{AFX_MSG(CChessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetBcolose0();
	afx_msg void OnSetBcolose1();
	afx_msg void OnSetBcolose2();
	afx_msg void OnActionRemove();
	afx_msg void OnSetChangestone();
	afx_msg void OnActinoNew();
	afx_msg void OnStartCreateserver();
	afx_msg void OnStartExit();
	afx_msg void OnStartConnectserver();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnStartClosesocket();
	afx_msg void OnSetRunmode();
	afx_msg void OnHelpGetip();
	afx_msg void OnHelpExplain();
	afx_msg void OnActionLose();
	afx_msg void OnHelpAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHESSDLG_H__C5DC7209_CFC1_4972_A700_3129510ABEB0__INCLUDED_)
