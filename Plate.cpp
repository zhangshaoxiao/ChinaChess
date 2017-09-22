// Plate.cpp: implementation of the CPlate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Chess.h"
#include "Plate.h"
#

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlate::CPlate()
{
	m_ndx=40;//���̵ĸ��
	m_ndy=40;//���̵ĸ��
	m_nPlateLeft=20;
	m_nPlateTop=20;
	m_nPlateX=8*m_ndx;//���̵Ŀ�
	m_nPlateY=9*m_ndy;//���̵ĸ�
	m_nPlateRight=m_nPlateLeft+m_nPlateX;
	m_nPlateBottom=m_nPlateTop+m_nPlateY;
	for(int i=0;i<10;i++)
		for(int j=0;j<9;j++)
		{
			platepos[i][j].x=j;
			platepos[i][j].y=i;
			platepos[i][j].chessID=NOCHESS;
		}
}

CPlate::~CPlate()
{

}
