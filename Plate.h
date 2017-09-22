// Plate.h: interface for the CPlate class.
//
//////////////////////////////////////////////////////////////////////
#include "define.h"
#include "Move.h"
#if !defined(AFX_PLATE_H__D491B3DE_DFFD_4EED_B19A_8CADA70537C9__INCLUDED_)
#define AFX_PLATE_H__D491B3DE_DFFD_4EED_B19A_8CADA70537C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPlate  
{
public:
	CHESSMANPOS platepos[10][9];//棋盘各个交点的坐标
	int m_ndx;     //棋格的宽
	int m_ndy;     //棋格的长
	int m_nPlateX; //棋盘的宽
	int m_nPlateY; //棋盘的长

	int m_nPlateLeft;//棋盘位置信息
	int m_nPlateRight;
	int m_nPlateTop;
	int m_nPlateBottom;
public:
	CPlate();
	virtual ~CPlate();

};

#endif // !defined(AFX_PLATE_H__D491B3DE_DFFD_4EED_B19A_8CADA70537C9__INCLUDED_)
