// Messg.h: interface for the CMessg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSG_H__334B65A5_E964_41C3_944B_AF7823EB7DBD__INCLUDED_)
#define AFX_MESSG_H__334B65A5_E964_41C3_944B_AF7823EB7DBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//��������ͨ�ŵ���Ϣ������
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
	int m_messgtype; //��Ϣ����
	int xfrom,yfrom; //�������ʼλ��
	int xto,yto;	 //������յ�λ��
	CString strchat; //�����õ�

};

#endif // !defined(AFX_MESSG_H__334B65A5_E964_41C3_944B_AF7823EB7DBD__INCLUDED_)
