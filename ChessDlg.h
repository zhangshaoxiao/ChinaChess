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
	void DrawPlate();                              //������
	void DrawConer(int y,int x,int i);             //������λ
	void InitGame();                               //��ʼ����Ϸ
	BOOL IsInPlate(const CPoint &point);           //�Ƿ���������
	CPoint PlateToPoint(const CPoint &point);      //��Ļ�����������ת��
	CPoint PointToView(const BYTE x,const BYTE y); //��������Ļ�����ת��
	void UpdatePlate();                            //���»���
	void ShowSolidFont(int x,int y ,CString str);  //��ʾ������
	void MoveStone(CPoint p1,CPoint p2);           //�ƶ�����
	void NetMoveStone(CMessg &msg);				   //��ʾ�Է��ƶ�����
	void CurrentPrompt();						   //��ǰ��ʾ
	int GetStoneNum(CPoint &point);                //ȡ�����Ӻ���
	BOOL IsGameOver();                             //��Ϸ�ǽ���
	BOOL IsTurnRun();							   //�Ƿ��ֵ��Լ�����
	void Remove();                                 //�����õ�
	void SetRunMode();                             //��������ģʽ
	void SetRunMode(int whofirst);     
	void SetNewGame();
	void GetLocalIP();                             //ȡ�ñ�����IP
	void ProcessPendingAccept();                   //����ͻ��˵�����
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
	CPlate plate;                 //����
	CMove move;		              //�ƶ�����
	CRect rect;                   //����ȡ�ÿͻ�����
	bool m_bIschangestone;        //�Ƿ�����
	//��������Ĳ���
	CServerSocket m_ListenSocket;
	CClientSocket m_ClientSocket;
	int m_bIsserver;			   //�Ƿ���������
	bool m_binit;				   //�Ƿ��ʼ��
	int m_port;                    //�˿ں�
	bool m_IsSendMessg;            //�����Ƿ���Է�������Ϣ
	CString m_ip;
	BYTE m_bIP[4];
	CString m_sLocalName;
protected:
	HICON m_hIcon;
	HICON m_hIconstone[32];		  //32������ͼ����
	int m_movestep;				  //��¼����Ĳ���
	CString m_strstep;            //����Ĳ����ַ���
	CPoint m_beforepickpos;		  //��¼��������ǰ��λ��		  
	CPoint m_pickpos;			  //��������ӵ�ʵ��λ��
	int m_pickno;				  //��¼��������ӵĺ���
	CStone stone[32];             //32������
	int m_whichplate;			  //ѡ����һ������ͼƬ
	CBitmap m_bplate,m_bplate1;	  //����ͼƬ��λͼ
	CDC *m_pplate,*m_pplate1;     //���ݱ���ͼƬ��DC
	CBitmap m_bitmap;             //�����̵�λͼ
	CBitmap m_bitstone;           //���ӵ�λͼ
	CDC *m_pmap,*m_pstone;        //˫����DC
private:
	CPoint m_point;
	int m_nWidth,m_nHeight;		  //�����������ǿ��ƴ�����Ч��
	int m_nDx,m_nDy;              
	int m_nDx1,m_nDy1;
	int m_whofirst;				  //˭����0�Ǻ죬1�Ǻ�
	int m_chockside;			  //��ѡ��1����ѡ��0
	int m_runmode[2];			  //����ģʽ
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
