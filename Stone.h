// Stone.h: interface for the CStone class.
//
//////////////////////////////////////////////////////////////////////
#include "define.h"

#if !defined(AFX_STONE_H__4942E6D3_973B_4E35_BD1E_3BC41E17A517__INCLUDED_)
#define AFX_STONE_H__4942E6D3_973B_4E35_BD1E_3BC41E17A517__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStone  
{
public:
	CHESSMANPOS stonepos;
	int m_stoneno;
	int m_stonevalues;
public:
	CStone();
	virtual ~CStone();

};

#endif // !defined(AFX_STONE_H__4942E6D3_973B_4E35_BD1E_3BC41E17A517__INCLUDED_)
