// Stone.cpp: implementation of the CStone class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Chess.h"
#include "Stone.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStone::CStone()
{
	stonepos.x=stonepos.y=-1;
	stonepos.chessID=NOCHESS;
	m_stoneno=-1;
	m_stonevalues=0;

}
CStone::~CStone()
{

}
