// Messg.cpp: implementation of the CMessg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chess.h"
#include "Messg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CMessg,CObject)
CMessg::CMessg()
{
	xfrom=yfrom=-1;
	xto=yto=-1;
	m_messgtype=0;

}

CMessg::~CMessg()
{

}

void CMessg::Init()
{
	xfrom=yfrom=-1;
	xto=yto=-1;
	m_messgtype=0;	
}

void CMessg::Serialize(CArchive &ar)
{//将数据串行化
	if(ar.IsStoring())
	{
		ar<<xfrom;
		ar<<yfrom;
		ar<<xto;
		ar<<yto;
		ar<<m_messgtype;
	}
	else
	{
		ar>>xfrom;
		ar>>yfrom;
		ar>>xto;
		ar>>yto;
		ar>>m_messgtype;
	}

}
