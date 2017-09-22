// Messg.h: interface for the CMessg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSG_H__334B65A5_E964_41C3_944B_AF7823EB7DBD__INCLUDED_)
#define AFX_MESSG_H__334B65A5_E964_41C3_944B_AF7823EB7DBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//用于网络通信的消息类型类
class CMessg : public CObject  
{
protected:
	DECLARE_DYNCREATE(CMessg)
public:
	CMessg();
	virtual ~CMessg();
	void Init();
	virtual void Serialize(CArchive &ar);
public:
	int m_messgtype; //消息类型
	int xfrom,yfrom; //走棋的起始位置
	int xto,yto;	 //走棋的终点位置
	CString strchat; //聊天用的

};

#endif // !defined(AFX_MESSG_H__334B65A5_E964_41C3_944B_AF7823EB7DBD__INCLUDED_)
